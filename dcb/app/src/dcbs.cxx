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

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
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
#include "drv_qspi_flash.h"
#include "flash_memory_maps.h"

}

// port to start the UDP servers on
#define SERVER_PORT_ASC 3000
#define SERVER_PORT_BIN 4000

#define CMD_SCAN        0x01
#define CMD_WRITE32     0x14
#define CMD_READ32      0x24

#define WDAQ_N_SLOTS      18
#define WDAQ_SLOT_DCB     16

#define SWAP_UINT32(x) (((x) >> 24) | \
                       (((x) & 0x00FF0000) >> 8) | \
                       (((x) & 0x0000FF00) << 8) | \
                       ((x) << 24))

int _server_abort = 0;

WDAQ_BRD_VENDOR_NAME; // define strings for board vendor names
WDAQ_BRD_TYPE_NAME;   // define strings for board type names

WDAQ_BRD board[WDAQ_N_SLOTS];

//-------------------------------------------------------------------

void print_buffer(const char *buffer, int len);

void process_dcb_command(char *buffer, std::string &rbuffer);

void reg_diff_cmd(int argc, const char **argv, std::string &rbuffer);

void upload(int argc, const char **param, std::string &rbuffer);

//-------------------------------------------------------------------

double clock_us() {
   struct timespec now;

   clock_gettime(CLOCK_MONOTONIC, &now);
   return now.tv_sec * 1e6 + now.tv_nsec / 1000.0;
}

//-------------------------------------------------------------------

std::string stringf(const char *fmt, ...) {
   char *ret;
   va_list ap;

   va_start(ap, fmt);
   vasprintf(&ret, fmt, ap);
   va_end(ap);

   std::string str(ret);
   free(ret);

   return str;
}

//-------------------------------------------------------------------

void printf_crate_scan(const char *hostname, std::string &b) {
   b[0] = 0;
   for (int slot = 0; slot < WDAQ_N_SLOTS; slot++) {
      if (slot == WDAQ_SLOT_DCB) {

         unsigned int d;
         reg_bank_read(DCB_BOARD_REVISION_REG, &d, 1);
         unsigned int rev = (d & DCB_BOARD_REVISION_MASK) >> DCB_BOARD_REVISION_OFS;
         reg_bank_read(DCB_BOARD_VARIANT_REG, &d, 1);
         unsigned int var = (d & DCB_BOARD_VARIANT_MASK) >> DCB_BOARD_VARIANT_OFS;

         b += stringf("Slot %2d: Found board \"DCB%02d\", Revision \"%c\", Variant \"0x%02X\", Vendor \"%s\"\n",
                      slot,
                      atoi(hostname + 3),
                      'A' + rev,
                      var,
                      "PSI");
      } else {
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

               spi_binary_cmd(buffer, rbuffer, 6 + 4, slot, board[slot].type_id, board[slot].rev_id);

               unsigned int sn = (rbuffer[8] << 8) | rbuffer[9];
               snprintf(name, sizeof(name), "WD%03d", sn);
            } else
               snprintf(name, sizeof(name), "%s", wdaq_brd_type_name[board[slot].type_id]);

            b += stringf("Slot %2d: Found board \"%s\", Revision \"%c\", Variant \"0x%02X\", Vendor \"%s\"\n",
                         slot,
                         name,
                         'A' + board[slot].rev_id,
                         board[slot].variant_id,
                         wdaq_brd_vendor_name[board[slot].vendor_id]);
         }
      }
   }
}

//-------------------------------------------------------------------

typedef struct {
   int slot;
   time_t last;
} UDP_CONN;

