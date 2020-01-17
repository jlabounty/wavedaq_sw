#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

/*
 * dcbs - DCB UDP network server
 *
 * Listens on port 4000 and receives network UDP packets to read
 * and write to internal registers in the same way as the WDB.
 *
 * S. Ritt Aug. 2019
 *
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "git-revision.h"

extern "C" { // make all library functions callable from C++

#include "drv_axi_dcb_reg_bank.h"
#include "register_map_dcb.h"
#include "update_config.h"
#include "drv_bpl.h"
#include "dbg.h"
#include "system.h"
#include "sc_io.h"
#include "wdaq_board_id.h"

}

// port to start the UDP servers on
#define SERVER_PORT_ASC 3000
#define SERVER_PORT_BIN 4000

#define CMD_SCAN        0x01
#define CMD_WRITE32     0x14
#define CMD_READ32      0x24

#define WDAQ_N_SLOTS      18

#define SWAP_UINT32(x) (((x) >> 24) | \
                       (((x) & 0x00FF0000) >> 8) | \
                       (((x) & 0x0000FF00) << 8) | \
                       ((x) << 24))

int _server_abort = 0;

WDAQ_BRD_VENDOR_NAME; // define strings for board vendor names
WDAQ_BRD_TYPE_NAME;   // define strings for board type names

WDAQ_BRD board[WDAQ_N_SLOTS];

/*------------------------------------------------------------------*/

void print_buffer(const char *buffer, int len);

/*------------------------------------------------------------------*/

double clock_us() {
   struct timespec now;

   clock_gettime(CLOCK_MONOTONIC, &now);
   return now.tv_sec * 1e6 + now.tv_nsec / 1000.0;
}

/*------------------------------------------------------------------*/

void printf_crate_scan(char *b, int size) {
   int n_boards = 0;
   b[0] = 0;
   for (int slot = 0; slot < WDAQ_N_SLOTS; slot++) {
      int status = get_slot_board_info(slot, &board[slot]);
      if (status && board[slot].type_id <= BRD_TYPE_ID_MAX &&
          board[slot].vendor_id <= BRD_VENDOR_ID_MAX) {

         char name[32];
         if (board[slot].type_id == BRD_TYPE_ID_WDB) {

            char buffer[10];
            char rbuffer[10];

            memset(buffer, 0, sizeof(buffer));
            buffer[0] = CMD_READ32;
            buffer[1] = 0;
            buffer[2] = 0;
            buffer[3] = 0;
            buffer[4] = 0x24; // Status register SN
            buffer[5] = 0; // dummy

            spi_binary_cmd(buffer, rbuffer, 6+4, slot, board[slot].type_id, board[slot].rev_id);

            unsigned int sn = (rbuffer[8] << 8) | rbuffer[9];
            snprintf(name, sizeof(name), "WD%03d", sn);
         } else
            snprintf(name, sizeof(name), "%s", wdaq_brd_type_name[board[slot].type_id]);

         snprintf(b+strlen(b), size,
                  "Slot %2d: Found board \"%s\", Revision %c, Variant %d, Vendor \"%s\"\n", slot,
                  name,
                  'A' + board[slot].rev_id,
                  board[slot].variant_id,
                  wdaq_brd_vendor_name[board[slot].vendor_id]);
         n_boards++;
      }
   }
   if (n_boards == 0)
      snprintf(b, size, "No boards found\n");
}

/*------------------------------------------------------------------*/