int main(int argc, char *argv[]) {

   int verbose = 0;
   int daemon = 0;
   char hostname[256], mac[256];
   int sock_bin, sock_asc, sock_raw;
   int board_type = 0;
   int board_revision = 0;
   std::map <std::string, UDP_CONN> connection;

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

   gethostname(hostname, sizeof(hostname));

   // set SW state ready to turn LED green
   emio_set_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_SW_READY_PIN);

   if (verbose) {
      printf("\n");
      print_sys_info();
   }

   memset(board, 0, sizeof(board));
   if (verbose) {
      set_dbg_level(DBG_LEVEL_ERR);
      printf("\nBoards found:\n");
      printf("-------------\n");
   }
   for (int i = 0; i < WDAQ_N_SLOTS; i++)
      int status = get_slot_board_info(i, &board[i]);

   if (verbose) {
      std::string str;
      printf_crate_scan(hostname, str);
      std::cout << str << std::endl;
      set_dbg_level(DBG_LEVEL_SPAM);
   }

   /*---- initialize network ----*/

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
         struct iphdr *ip = (struct iphdr *) (buffer + sizeof(struct ethhdr));
         struct udphdr *udp = (struct udphdr *) (buffer + sizeof(struct ethhdr) + ip->ihl * 4);

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
            printf("Binary request received: %d bytes from client %s, port %d\n", len,
                   inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
            buffer[len] = '\0';
            print_buffer(buffer, len);
         }

         // interpret packet
         unsigned int cmd = buffer[0];
         unsigned int slot = buffer[1];
         unsigned int seq = (buffer[2] << 8) | (buffer[3] << 0);
         unsigned int adr = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | (buffer[7] << 0);

         if (cmd == CMD_SCAN) {
            char rbuffer[1600];
            rbuffer[0] = CMD_SCAN;

            if (verbose)
               printf("Board scan:\n");

            for (int i = 0; i < WDAQ_N_SLOTS; i++) {
               int status = get_slot_board_info(i, &board[i]);
               if (status) {
                  rbuffer[i * 4 + 4] = board[i].vendor_id;
                  rbuffer[i * 4 + 5] = board[i].type_id;
                  rbuffer[i * 4 + 6] = board[i].rev_id;
                  rbuffer[i * 4 + 7] = board[i].variant_id;
               } else {
                  rbuffer[i * 4 + 4] = 0xFF;
                  rbuffer[i * 4 + 5] = 0xFF;
                  rbuffer[i * 4 + 6] = 0xFF;
                  rbuffer[i * 4 + 7] = 0xFF;
               }
            }

            // send acknowledge back to client
            rbuffer[0] = CMD_SCAN;
            rbuffer[1] = 0x01;
            rbuffer[2] = buffer[2];
            rbuffer[3] = buffer[3];

            sendto(sock_bin, rbuffer, 4 + WDAQ_N_SLOTS * 4, 0, (struct sockaddr *) &client_address,
                   sizeof(client_address));

         } else if (cmd == CMD_WRITE32) {
            char rbuffer[1600];
            unsigned n = (len - 8) / 4;

            if (verbose) {
               printf("Write to slot %d at 0x%04X, seq %d:\n", slot, adr, seq);
               print_buffer(buffer + 8, n * 4);
            }

            unsigned int *p = (unsigned int *) (&buffer[8]);
            unsigned int d;

            if (slot == WDAQ_SLOT_DCB) {
               for (int i = 0; i < n; i++, p++) {
                  d = SWAP_UINT32(*p);
                  reg_bank_write(adr + i * 4, &d, 1);
               }
            } else {
               double start = clock_us();

               buffer[3] = CMD_WRITE32;
               spi_binary_cmd((char *) &buffer[3], (char *) rbuffer, (len - 8) + 5, slot,
                              board[slot].type_id, board[slot].rev_id); // 1 cmd, 4 adr. bytes + data

               if (verbose)
                  printf("SPI took %5.3lf ms\n\n", (clock_us() - start) / 1e3);
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

            if (slot == WDAQ_SLOT_DCB) {
               for (int i = 0; i < n / 4 && i < 1024 / 4; i++, p++) {
                  reg_bank_read(adr + i * 4, &d, 1);
                  *p = SWAP_UINT32(d);
               }
            } else {

               buffer[3] = CMD_READ32;
               buffer[8] = 0; // dummy byte

               spi_binary_cmd((char *) &buffer[3], (char *) &rbuffer[4], n + 6, slot,
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
         memset(buffer, 0, sizeof(buffer));
         int len = recvfrom(sock_asc, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address,
                            &client_address_len);

         // retrieve address as IP:port
         std::string addr = std::string(inet_ntoa(client_address.sin_addr)) + ":" +
                            std::to_string(ntohs(client_address.sin_port));

         // store address and corresponding slot in connection map
         if (connection.find(addr) == connection.end())
            connection[addr].slot = WDAQ_SLOT_DCB; // Default is DCB slot
         connection[addr].last = time(0);

         // clean up connection map
         for (auto &c: connection) {
            if (time(0) > c.second.last + 10) {
               connection.erase(c.first);
               break;
            }
         }

         // strip trailing \r\n from buffer
         if (strchr(buffer, '\n'))
            *strchr(buffer, '\n') = 0;
         if (strchr(buffer, '\r'))
            *strchr(buffer, '\r') = 0;

         // inet_ntoa prints user friendly representation of the ip address
         if (verbose) {
            buffer[len] = '\0';
            printf("ASCII request received: %d bytes from client %s\n", len, addr.c_str());
            print_buffer(buffer, len);
         }

         std::string rbuffer;

         if (strncmp(buffer, "slot", 4) == 0 || strncmp(buffer, "s ", 2) == 0 || strcmp(buffer, "s") == 0) {

            int slot = WDAQ_SLOT_DCB;
            if (strchr(buffer, ' '))
               slot = strtol(strchr(buffer, ' '), 0, 0);

            if (slot == WDAQ_SLOT_DCB) {
               connection[addr].slot = slot;
            } else {
               int status = get_slot_board_info(slot, &board[slot]);
               if (status && board[slot].type_id <= BRD_TYPE_ID_MAX &&
                   board[slot].vendor_id <= BRD_VENDOR_ID_MAX) {
                  connection[addr].slot = slot;
                  if (verbose)
                     printf("Switched to slot #%d\n", connection[addr].slot);
               } else {
                  rbuffer += stringf("No board present in slot %d\n", slot);
               }
            }

         } else if (strncmp(buffer, "scan", 4) == 0) {

            printf_crate_scan(hostname, rbuffer);

         } else if (connection[addr].slot != WDAQ_SLOT_DCB) { //---- Send to slot via SPI -----------

            // send ASCII command to WDB via SPI

            if (verbose)
               printf("WDB command found for slot %d\n", connection[addr].slot);

            if (verbose)
               printf("TX: %s\n", buffer);

            char rb[10000];
            spi_ascii_cmd(buffer, rb, sizeof(rb), connection[addr].slot,
                          board[connection[addr].slot].type_id, board[connection[addr].slot].rev_id);

            if (verbose)
               printf("RX: %s\n\n", rb);

            rbuffer += std::string(rb);

         } else if (strncmp(buffer, "reset", 5) == 0) { //---- Process command locally --------------

            const char *str = "Rebooting...\n\n";
            sendto(sock_asc, str, strlen(str) + 1, 0, (struct sockaddr *) &client_address,
                   sizeof(client_address));
            system("reboot");
            exit(0);

         } else
            // process DCB command locally
            process_dcb_command(buffer, rbuffer);

         // add prompt
         if (connection[addr].slot == WDAQ_SLOT_DCB)
            rbuffer += stringf("%s> ", hostname);
         else
            rbuffer += stringf("%s:%02d> ", hostname, connection[addr].slot);


         // send data to client in chunks of 1000 bytes
         int n = rbuffer.length() + 1;
         int i;
         for (const char *p = rbuffer.c_str(); n > 0; n -= i, p += i)
            i = sendto(sock_asc, p, std::min(1000, n), 0, (struct sockaddr *) &client_address,
                       sizeof(client_address));

      } // ASCII

   }

   return 0;
}

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

void process_dcb_command(char *buffer, std::string &rbuffer) {

   // split string into parameter
   char *param[10];
   int n_param = 0;
   memset(param, 0, sizeof(param));
   char *p = strtok(buffer, " ");
   for (; p != NULL && n_param < 10; n_param++) {
      param[n_param] = p;
      p = strtok(NULL, " ");
   }

   if (param[0] == NULL) // ignore single \n
      return;

   if (param[0][0] == 'h') {  //---- Process locally on DCB ------------------------------

      rbuffer += stringf("\nCrate commands:\n");
      rbuffer += stringf("---------------\n");
      rbuffer += stringf("scan                 Scan crate for boards\n");
      rbuffer += stringf("slot|s <n>           Seclect slot (%d=DCB)\n", WDAQ_SLOT_DCB);
      rbuffer += stringf("   - all further commands will then be sent to slot <n>\n");
      rbuffer += stringf("   - switch back to DCB with \"slot 16\"\n\n");
      rbuffer += stringf("DCB commands:\n");
      rbuffer += stringf("-------------\n");
      rbuffer += stringf("clkint               Switch bus clock to quartz\n");
      rbuffer += stringf("clkext               Switch bus clock to FCI input\n");
      rbuffer += stringf("delay <n>            Set SYNC delay\n");
      rbuffer += stringf("help                 This help page\n");
      rbuffer += stringf("info                 Show system information\n");
      rbuffer += stringf("reset                Reboot DCB\n");
      rbuffer += stringf("rr|regrd <ofs> [<n>] Read register\n");
      rbuffer += stringf("rw|regwr <ofs> <d>   Write register\n");
      rbuffer += stringf("rs|regset <ofs> <d>  Set bits of register\n");
      rbuffer += stringf("rc|regclr <ofs> <d>  Clear bits of register\n");
      rbuffer += stringf("regstore             Store registers in QSPI flash\n");
      rbuffer += stringf("regload              Load registers from QSPI flash\n");

      rbuffer += stringf("regdiff [-a][-r] [i|s|c [i|s|c]] [<ofs> [<n>]]\n");
      rbuffer += stringf("                     Compare control registers\n");
      rbuffer += stringf("      -a : show all registers, even when equal\n");
      rbuffer += stringf("      -r : show read-only registers when not equal\n");
      rbuffer += stringf("       i : initial register\n");
      rbuffer += stringf("       s : stored  register, default for left column\n");
      rbuffer += stringf("       c : current register, default for right column\n");
      rbuffer += stringf("   <ofs> : starting register, default: first ctrl reg\n");
      rbuffer += stringf("     <n> : number of registers, default 1 if <ofs> is specified, otherwise all\n\n");

      rbuffer += stringf("sysmon               Print system monitor info\n\n");

      rbuffer += stringf("upload <slot> [-f <path>] [-s <path>] [-t <type>] [-r <rev>]\n");
      rbuffer += stringf("  <slot>    : WDB/TCP slot, multiple slots possible separated by spaces,\n");
      rbuffer += stringf("                use \"*\" to upload all slots\n");
      rbuffer += stringf("  -f <path> : WDB/TCB firmware file (optional)\n");
      rbuffer += stringf("  -s <path> : WDB software file (optional)\n");
      rbuffer += stringf("  -t <type> : Board type \"wdb\" or \"tcb\", forces upload\n");
      rbuffer += stringf("  -r <rev>  : Board revision, \"f\", \"g\" for wdb, \"1\", \"2\" for tcb, forced upload\n");

      rbuffer += stringf("\n");

   } else if (strcmp(param[0], "clkint") == 0) {

      unsigned int data = (1 << DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS);
      unsigned int mask = DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK;
      reg_bank_mask_write(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, &data, &mask, 1);
      rbuffer += stringf("Set bus clock to internal 80 MHz quartz\n");

   } else if (strcmp(param[0], "clkext") == 0) {

      unsigned int data = (0 << DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS);
      unsigned int mask = DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK;
      reg_bank_mask_write(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, &data, &mask, 1);
      rbuffer += stringf("Set bus clock to external FCI connector input\n");

   } else if (strcmp(param[0], "delay") == 0) {

      if (n_param < 2) {
         rbuffer += stringf("Please specify delay value\n");
      } else {
         unsigned int d = atoi(param[1]);
         unsigned int data = (d << DCB_SYNC_DELAY_OFS);
         unsigned int mask = DCB_SYNC_DELAY_MASK;
         reg_bank_mask_write(DCB_SYNC_DELAY_REG, &data, &mask, 1);
         rbuffer += stringf("Set delay to %d\n", d);
      }

   } else if (strcmp(param[0], "info") == 0) {

      rbuffer += stringf("Version Information of DCB:\n\n");
      rbuffer += stringf("-- SW GIT Revision:       %s\n", GIT_REVISION);
      rbuffer += stringf("-- SW Build:              %s %s (UTC)\n\n",
                         __DATE__, __TIME__);

      rbuffer += stringf("-- Board Type:            DCB\n");

      unsigned int d;
      reg_bank_read(DCB_BOARD_REVISION_REG, &d, 1);
      d = (d & DCB_BOARD_REVISION_MASK) >> DCB_BOARD_REVISION_OFS;
      rbuffer += stringf("-- Board Revision:        %c\n", 'A' + d);

      reg_bank_read(DCB_BOARD_VARIANT_REG, &d, 1);
      d = (d & DCB_BOARD_VARIANT_MASK) >> DCB_BOARD_VARIANT_OFS;
      rbuffer += stringf("-- Board Variant:         0x%02X\n\n", d);

   } else if (strcmp(param[0], "rr") == 0 || strcmp(param[0], "regrd") == 0) {

      if (n_param < 2) {
         rbuffer += stringf("Error: please specify register offset\n");
         return;
      }

      int offset = strtoul(param[1], NULL, 0);
      int nr_of_regs = 1;

      if (n_param > 2)
         nr_of_regs = strtoul(param[2], NULL, 0);

      for (unsigned int i = 0; i < nr_of_regs; i++) {
         unsigned int data;
         reg_bank_read(offset + i * 4, &data, 1);
         rbuffer += stringf("[0x%04X]: 0x%08X\r\n", offset + i * 4, data);
      }

   } else if (strcmp(param[0], "rw") == 0 || strcmp(param[0], "regwr") == 0) {

      if (n_param < 3) {
         rbuffer += stringf("Error: please specify register offset and data\n");
         return;
      }

      unsigned int offset = strtoul(param[1], NULL, 0);
      unsigned int data = strtoul(param[2], NULL, 0);

      reg_bank_write(offset, &data, 1);
      rbuffer += stringf("[0x%04X]<=0x%08X\r\n", offset, data);

   } else if (strcmp(param[0], "rs") == 0 || strcmp(param[0], "regset") == 0) {

      if (n_param < 3) {
         rbuffer += stringf("Error: please specify register offset and data\n");
         return;
      }

      unsigned int offset = strtoul(param[1], NULL, 0);
      unsigned int data = strtoul(param[2], NULL, 0);

      reg_bank_set(offset, &data, 1);
      reg_bank_read(offset, &data, 1);
      rbuffer += stringf("[0x%04X]<=0x%08X\r\n", offset, data);

   } else if (strcmp(param[0], "rc") == 0 || strcmp(param[0], "regclr") == 0) {

      if (n_param < 3) {
         rbuffer += stringf("Error: please specify register offset and data\n");
         return;
      }

      unsigned int offset = strtoul(param[1], NULL, 0);
      unsigned int data = strtoul(param[2], NULL, 0);

      reg_bank_clr(offset, &data, 1);
      reg_bank_read(offset, &data, 1);
      rbuffer += stringf("[0x%04X]<=0x%08X\r\n", offset, data);

   } else if (strcmp(param[0], "regstore") == 0) {

      reg_bank_store();
      rbuffer += stringf("Registers stored in QSPI flash\n");

   } else if (strcmp(param[0], "regload") == 0) {

      reg_bank_load();
      rbuffer += stringf("Registers loaded from QSPI flash\n");

   } else if (strcmp(param[0], "regdiff") == 0) {

      reg_diff_cmd(n_param, (const char **) param, rbuffer);

   } else if (strcmp(param[0], "sysmon") == 0) {

      rbuffer += stringf("Temperature      T: %6.1lf   deg C\r\n",
                         sysmon_get_temp_mdeg(SYSPTR(sys_mon)) / 1000.0);
      rbuffer += stringf("System Monitor Vdd: %8.3lf V\r\n",
                         sysmon_get_vdd_mv(SYSPTR(sys_mon)) / 1000.0);
      rbuffer += stringf("Main Current     I: %8.3lf A\r\n",
                         sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN0) * 0.5);
      rbuffer += stringf("Voltage    V(5.0V): %8.3lf V\r\n",
                         sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN1) * 2.5);
      rbuffer += stringf("Voltage    V(3.3V): %8.3lf V\r\n",
                         sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN2) * 5.0 / 3.0);
      rbuffer += stringf("Voltage    V(2.5V): %8.3lf V\r\n",
                         sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN3) * 1.22);
      rbuffer += stringf("Voltage    V(2.0V): %8.3lf V\r\n",
                         sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN4) / 1000.0);
      rbuffer += stringf("Voltage    V(1.8V): %8.3lf V\r\n",
                         sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN5) / 1000.0);
      rbuffer += stringf("Voltage    V(1.5V): %8.3lf V\r\n",
                         sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN6) / 1000.0);
      rbuffer += stringf("Voltage    V(1.0V): %8.3lf V\r\n",
                         sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN7) / 1000.0);

   } else if (strcmp(param[0], "upload") == 0) {

      upload(n_param, (const char **) param, rbuffer);

   } else {
      rbuffer += stringf("Unknown command: %s\n", buffer);
   }

}

//-------------------------------------------------------------------

#define REGDIFF_CMP_INITIAL  0
#define REGDIFF_CMP_STORED   1
#define REGDIFF_CMP_CURRENT  2

#define REGDIFF_POS_A  24
#define REGDIFF_POS_B  45

#define REG_START   0x0000
#define REG_END     (REG_START + ((NR_OF_REGS-2)*4))

unsigned int regdiff_getreg(unsigned int reg, int sel) {
   unsigned int val;
   unsigned char flash_reg[4];
   qspi_flash_partition flash_partition;
   flash_partition_type *mtd_ptr;

   if (sel == REGDIFF_CMP_INITIAL) {
      val = reg_default[reg / 4];
   } else if (sel == REGDIFF_CMP_STORED) {
      if (!(mtd_ptr = get_flash_partition(get_flash_mem_map(BRD_TYPE_ID_DCB, DCB_BRD_REV_ID_B), "qspi-regcontent"))) {
         if (DBG_ERR)
            printf("Error: flash partitions for register content not found");
      }
      if (!(qspi_flash_init(&flash_partition, mtd_ptr->mtd_partition))) {
         if (DBG_ERR)
            printf("Error: register value flash partition accesse failed\n");
         return 0;
      }
      qspi_flash_read(&flash_partition, reg, sizeof(flash_reg), flash_reg);
      val = 0;
      for (int i = 3; i >= 0; i--) {
         val = val << 8;
         val |= flash_reg[i];
      }
   } else /* REGDIFF_CMP_CURRENT */
   {
      reg_bank_read(reg, &val, 1);
   }

   return val;
}