int main(int argc, char *argv[]) {

   int verbose = 0;
   int daemon = 0;
   char hostname[256], mac[256];
   int sock_bin, sock_asc, sock_raw;
   int board_type = 0;
   int board_revision = 0;

   /* parse command line parameters */
   for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'D')
         daemon = 1;
      else if (argv[i][0] == '-' && argv[i][1] == 'v')
         verbose = 1;
      else if (argv[i][0] == '-') {
         if (i + 1 >= argc || argv[i + 1][0] == '-')
            goto usage;
      } else {
         usage:
         printf("usage: dcbs [-p port] [-v]\n\n");
         printf("       -D     Become a daemon\n");
         printf("       -h     Print this help page\n");
         printf("       -v     Produce verbose debugging output\n\n");
         return 0;
      }
   }

   /*---- initialize system ----*/

   // set default debug level
   set_dbg_level(verbose ? DBG_LEVEL_SPAM : DBG_LEVEL_ERR);

   init_system();

   // set SW state ready to turn LED green
   emio_set_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_SW_READY_PIN);

   if (verbose)
      print_sys_info();

   memset(board, 0, sizeof(board));
   if (verbose) {
      set_dbg_level(DBG_LEVEL_ERR);
      printf("\nBoards found:\n");
      printf("-------------\n");
   }
   for (int i = 0; i < WDAQ_N_SLOTS; i++)
      int status = get_slot_board_info(i, &board[i]);

   if (verbose) {
      char b[1500];
      printf_crate_scan(b, sizeof(b));
      printf("%s\n", b);
      set_dbg_level(DBG_LEVEL_SPAM);
   }

   /*---- initialize network ----*/

   gethostname(hostname, sizeof(hostname));

   // create raw socket
   sock_raw = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));
   if (sock_raw == -1) {
      //socket creation failed, may be because of non-root privileges
      perror("Failed to create socket, please start program as root");
      return 1;
   }

   // socket address used for the server
   struct sockaddr_in server_address;
   memset(&server_address, 0, sizeof(server_address));
   server_address.sin_family = AF_INET;

   // htons: host to network short: transforms a value in host byte
   // ordering format to a short value in network byte ordering format
   server_address.sin_port = htons(SERVER_PORT_BIN);

   // htons: host to network long: same as htons but to long
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);

   // create a UDP socket, creation returns -1 on failure
   if ((sock_bin = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("Could not create socket\n");
      return 1;
   }

   // bind it to listen to the incoming connections on the created server
   // address, will return -1 on error
   if ((bind(sock_bin, (struct sockaddr *) &server_address, sizeof(server_address))) < 0) {
      printf("Could not bind socket to port %d\n", SERVER_PORT_BIN);
      return 1;
   }

   // socket address used to store client address
   struct sockaddr_in client_address;
   socklen_t client_address_len = sizeof(client_address);

   // socket address used for the server
   memset(&server_address, 0, sizeof(server_address));
   server_address.sin_family = AF_INET;

   // htons: host to network short: transforms a value in host byte
   // ordering format to a short value in network byte ordering format
   server_address.sin_port = htons(SERVER_PORT_ASC);

   // htons: host to network long: same as htons but to long
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);

   // create a UDP socket, creation returns -1 on failure
   if ((sock_asc = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
      printf("Could not create socket\n");
      return 1;
   }

   // bind it to listen to the incoming connections on the created server
   // address, will return -1 on error
   if ((bind(sock_asc, (struct sockaddr *) &server_address, sizeof(server_address))) < 0) {
      printf("Could not bind socket to port %d\n", SERVER_PORT_ASC);
      return 1;
   }

   // socket address used to store client address
   client_address_len = sizeof(client_address);

   printf("DCB binary and ASCII servers listening on %s ports %d,%d\n", hostname, SERVER_PORT_BIN, SERVER_PORT_ASC);

   if (daemon) {
      printf("DCB server becoming a daemon...\n");
      int i, fd, pid;

      if ((pid = fork()) < 0)
         return 1;
      else if (pid != 0)
         exit(0);  // parent finished

      /* child continues here */

      setsid(); // become session leader
   }

   // run indefinitely
   while (!_server_abort) {
      char buffer[65536];
      fd_set fds;

      // periodically propagate new register contents to hardware
      auto_update_configurations();
      trigger_update_configurations();

      FD_ZERO(&fds);
      FD_SET(sock_bin, &fds);
      FD_SET(sock_asc, &fds);
      FD_SET(sock_raw, &fds);

      struct timeval tv = {0, 10000}; // 10 ms
      if (select(FD_SETSIZE, &fds, NULL, NULL, &tv) < 0)
         perror("select");

      if (FD_ISSET(sock_raw, &fds)) {
         memset(buffer, 0, sizeof(buffer));
         int len = recvfrom(sock_raw, buffer, 65536, 0, NULL, NULL);
         if (len == -1) {
            perror("Failed to receive raw packet");
            exit(1);
         }

         struct ethhdr *eth = (struct ethhdr *) buffer;
         struct iphdr  *ip  = (struct iphdr *) (buffer + sizeof(struct ethhdr));
         struct udphdr *udp = (struct udphdr *) (buffer + sizeof(struct ethhdr) + ip->ihl*4);

         if (ip->protocol == IPPROTO_UDP && ntohs(udp->dest) == SERVER_PORT_BIN) {
            memset(&client_address, 0, sizeof(client_address));
            client_address.sin_addr.s_addr = ip->saddr;

            if (verbose) {
               printf("\n---- RAW UDP Packet ---------------------\n");
               printf("IP source         %s\n", inet_ntoa(client_address.sin_addr));
               printf("MAC source        %02x:%02x:%02x:%02x:%02x:%02x\n",
                      eth->h_source[0], eth->h_source[1], eth->h_source[2],
                      eth->h_source[3], eth->h_source[4], eth->h_source[5]);

               printf("Source port       %d\n", ntohs(udp->source));
               printf("Destination port  %d\n", ntohs(udp->dest));
               printf("Data Length       %d\n", ntohs(udp->len) - sizeof(struct udphdr));
               printf("-----------------------------------------\n");
            }
         }
      }

      if (FD_ISSET(sock_bin, &fds)) {
         // read content into buffer from an incoming client
         memset(buffer, 0, sizeof(buffer));
         int len = recvfrom(sock_bin, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address,
                            &client_address_len);

         // inet_ntoa prints user friendly representation of the
         // ip address
         if (verbose) {
            char mac[256];
            printf("Binary request received: %d bytes from client %s\n", len, inet_ntoa(client_address.sin_addr));
            buffer[len] = '\0';
            print_buffer(buffer, len);
         }

         // interpret packet
         unsigned int cmd = buffer[0];
         unsigned int slot = buffer[1];
         unsigned int seq = (buffer[2] <<  8 )| (buffer[3] <<  0);
         unsigned int adr = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | (buffer[7] << 0);

         if (cmd == CMD_SCAN) {
            char rbuffer[1600];
            rbuffer[0] = CMD_SCAN;

            if (verbose)
               printf("Board scan:\n");

            for (int i = 0; i < WDAQ_N_SLOTS; i++) {
               int status = get_slot_board_info(i, &board[i]);
               if (status) {
                  rbuffer[i*4+4] = board[i].vendor_id;
                  rbuffer[i*4+5] = board[i].type_id;
                  rbuffer[i*4+6] = board[i].rev_id;
                  rbuffer[i*4+7] = board[i].variant_id;
               } else {
                  rbuffer[i*4+4] = 0xFF;
                  rbuffer[i*4+5] = 0xFF;
                  rbuffer[i*4+6] = 0xFF;
                  rbuffer[i*4+7] = 0xFF;
               }
            }

            // send acknowledge back to client
            rbuffer[0] = CMD_SCAN;
            rbuffer[1] = 0x01;
            rbuffer[2] = buffer[2];
            rbuffer[3] = buffer[3];

            sendto(sock_bin, rbuffer, 4+WDAQ_N_SLOTS*4, 0, (struct sockaddr *) &client_address, sizeof(client_address));

         } else if (cmd == CMD_WRITE32) {
            char rbuffer[1600];
            unsigned n = (len - 8) / 4;

            if (verbose) {
               printf("Write to slot %d at 0x%04X, seq %d:\n", slot, adr, seq);
               print_buffer(buffer+8, n * 4);
            }

            unsigned int *p = (unsigned int *) (&buffer[8]);
            unsigned int d;

            if (slot == 16) { // DCB
               for (int i = 0; i < n; i++, p++) {
                  d = SWAP_UINT32(*p);
                  reg_bank_write(adr + i * 4, &d, 1);
               }
            } else {
               double start = clock_us();

               buffer[3] = CMD_WRITE32;
               spi_binary_cmd((char*)&buffer[3], (char*)rbuffer, (len-8)+5, slot,
                       board[slot].type_id, board[slot].rev_id); // 1 cmd, 4 adr. bytes + data

               if (verbose)
                  printf("SPI took %5.3lf ms\n\n", (clock_us() - start)/1e3);
            }

            // send acknowledge back to client
            buffer[1] = 0x01;
            buffer[2] = (seq >> 8) & 0xFF;
            buffer[3] = seq & 0xFF;
            sendto(sock_bin, buffer, 4, 0, (struct sockaddr *) &client_address, sizeof(client_address));

         } else if (cmd == CMD_READ32) {
            char rbuffer[1600];
            memset(rbuffer, 0, sizeof(rbuffer));

            unsigned int n = (buffer[8] << 24) | (buffer[9] << 16) | (buffer[10] << 8) | (buffer[11] << 0);

            // limit data to 1024 bytes for the moment
            n = n > 1024 ? 1024 : n;

            if (verbose)
               printf("Read %d bytes from slot %d at 0x%08X, seq %d:\n", n, slot, adr, seq);

            rbuffer[0] = CMD_READ32;
            rbuffer[1] = 0x01;
            rbuffer[2] = buffer[2];
            rbuffer[3] = buffer[3];

            unsigned int *p = (unsigned int *) (&rbuffer[4]);
            unsigned int d;

            if (slot == 16) { // DCB
               for (int i = 0; i < n / 4 && i < 1024 / 4; i++, p++) {
                  reg_bank_read(adr + i * 4, &d, 1);
                  *p = SWAP_UINT32(d);
               }
            } else {

               buffer[3] = CMD_READ32;
               buffer[8] = 0; // dummy byte

               spi_binary_cmd((char*)&buffer[3], (char*)&rbuffer[4], n+6, slot,
                              board[slot].type_id, board[slot].rev_id); // 1 cmd, 4 adr. bytes, 1 dummy + data

               memmove(&rbuffer[4], &rbuffer[10], n);
            }

            if (verbose)
               print_buffer(rbuffer, n + 4);

            // send data to client
            sendto(sock_bin, rbuffer, n + 4, 0, (struct sockaddr *) &client_address, sizeof(client_address));

         } else {

            char str[2000];

            strncpy(str, "DCBS Server\nRevision: ", sizeof(str));
            strncat(str, GIT_REVISION, sizeof(str) - strlen(str));
            strncat(str, "\n\n", sizeof(str) - strlen(str));

            // send same content back to the client ("echo")
            sendto(sock_bin, str, strlen(str), 0, (struct sockaddr *) &client_address, sizeof(client_address));

         }

      } // binary

      if (FD_ISSET(sock_asc, &fds)) {
         // read content into buffer from an incoming client
         int len = recvfrom(sock_asc, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address,
                            &client_address_len);

         // inet_ntoa prints user friendly representation of the
         // ip address
         if (verbose) {
            buffer[len] = '\0';
            printf("ASCII request received: %d bytes from client %s\n", len, inet_ntoa(client_address.sin_addr));
            print_buffer(buffer, len);
         }

         char rbuffer[1600];
         rbuffer[0] = 0;

         if (isdigit(buffer[0])) {
            unsigned int slot = atoi(buffer);

            if (verbose)
               printf("WDB command found for slot %d\n", slot);

            char *p = strchr(buffer, ' ');
            if (p == NULL)
               p = buffer;
            else
               p++;

            if (verbose)
               printf("TX: %s\n", p);

            spi_ascii_cmd(p, (char*)rbuffer, sizeof(rbuffer), slot,
                          board[slot].type_id, board[slot].rev_id);

            if (verbose)
               printf("RX: %s\n\n", rbuffer);

         } else if (buffer[0] == 'h') {
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "WDB commands:\n\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "<slot> <command>\n\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "DCB commands (no <slot>):\n\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "clkint      Switch bus clock to quartz\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "clkext      Switch bus clock to FCI input\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "delay <n>   Set SYNC delay\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "help        This help page\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "info        Show system information\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "reset       Reboot DCB\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "scan        Scan crate for boards\n\n");

         } else if (strncmp(buffer, "clkint", 6) == 0) {

            unsigned int data = (1 << DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS);
            unsigned int mask = DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK;
            reg_bank_mask_write(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, &data, &mask, 1);
            snprintf(rbuffer, sizeof(rbuffer), "Set bus clock to internal 80 MHz quartz\n");

         } else if (strncmp(buffer, "clkext", 6) == 0) {

            unsigned int data = (0 << DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS);
            unsigned int mask = DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK;
            reg_bank_mask_write(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, &data, &mask, 1);
            snprintf(rbuffer, sizeof(rbuffer), "Set bus clock to external FCI connector input\n");

         } else if (strncmp(buffer, "delay", 5) == 0) {

            char *p = strchr(buffer, ' ');
            if (p == NULL) {
               snprintf(rbuffer, sizeof(rbuffer), "Please specify delay value\n");
            } else {
               unsigned int d = atoi(p);
               unsigned int data = (d << DCB_SYNC_DELAY_OFS);
               unsigned int mask = DCB_SYNC_DELAY_MASK;
               reg_bank_mask_write(DCB_SYNC_DELAY_REG, &data, &mask, 1);
               snprintf(rbuffer, sizeof(rbuffer), "Set delay to %d\n", d);
            }

         } else if (strncmp(buffer, "info", 4) == 0) {
            snprintf(rbuffer, sizeof(rbuffer), "Version Information of DCB:\n\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "-- SW GIT Revision:       %s\n\n", GIT_REVISION);
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "-- Board Type:            WaveDAQ DCB\n");

            unsigned int d;
            reg_bank_read(DCB_BOARD_REVISION_REG, &d, 1);
            d = (d & DCB_BOARD_REVISION_MASK) >> DCB_BOARD_REVISION_OFS;
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "-- Board Revision:        %c\n", 'A'+d);

            reg_bank_read(DCB_BOARD_VARIANT_REG, &d, 1);
            d = (d & DCB_BOARD_VARIANT_MASK) >> DCB_BOARD_VARIANT_OFS;
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "-- Board Variant:         0x%02X\n\n", d);

         } else if (strncmp(buffer, "reset", 5) == 0) {

            snprintf(rbuffer, sizeof(rbuffer), "Rebooting...\n\n");
            sendto(sock_asc, rbuffer, strlen(rbuffer)+1, 0, (struct sockaddr *) &client_address, sizeof(client_address));
            system("reboot");
            exit(0);

         } else if (strncmp(buffer, "scan", 4) == 0) {

            printf_crate_scan(rbuffer, sizeof(rbuffer));

         } else if (buffer[0] == '\n') {
            // just ignore <CR>

         } else {
            snprintf(rbuffer, sizeof(rbuffer), "Unknown command: %s\n", buffer);
         }

         // interpret packet
         snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "%s> ", hostname);

         // send data to client
         sendto(sock_asc, rbuffer, strlen(rbuffer)+1, 0, (struct sockaddr *) &client_address, sizeof(client_address));

      } // ASCII

   }

   return 0;
}

void print_buffer(const char *buffer, int len) {
   for (int i = 0; i < len; i++) {
      if (i % 16 == 0)
         printf("%04X  ", i);
      printf("%02X ", buffer[i]);
      if (i % 16 == 7)
         printf(" ");
      if (i % 16 == 15) {
         printf(" |");
         for (int j = i - 15; j <= i; j++) {
            printf("%c", buffer[j] < 32 || buffer[j] > 128 ? '.' : buffer[j]);
         }
         printf("|\n");
      }
   }
   if (len % 16 != 0) {
      if (len % 16 < 8)
         printf(" ");
      for (int j = 0; j < 16 - len % 16; j++)
         printf("   ");
      printf(" |");
      for (int j = len - (len % 16); j < len; j++) {
         printf("%c", buffer[j] < 32 || buffer[j] > 128 ? '.' : buffer[j]);
      }
      printf("|\n");
   }
   printf("\n");
}