void reg_diff_cmd(int argc, const char **argv, std::string &rbuffer) {
   int ac = 0;
   int show_all = 0;
   int show_readonly = 0;
   int regcmp[2] = {REGDIFF_CMP_STORED, REGDIFF_CMP_CURRENT};
   int rc = 0;
   const char *rc_names[3] = {"initial", "stored", "current"};
   unsigned int reg_sel[2] = {REG_START, REG_END};
   unsigned int max_regs;
   unsigned int mask, reg, val_a, val_b;
   unsigned int rs = 0;
   int i, changed;
   char diff_line[REGDIFF_POS_B + 11];

   while (++ac < argc) {
      if (fstrcmp(argv[ac], "-a"))
         show_all = 1;
      else if (fstrcmp(argv[ac], "-r"))
         show_readonly = 1;
      else if (fstrcmp(argv[ac], "i") || fstrcmp(argv[ac], rc_names[REGDIFF_CMP_INITIAL]))
         regcmp[rc++ & 1] = REGDIFF_CMP_INITIAL;
      else if (fstrcmp(argv[ac], "s") || fstrcmp(argv[ac], rc_names[REGDIFF_CMP_STORED]))
         regcmp[rc++ & 1] = REGDIFF_CMP_STORED;
      else if (fstrcmp(argv[ac], "c") || fstrcmp(argv[ac], rc_names[REGDIFF_CMP_CURRENT]))
         regcmp[rc++ & 1] = REGDIFF_CMP_CURRENT;
      else if (isdigit(argv[ac][0]))
         reg_sel[rs++ & 1] = strtol(argv[ac], 0, 0);
   }

   /* check boundaries */
   if (reg_sel[0] < REG_START)
      reg_sel[0] = REG_START;
   if (reg_sel[0] > REG_END)
      reg_sel[0] = REG_END;
   if (rs == 1)
      reg_sel[1] = 1;
   else {
      max_regs = (((REG_END - reg_sel[0]) / 4) + 1);
      if (reg_sel[1] > max_regs) reg_sel[1] = max_regs;
   }

   for (i = 0; i < (REGDIFF_POS_B + 8); i++) diff_line[i] = ' ';
   diff_line[REGDIFF_POS_B + 8] = '\r';
   diff_line[REGDIFF_POS_B + 9] = '\n';
   diff_line[REGDIFF_POS_B + 10] = '\0';

   reg = reg_sel[0];
   for (rs = 0; rs < reg_sel[1]; rs++) {
      val_a = regdiff_getreg(reg, regcmp[0]);
      val_b = regdiff_getreg(reg, regcmp[1]);
      changed = (val_a != val_b);
      if ((changed && (!dcb_reg_list[reg / 4].read_only || show_readonly)) || show_all) {
         rbuffer += stringf("reg[0x%04x]  %7s: 0x%08x  %7s: 0x%08x  %s\r\n", reg, rc_names[regcmp[0]], val_a,
                            rc_names[regcmp[1]],
                            val_b, (changed && show_all) ? "!!!" : "");
         if (changed) {
            for (i = 0; i < 8; i++) {
               mask = 0xf0000000 >> (4 * i);

               if ((val_a & mask) == (val_b & mask)) {
                  diff_line[REGDIFF_POS_A + i] = '=';
                  diff_line[REGDIFF_POS_B + i] = '=';
               } else {
                  diff_line[REGDIFF_POS_A + i] = '^';
                  diff_line[REGDIFF_POS_B + i] = '^';
               }
            }
            rbuffer += std::string(diff_line);
         }
      }
      reg += 4;
   }
}

//-------------------------------------------------------------------

extern "C" { // make all library functions callable from C++

   // functions defined in drv_bpl.c
   extern flash_memory_map_type *connect_flash(unsigned int slot_nr, unsigned int board_type, unsigned int board_rev);
   extern void disconnect();
   extern void wr_fw(char *fw_file, flash_memory_map_type *flash_mem_map, const char *flash_partition_name);
   extern void wr_sw(char *sw_file, flash_memory_map_type *flash_mem_map, const char *flash_partition_name);

}

void slot_upload(unsigned int slot_nr, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p,
                       unsigned int board_type, unsigned int board_rev) {
   char fw_def_path[250];
   char sw_def_path[250];
   char *fwp;
   char *swp;

   flash_memory_map_type *flash_mem_map = NULL;

   if (fw_spec_p)
      fwp = fw_spec_p;
   else
      fwp = fw_def_path;

   if (sw_spec_p)
      swp = sw_spec_p;
   else
      swp = sw_def_path;

   if (DBG_INF0)
      printf("\nSlot %d:\n", slot_nr);

   if (flash_mem_map = connect_flash(slot_nr, board_type, board_rev)) {
      if (DBG_INF0)
         printf("default path: %s\n", flash_mem_map->default_fw_path);
   } else {
      if (DBG_ERR)
         printf("Error: flash memory map not found (type %d, revision %d)\n", board_type, board_rev);
      return;
   }

   if (strstr(flash_mem_map->default_fw_path, "/wdb/")) {
      /* WDB */
      if (load_fw) {
         if (!fw_spec_p) {
            /* set default path according to type and revision */
            strcpy(fwp, flash_mem_map->default_fw_path);
            strcpy(&fwp[strlen(flash_mem_map->default_fw_path)], wdb_fw_default_file);
         }
         /* upload firmware */
         if (DBG_INF0) printf("-> Uploading WDB firmware %s\n", fwp);
         wr_fw(fwp, flash_mem_map, "fw");
      }
      if (load_sw) {
         if (!sw_spec_p) {
            /* set default path according to type and revision */
            strcpy(swp, flash_mem_map->default_fw_path);
            strcpy(&swp[strlen(flash_mem_map->default_fw_path)], wdb_sw_default_file);
         }
         /* upload sofware */
         if (DBG_INF0) printf("-> Uploading WDB software %s\n", swp);
         wr_sw(swp, flash_mem_map, "sw");
      }
   } else if (strstr(flash_mem_map->default_fw_path, "/tcb/")) {
      /* TCB */
      if (load_fw) {
         if (!fw_spec_p) {
            /* set default path according to type and revision */
            strcpy(fwp, flash_mem_map->default_fw_path);
            strcpy(&fwp[strlen(flash_mem_map->default_fw_path)], tcb_fw_default_file);
         }
         /* upload firmware */
         if (DBG_INF0) printf("-> Uploading TCB firmware %s\n", fwp);
         wr_fw(fwp, flash_mem_map, "fw");
      }
   }

   disconnect();

   if (DBG_INF0) printf("\n");
}

//-------------------------------------------------------------------

void crate_upload(int slot[WDAQ_N_SLOTS], int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p,
                        unsigned int board_type, unsigned int board_rev, unsigned int force) {
   int i;
   WDAQ_BRD slot_board_info;

   for (i = 0; i < WDAQ_N_SLOTS;  i++) {
      if (slot[i] && i != WDAQ_SLOT_DCB) {
         if (DBG_INF0) {
            if (force)
               printf("FORCED upload\n");
            else
               printf("Standard upload\n");
         }
         if (get_slot_board_info(i, &slot_board_info)) {
            if (force) {
               /* get forced upload information */
               if ((board_type != slot_board_info.type_id) || (board_rev != slot_board_info.rev_id)) {
                  if (DBG_ERR)
                     printf("Error: present board in slot %d does not match type and revision\n", i);
                  continue;
               }
            }
         } else {
            if (force) {
               slot_board_info.type_id = board_type;
               slot_board_info.rev_id = board_rev;
            } else {
               /* no slot board information for standard upload */
               if (DBG_ERR)
                  printf("Error: board information for slot %d could not be read\n", i);
               return;
            }
         }

         slot_upload(i, load_fw, fw_spec_p, load_sw, sw_spec_p, slot_board_info.type_id, slot_board_info.rev_id);
      }
   }
}

//-------------------------------------------------------------------

void upload(int n_param, const char **param, std::string &rbuffer) {
   int slot_sel[18];
   int load_fw = 0;
   int load_sw = 0;
   char fwp[256];
   char swp[256];
   WDAQ_BRD board_info;
   unsigned int board_type = 0;
   unsigned int board_rev = 0;
   unsigned int t_force = 0;
   unsigned int r_force = 0;

   // decode slots
   for (int i = 0; i < WDAQ_N_SLOTS; i++)
      slot_sel[i] = 0;
   for (int i = 1; i < n_param; i++) {
      if (isdigit(param[i][0])) {
         if (strchr(param[i], '-')) {
            int s1 = atoi(param[i]);
            int s2 = atoi(strchr(param[i], '-') + 1);
            for (int s = s1; s <= s2; s++)
               if (s >= 0 && s < WDAQ_N_SLOTS)
                  slot_sel[s] = 1;
         } else {
            int s = atoi(param[i]);
            if (s >= 0 && s < WDAQ_N_SLOTS)
               slot_sel[s] = 1;
         }
      } else if (param[i][0] == '*') {
         for (int s = 0; s < WDAQ_N_SLOTS; s++)
            slot_sel[s] = 1;
      }
   }

   // decode flags
   for (int i = 1; i < n_param; i++) {

      if (param[i][0] == '-' && param[i][1] == 'f') {
         if (++i < n_param) {
            rbuffer = "Missing firmware file with \"-f\" option\n";
            return;
         }
         if (!is_file(param[i])) {
            rbuffer = stringf("Firmware file \"%s\" not found\n", param[i]);
            return;
         } else {
            strncpy(fwp, param[i], sizeof(fwp));
         }
         load_fw = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 's') {
         if (++i < n_param) {
            rbuffer = "Missing software file with \"-s\" option\n";
            return;
         }
         if (!is_file(param[i])) {
            rbuffer = stringf("Software file \"%s\" not found\n", param[i]);
            return;
         } else {
            strncpy(swp, param[i], sizeof(swp));
         }
         load_sw = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 't') {
         if (++i < n_param) {
            rbuffer = "Missing board type with \"-t\" option\n";
            return;
         }
         if (strcmp(param[i], "wdb") == 0) {
            board_type = BRD_TYPE_ID_WDB;
         } else if (strcmp(param[i], "tcb") == 0) {
            board_type = BRD_TYPE_ID_TCB;
         } else {
            rbuffer = "Unknown board type with \"-t\" option, must be \"wdb\" or \"tcb\"\n";
            return;
         }
         t_force = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 'r') {
         if (++i < n_param) {
            rbuffer = "Missing board revision with \"-r\" option\n";
            return;
         }
         if (param[i][0] >= '0' && param[i][0] <= '9') {
            board_rev = strtoul(param[i], NULL, 0);
         } else if (param[i][0] >= 'a' && param[i][0] <= 'z') {
            board_rev = param[i][0] - 'a';
         } else if (param[i][0] >= 'A' && param[i][0] <= 'Z') {
            board_rev = param[i][0] - 'A';
         } else {
            rbuffer = "Invalid board revision, must be 0-9 or a-z\n";
            return;
         }
         r_force = 1;
      }

      else {
         rbuffer = stringf("Invalid option \"%s\"\n\n", param[i]);
         return;
      }
   }

   if (load_fw == 0 && load_sw == 0) {
      load_fw = 1;
      load_sw = 1;
   }

   if (t_force && r_force) {
      /* forced upload */
      crate_upload(slot_sel, load_fw, fwp, load_sw, swp, board_type, board_rev, 1);
   } else {
      /* standard upload */
      crate_upload(slot_sel, load_fw, fwp, load_sw, swp, board_type, board_rev, 0);
   }

   return;
}
