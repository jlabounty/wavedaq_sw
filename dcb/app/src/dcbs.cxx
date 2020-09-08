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
#include <cstddef>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/udp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "git-revision.h"

extern "C" { // make all library functions callable from C++

#include "drv_axi_dcb_reg_bank.h"
#include "register_map_dcb.h"
#include "update_config.h"
#include "drv_bpl.h"
#include "drv_tcb.h"
#include "dbg.h"
#include "system.h"
#include "sc_io.h"
#include "wdaq_board_id.h"
#include "drv_qspi_flash.h"
#include "flash_memory_maps.h"
#include "xilinx_cfg.h"

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

class udp_connection {
public:
   int sock;
   int slot;
   int verbose;
   int percent;
   int erase;
   int show_default;
   time_t last;
   struct sockaddr client_address;
   unsigned char client_macaddr[6];
   std::string rb;

   udp_connection(int so, int sl) { sock = so; slot = sl; verbose = 0; show_default = 0; }
   void clear() { rb = ""; }
   void send(std::string s) { rb += s; }
   void sprintf(const char *fmt, ...);
   void flush();
};

void udp_connection::flush() {
   int i;
   int n = rb.length() + 1;

   // chop data in chunks of 1000 bytes to fit in UDP packets
   for (const char *p = rb.c_str(); n > 0; n -= i, p += i)
      i = sendto(sock, p, std::min(1000, n), 0,
                 &client_address,
                 sizeof(struct sockaddr));

   rb = "";
}

void udp_connection::sprintf(const char *fmt, ...) {
   char *ret;
   va_list ap;

   va_start(ap, fmt);
   vasprintf(&ret, fmt, ap);
   va_end(ap);

   std::string str(ret);
   free(ret);
   rb += str;
}

//-------------------------------------------------------------------

void print_buffer(const char *buffer, int len);
void process_dcb_command(udp_connection &c, char *buffer);
void reg_diff_cmd(udp_connection &c, int argc, const char **argv);
void upload(udp_connection &c, int argc, const char **param);
void init_reg_settings(udp_connection &c, int snr);

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
         } else {
            // check for empty board
            status = is_flash_available(slot);
            if (status == 1) {
               b += stringf("Slot %2d: Found un-programmed board\n", slot);
            }
         }
      }
   }
}

//-------------------------------------------------------------------

int main(int argc, char *argv[]) {

   int verbose = 0;
   int daemon = 0;
   char hostname[256], mac[256];
   int sock_bin, sock_asc, sock_raw;
   int board_type = 0;
   int board_revision = 0;
   std::map <std::string, udp_connection *> connection;

   // check structure packing
   if (sizeof(qspi_flash_partition) != 40) {
      printf("Error: structure packing is wrong, please remove \"#pragma pack\" in any header file\n");
      exit(0);
   }

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

   //array to store client mac address
   unsigned char client_macaddr[6];

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

         if (ip->protocol == IPPROTO_UDP && (ntohs(udp->dest) == SERVER_PORT_BIN || ntohs(udp->dest) == SERVER_PORT_ASC)) {
            memset(&client_address, 0, sizeof(client_address));
            client_address.sin_addr.s_addr = ip->saddr;
            for(int i=0; i<6; i++) client_macaddr[i] = eth->h_source[i];
            memcpy(&client_macaddr, &eth->h_source, sizeof(client_macaddr));

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
         if (connection.find(addr) == connection.end()) {
            connection[addr] = new udp_connection(sock_asc, WDAQ_SLOT_DCB); // Default is DCB slot
         }
         connection[addr]->last = time(0);

         // store connection specific parameters
         memcpy(&connection[addr]->client_address, &client_address, sizeof(client_address));
         memcpy(&connection[addr]->client_macaddr, &client_macaddr, sizeof(client_macaddr));
         connection[addr]->rb   = "";

         // clean up connection map
         for (auto &c: connection) {
            if (time(0) > c.second->last + 10) {
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

         if (strncmp(buffer, "slot", 4) == 0 || strncmp(buffer, "s ", 2) == 0 || strcmp(buffer, "s") == 0) {

            int slot = WDAQ_SLOT_DCB;
            if (strchr(buffer, ' '))
               slot = strtol(strchr(buffer, ' '), 0, 0);

            if (slot == WDAQ_SLOT_DCB) {
               connection[addr]->slot = slot;
            } else {
               int status = get_slot_board_info(slot, &board[slot]);
               if (status && board[slot].type_id <= BRD_TYPE_ID_MAX &&
                   board[slot].vendor_id <= BRD_VENDOR_ID_MAX) {
                  connection[addr]->slot = slot;
                  if (verbose)
                     printf("Switched to slot #%d\n", connection[addr]->slot);
               } else {
                  connection[addr]->sprintf("No board present in slot %d\n", slot);
               }
            }

         } else if (strncmp(buffer, "scan", 4) == 0) {

            printf_crate_scan(hostname, connection[addr]->rb);

         } else if (connection[addr]->slot != WDAQ_SLOT_DCB) { //---- Send to slot via SPI -----------

            // send ASCII command to WDB via SPI

            if (verbose)
               printf("WDB command found for slot %d\n", connection[addr]->slot);

            if (verbose)
               printf("TX: %s\n", buffer);

            char rb[10000];
            spi_ascii_cmd(buffer, rb, sizeof(rb), connection[addr]->slot,
                          board[connection[addr]->slot].type_id, board[connection[addr]->slot].rev_id);

            if (verbose)
               printf("RX: %s\n\n", rb);

            connection[addr]->rb += std::string(rb);

         } else if (strncmp(buffer, "reset", 5) == 0) { //---- Process command locally --------------

            const char *str = "Rebooting...\n\n";
            sendto(sock_asc, str, strlen(str) + 1, 0, (struct sockaddr *) &client_address,
                   sizeof(client_address));
            system("reboot");
            exit(0);

         } else
            // process DCB command locally
            process_dcb_command(*connection[addr], buffer);

         // add prompt
         if (connection[addr]->slot == WDAQ_SLOT_DCB)
            connection[addr]->sprintf("%s> ", hostname);
         else
            connection[addr]->sprintf("%s:%02d> ", hostname, connection[addr]->slot);

         // send data back to client
         connection[addr]->flush();

      } // ASCII

      //check for TCB data
      if(hasTcbDataDestination()){
         for (int slot = 0; slot < WDAQ_N_SLOTS; slot++) {
            if(board[slot].type_id==BRD_TYPE_ID_TCB){
               if(hasData(slot, board + slot))
                  processData(slot, board + slot);
            }
         }
      }

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

void process_dcb_command(udp_connection &c, char *buffer) {

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

      c.sprintf("\nCrate commands:\n");
      c.sprintf("---------------\n");
      c.sprintf("scan                 Scan crate for boards\n");
      c.sprintf("slot|s <n>           Seclect slot (%d=DCB)\n", WDAQ_SLOT_DCB);
      c.sprintf("   - all further commands will then be sent to slot <n>\n");
      c.sprintf("   - switch back to DCB with \"slot 16\"\n\n");
      c.sprintf("DCB commands:\n");
      c.sprintf("-------------\n");
      c.sprintf("cfgdst <port> [<ip>] Configure destination address for UDP packets\n");
      c.sprintf("clkint               Switch bus clock to quartz\n");
      c.sprintf("clkext               Switch bus clock to FCI input\n");
      c.sprintf("delay <n>            Set SYNC delay\n");
      c.sprintf("help                 This help page\n");
      c.sprintf("info                 Show system information\n");
      c.sprintf("init <serial>        Initialize DCB environment variables\n");
      c.sprintf("mark                 Mark board by letting led blink magenta\n");
      c.sprintf("unmark               Remove marking\n");
      c.sprintf("reset                Reboot DCB\n");
      c.sprintf("rr|regrd <ofs> [<n>] Read register\n");
      c.sprintf("rw|regwr <ofs> <d>   Write register\n");
      c.sprintf("rs|regset <ofs> <d>  Set bits of register\n");
      c.sprintf("rc|regclr <ofs> <d>  Clear bits of register\n");
      c.sprintf("regstore             Store registers in QSPI flash\n");
      c.sprintf("regload              Load registers from QSPI flash\n");

      c.sprintf("regdiff [-a][-r] [i|s|c [i|s|c]] [<ofs> [<n>]]\n");
      c.sprintf("                     Compare control registers\n");
      c.sprintf("      -a : show all registers, even when equal\n");
      c.sprintf("      -r : show read-only registers when not equal\n");
      c.sprintf("       i : initial register\n");
      c.sprintf("       s : stored  register, default for left column\n");
      c.sprintf("       c : current register, default for right column\n");
      c.sprintf("   <ofs> : starting register, default: first ctrl reg\n");
      c.sprintf("     <n> : number of registers, default 1 if <ofs> is specified, otherwise all\n\n");

      c.sprintf("sinit  <slot>        Send init to WDB/TCB via backplane\n\n");
      c.sprintf("sysmon               Print system monitor info\n\n");

      c.sprintf("upload <slot> [-f <path>] [-s <path>] [-t <type>] [-r <rev>]\n");
      c.sprintf("  <slot>    : WDB slot, multiple slots possible separated by spaces,\n");
      c.sprintf("                use \"*\" to upload all slots 0-15 (if boards are present)\n");
      c.sprintf("                use \"17\" to upload firmware for TCB\n");
      c.sprintf("  -f <path> : WDB/TCB firmware file (optional)\n");
      c.sprintf("  -s <path> : WDB software file (optional)\n");
      c.sprintf("  -t <type> : Board type \"wdb\" or \"tcb\", forces upload\n");
      c.sprintf("  -r <rev>  : Board revision, \"f\", \"g\" for wdb, \"1\", \"2\" for tcb, forced upload\n");
      c.sprintf("         -d : Show default firmware and software files\n");
      c.sprintf("         -p : Show only percent value of upload\n");
      c.sprintf("         -e : Only erase flash, do not program\n");
      c.sprintf("         -v : Verbose output\n");

      c.sprintf("\n");

   } else if (strcmp(param[0], "clkint") == 0) {

      unsigned int data = (1 << DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS);
      unsigned int mask = DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK;
      reg_bank_mask_write(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, &data, &mask, 1);
      c.sprintf("Set bus clock to internal 80 MHz quartz\n");

   } else if (strcmp(param[0], "clkext") == 0) {

      unsigned int data = (0 << DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS);
      unsigned int mask = DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK;
      reg_bank_mask_write(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, &data, &mask, 1);
      c.sprintf("Set bus clock to external FCI connector input\n");

   } else if (strcmp(param[0], "delay") == 0) {

      if (n_param < 2) {
         c.sprintf("Please specify delay value\n");
      } else {
         unsigned int d = atoi(param[1]);
         unsigned int data = (d << DCB_SYNC_DELAY_OFS);
         unsigned int mask = DCB_SYNC_DELAY_MASK;
         reg_bank_mask_write(DCB_SYNC_DELAY_REG, &data, &mask, 1);
         c.sprintf("Set delay to %d\n", d);
      }

   } else if (strcmp(param[0], "info") == 0) {

      c.sprintf("Version Information of DCB:\n\n");
      c.sprintf("-- SW GIT Revision:       %s\n", GIT_REVISION);
      c.sprintf("-- SW Build:              %s %s (UTC)\n\n",
                         __DATE__, __TIME__);

      c.sprintf("-- Board Type:            DCB\n");

      unsigned int d;
      reg_bank_read(DCB_BOARD_REVISION_REG, &d, 1);
      d = (d & DCB_BOARD_REVISION_MASK) >> DCB_BOARD_REVISION_OFS;
      c.sprintf("-- Board Revision:        %c\n", 'A' + d);

      reg_bank_read(DCB_BOARD_VARIANT_REG, &d, 1);
      d = (d & DCB_BOARD_VARIANT_MASK) >> DCB_BOARD_VARIANT_OFS;
      c.sprintf("-- Board Variant:         0x%02X\n\n", d);

   } else if (strcmp(param[0], "init") == 0) {

      if (n_param < 2) {
         c.sprintf("Error: please specify serial number\n");
         return;
      }

      int serial = atoi(param[1]);
      init_reg_settings(c, serial);
      c.sprintf("\nInitialization of DCB%02d complete\n", serial);

   } else if (strcmp(param[0], "mark") == 0) {

      emio_set_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_PIN);
      c.sprintf("Turned LED blinking on\n");

   } else if (strcmp(param[0], "unmark") == 0) {

      emio_clr_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_PIN);
      c.sprintf("Turned LED blinking off\n");

   } else if (strcmp(param[0], "rr") == 0 || strcmp(param[0], "regrd") == 0) {

      if (n_param < 2) {
         c.sprintf("Error: please specify register offset\n");
         return;
      }

      int offset = strtoul(param[1], NULL, 0);
      int nr_of_regs = 1;

      if (n_param > 2)
         nr_of_regs = strtoul(param[2], NULL, 0);

      for (unsigned int i = 0; i < nr_of_regs; i++) {
         unsigned int data;
         reg_bank_read(offset + i * 4, &data, 1);
         c.sprintf("[0x%04X]: 0x%08X\r\n", offset + i * 4, data);
      }

   } else if (strcmp(param[0], "rw") == 0 || strcmp(param[0], "regwr") == 0) {

      if (n_param < 3) {
         c.sprintf("Error: please specify register offset and data\n");
         return;
      }

      unsigned int offset = strtoul(param[1], NULL, 0);
      unsigned int data = strtoul(param[2], NULL, 0);

      reg_bank_write(offset, &data, 1);
      c.sprintf("[0x%04X]<=0x%08X\r\n", offset, data);

   } else if (strcmp(param[0], "rs") == 0 || strcmp(param[0], "regset") == 0) {

      if (n_param < 3) {
         c.sprintf("Error: please specify register offset and data\n");
         return;
      }

      unsigned int offset = strtoul(param[1], NULL, 0);
      unsigned int data = strtoul(param[2], NULL, 0);

      reg_bank_set(offset, &data, 1);
      reg_bank_read(offset, &data, 1);
      c.sprintf("[0x%04X]<=0x%08X\r\n", offset, data);

   } else if (strcmp(param[0], "rc") == 0 || strcmp(param[0], "regclr") == 0) {

      if (n_param < 3) {
         c.sprintf("Error: please specify register offset and data\n");
         return;
      }

      unsigned int offset = strtoul(param[1], NULL, 0);
      unsigned int data = strtoul(param[2], NULL, 0);

      reg_bank_clr(offset, &data, 1);
      reg_bank_read(offset, &data, 1);
      c.sprintf("[0x%04X]<=0x%08X\r\n", offset, data);

   } else if (strcmp(param[0], "regstore") == 0) {

      reg_bank_store();
      c.sprintf("Registers stored in QSPI flash\n");

   } else if (strcmp(param[0], "regload") == 0) {

      reg_bank_load();
      c.sprintf("Registers loaded from QSPI flash\n");

   } else if (strcmp(param[0], "regdiff") == 0) {

      reg_diff_cmd(c, n_param, (const char **) param);

   } else if (strcmp(param[0], "sinit") == 0) {

      if (n_param < 2) {
         c.sprintf("Error: please specify slot number\n");
         return;
      }

      int slot = atoi(param[1]);
      if (slot >= 0 && slot <= 17 && slot != 16) {
         init_slot(slot, 1);
         c.sprintf("INIT sent to slot %d\n", slot);
      } else
         c.sprintf("Invalid slot number %d\n", slot);

   } else if (strcmp(param[0], "sysmon") == 0) {

      c.sprintf("Temperature      T: %6.1lf   deg C\r\n", sysmon_get_temp_mdeg(SYSPTR(sys_mon)) / 1000.0);
      c.sprintf("System Monitor Vdd: %8.3lf V\r\n", sysmon_get_vdd_mv(SYSPTR(sys_mon)) / 1000.0);
      c.sprintf("Main Current     I: %8.3lf A\r\n", sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN0) * 0.5);
      c.sprintf("Voltage    V(5.0V): %8.3lf V\r\n", sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN1) * 2.5);
      c.sprintf("Voltage    V(3.3V): %8.3lf V\r\n", sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN2) * 5.0 / 3.0);
      c.sprintf("Voltage    V(2.5V): %8.3lf V\r\n", sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN3) * 1.22);
      c.sprintf("Voltage    V(2.0V): %8.3lf V\r\n", sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN4) / 1000.0);
      c.sprintf("Voltage    V(1.8V): %8.3lf V\r\n", sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN5) / 1000.0);
      c.sprintf("Voltage    V(1.5V): %8.3lf V\r\n", sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN6) / 1000.0);
      c.sprintf("Voltage    V(1.0V): %8.3lf V\r\n", sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN7) / 1000.0);

   } else if (strcmp(param[0], "upload") == 0 || strcmp(param[0], "up") == 0) {

      upload(c, n_param, (const char **) param);

   } else if (strcmp(param[0], "cfgdst") == 0) {
      char *dest_addr;
      int dest_port;

      if (n_param == 2) {
         // get ip addr from udp packet
         dest_port = atoi(param[1]);
         sockaddr_in *ptr = (sockaddr_in *) &c.client_address;
         dest_addr = inet_ntoa(ptr->sin_addr);
      } else if (n_param > 2) {
         // ip addr given
         dest_port = atoi(param[1]);
         dest_addr = param[2];
      } else {
         c.sprintf("Please use this format \"cfgdst <port number> [<ip>]\"\n");
         return;
      }

      c.sprintf("Setting data destination to %s port %d\n", dest_addr, dest_port);

      // notify tcb readout driver of the new port and ip
      setTcbDataDestination(dest_addr, dest_port);

      // TEMPORARY until serial links work
      // configure destination of all WDBs
      char cmdbuf[64];
      sprintf(cmdbuf, "cfgdst %d %s %02X:%02X:%02X:%02X:%02X:%02X\n", dest_port, dest_addr,
              c.client_macaddr[0], c.client_macaddr[1], c.client_macaddr[2],
              c.client_macaddr[3], c.client_macaddr[4], c.client_macaddr[5]);

      for (int slot = 0; slot < WDAQ_N_SLOTS; slot++) {
         if(board[slot].type_id == BRD_TYPE_ID_WDB){
            spi_ascii_cmd(cmdbuf, 0, 0, slot,
                          board[slot].type_id, board[slot].rev_id);
         }
      }

   } else {
      c.sprintf("Unknown command: %s\n", buffer);
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

void reg_diff_cmd(udp_connection &c, int argc, const char **argv) {
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
         c.sprintf("reg[0x%04x]  %7s: 0x%08x  %7s: 0x%08x  %s\r\n", reg, rc_names[regcmp[0]], val_a,
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
            c.send(diff_line);
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

}

#define FLASH_BUF_SIZE      8192 // 8k 
#define PROG_BAR_ITEMS        40

// block chars, see https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
#define PROG_BAR_DEL_CHAR  "\033[48;5;7m \033[0m"  // grey
#define PROG_BAR_FW_CHAR   "\033[48;5;2m \033[0m"  // green
#define PROG_BAR_SW_CHAR   "\033[48;5;2m \033[0m"  // green
#define PROG_BAR_REB_CHAR  "\033[48;5;8m \033[0m"  // dark grey

//-------------------------------------------------------------------

void show_progress(udp_connection &c, int item, const char* prefix, double percent,
                   const char *idle_char, const char *prog_char)
{
   int i;
   double titem[] = { 0, 0.38, 0.62, 0.85, 0.92, 1};

   if (c.percent) {
      percent = titem[item]*100 + (titem[item+1]-titem[item]) * percent;
      c.sprintf("%5.1lf\n", percent);
      c.flush();
   } else {
      c.sprintf("\r"); // Send carriage return without newline
      if (prefix)
         c.sprintf("%s", prefix);
      c.sprintf("[");
      for (i = 0; i < PROG_BAR_ITEMS; i++) {
         if ((i * (100.0 / PROG_BAR_ITEMS)) <= percent)
            c.sprintf("%s", prog_char);
         else
            c.sprintf("%s", idle_char);
      }
      c.sprintf("] %5.1lf%%  ", percent);
      c.flush();
   }
}

//-------------------------------------------------------------------

void write_fw(udp_connection &c, int slot, char *fw_file, 
              flash_memory_map_type *flash_mem_map, const char *flash_partition_name)
{
   int header_len;
   unsigned int len;
   bitfile_info_type bit_inf;
   bitfile_info_type bit_inf_swapped;
   qspi_flash_partition flash_partition;
   flash_partition_type *mtd_ptr = NULL;
   int fd;
   unsigned int   ers_size;
   unsigned int   tot_ers_size;
   unsigned int   flash_offs;
   unsigned int   flash_len;
   unsigned char  buff[FLASH_BUF_SIZE];
   int i;

   /* open bitfile */
   fd = open(fw_file, O_RDONLY);

   /* return if no valid file */
   if(!fd) {
      c.sprintf("Error: cannot find firmware file \"%s\"", fw_file);
      return;
   }

   /* check flash partition */
   if( !(mtd_ptr = get_flash_partition(flash_mem_map, flash_partition_name)) )
   {
      c.sprintf("Error: partition %s not found\n", flash_partition_name);
      return;
   }

   if( !(qspi_flash_init(&flash_partition, mtd_ptr->mtd_partition)) )
   {
      c.sprintf("Error: flash partition %s accesse failed\n", flash_partition_name);
      return;
   }

   /* parse header for flash */
   len = read(fd, buff, 1024);
   header_len = parse_bitfile(buff, len, &bit_inf);

   /* Check FPGA (local header) */
   if (header_len > 0)
   {
      /* got valid header */
      if(c.verbose) {
         c.sprintf("Bit file header:\n");
         for (i=0; i<4; i++)
            c.sprintf("%-10s : %s\r\n", info_field_name[i], buff + bit_inf.field[i]);
         c.sprintf("Image size : %d Bytes\r\n", bit_inf.info.data_len);
         c.flush();
      }
      byte_swap_uint32(bit_inf.field, bit_inf_swapped.field, sizeof(bit_inf)/sizeof(unsigned int));

      /* check fpga type */
      if(flash_mem_map->fpga_type) {
         len = bit_inf.info.date_offs - bit_inf.info.fpga_offs;
         if (strncmp(flash_mem_map->fpga_type, (const char*) buff + bit_inf.info.fpga_offs, len) != 0)          {
            c.sprintf("Warning: Bitfile for wrong FPGA type: %s  expected: %s\r\n", buff + bit_inf.info.fpga_offs, flash_mem_map->fpga_type);
            return;
         }
      }

      /* Erase header */
      if(c.verbose)
         c.sprintf("Deleting header ... ");
      c.flush();
      qspi_flash_erase_sector(&flash_partition, mtd_ptr->header_offset);
      if(c.verbose)
         c.sprintf("done\n");
      c.flush();

      /* Erase bitfile only */
      ers_size = 0;
      tot_ers_size=0;
      char str[80];
      sprintf(str, "Slot %2d: Deleting firmware ", slot);
      while(tot_ers_size<bit_inf.info.data_len) {
         ers_size = qspi_flash_erase_sector(&flash_partition, tot_ers_size);
         tot_ers_size += ers_size;
         if(tot_ers_size>bit_inf.info.data_len) tot_ers_size = bit_inf.info.data_len; /* Keep progress bar <= 100% */
         show_progress(c, 0, str, 100.0 * tot_ers_size/bit_inf.info.data_len,
                       " ", PROG_BAR_DEL_CHAR);
      }

      if (!c.erase) {
         /* write bitfile excluding header */
         lseek(fd, header_len, SEEK_SET); /* go back to start of file */
         flash_offs = 0;
         flash_len  = FLASH_BUF_SIZE;
         sprintf(str, "Slot %2d: Writing firmware  ", slot);
         while(flash_len == FLASH_BUF_SIZE) {
            flash_len = read(fd, buff, FLASH_BUF_SIZE);
            qspi_flash_write(&flash_partition, flash_offs, flash_len, buff);
            flash_offs += flash_len;
            show_progress(c, 1, str, 100.0 * flash_offs/bit_inf.info.data_len,
                          PROG_BAR_DEL_CHAR, PROG_BAR_FW_CHAR);
         }
         if (!c.percent) {
            c.sprintf("\n");
            c.flush();
         }

         /* write header */
         lseek(fd, 0, SEEK_SET); // go back to start of file

         if(mtd_ptr->header_offset) { // check if header has to be written
            if(c.verbose)
               c.sprintf("Writing header ... ");
            c.flush();
            flash_offs = mtd_ptr->header_offset;
            flash_len  = sizeof(bitfile_info_type);
            qspi_flash_write(&flash_partition, flash_offs, flash_len, (unsigned char*) &bit_inf_swapped);
            flash_offs += flash_len;
            flash_len   = header_len;
            read(fd, buff, flash_len);
            qspi_flash_write(&flash_partition, flash_offs, flash_len, buff);
            if(c.verbose)
               c.sprintf("done\n");
            c.flush();
         }
      }
   }

   fsync(fd); // flush caches to make sure operation completes before de-selecting board
   if(close(fd) < 0)
      c.sprintf("Error closing file\n");
}

//-------------------------------------------------------------------

void write_sw(udp_connection &c, int slot, char *sw_file, 
              flash_memory_map_type *flash_mem_map, const char *flash_partition_name)
{
   int header_len;
   unsigned int len;
   sw_file_info_type sw_info;
   sw_file_info_type sw_info_swapped;
   qspi_flash_partition flash_partition;
   flash_partition_type *mtd_ptr = NULL;
   int fd;
   unsigned int   ers_size;
   unsigned int   tot_ers_size;
   unsigned int   flash_offs;
   unsigned int   flash_len;
   unsigned char  buff[FLASH_BUF_SIZE];
   unsigned char sr_header_buf[SREC_MAX_BYTES];
   struct stat file_stat;
   int i;

   /* open bitfile */
   fd = open(sw_file, O_RDONLY);

   /* return if no valid file */
   if(!fd) {
      c.sprintf("Error: cannot find firmware file \"%s\"", sw_file);
      return;
   }

   stat(sw_file, &file_stat);

   /* check flash partition */
   if (!(mtd_ptr = get_flash_partition(flash_mem_map, flash_partition_name))) {
      c.sprintf("Error: partition %s not found\n", flash_partition_name);
      return;
   }

   if (!(qspi_flash_init(&flash_partition, mtd_ptr->mtd_partition))) {
      c.sprintf("Error: flash partition %s accesse failed\n", flash_partition_name);
      return;
   }

   /* parse header for flash */
   len = read(fd, buff, SREC_MAX_BYTES);
   header_len = parse_srec(buff, sr_header_buf);

   /* Check FPGA (local header) */
   if (header_len > 0) {
      /* got valid header */
      if (!c.percent) {
         if (c.verbose)
            c.sprintf("SREC header: %s\n", sr_header_buf);
         c.flush();
      }

      /* Erase partition */
      ers_size = 0;
      tot_ers_size = 0;
      char str[80];
      sprintf(str, "Slot %2d: Deleting software ", slot);
      while (tot_ers_size < flash_partition.mtd_info.size) {
         ers_size = qspi_flash_erase_sector(&flash_partition, tot_ers_size);
         tot_ers_size += ers_size;
         show_progress(c, 2, str, 100.0 * tot_ers_size / flash_partition.mtd_info.size,
           " ", PROG_BAR_DEL_CHAR);
      }

      if (!c.erase) {
         /* write bitfile excluding header */
         lseek(fd, 0, SEEK_SET); /* go back to start of file */
         flash_len = FLASH_BUF_SIZE;
         flash_offs = 0;
         sprintf(str, "Slot %2d: Writing software  ", slot);
         while (flash_len == FLASH_BUF_SIZE) {
            flash_len = read(fd, buff, FLASH_BUF_SIZE);
            qspi_flash_write(&flash_partition, flash_offs, flash_len, buff);
            flash_offs += flash_len;
            show_progress(c, 3, str, 100.0 * flash_offs / file_stat.st_size,
                          PROG_BAR_DEL_CHAR, PROG_BAR_SW_CHAR);
         }
         if (!c.percent) {
            c.sprintf("\n");
            c.flush();
         }

         /* write header part 1 (info) */
         if (c.verbose)
            c.sprintf("Writing header info ... ");
         c.flush();
         sw_info.info.name_offs = sizeof(sw_file_info_type);
         sw_info.info.data_len = file_stat.st_size;
         sw_info.info.head_len = header_len;
         sw_info.info.checksum = sw_file_info_checksum(&sw_info);
         byte_swap_uint32(sw_info.field, sw_info_swapped.field, sizeof(sw_info)/sizeof(unsigned int));
         flash_offs = mtd_ptr->header_offset;
         flash_len = sizeof(sw_file_info_type);
         qspi_flash_write(&flash_partition, flash_offs, flash_len, (unsigned char *) &sw_info_swapped);
         if (c.verbose)
            c.sprintf("done\n");
         c.flush();

         /* write header part 2 (filename) */
         if (c.verbose)
            c.sprintf("writing header filename ... ");
         c.flush();
         flash_offs = mtd_ptr->header_offset + sizeof(sw_file_info_type);
         flash_len = header_len + 1;
         qspi_flash_write(&flash_partition, flash_offs, flash_len, sr_header_buf);
         if (c.verbose)
            c.sprintf("done\n");
         c.flush();
      }
   }

   fsync(fd); /* flush caches to make sure operation completes before desecting board */
   if (close(fd) < 0)
      c.sprintf("Error closing file\n");
}

//-------------------------------------------------------------------

void slot_upload(udp_connection &c, unsigned int slot_nr, int load_fw, char *fwp, int load_sw, char *swp,
                 unsigned int board_type, unsigned int board_rev) {
   char fw_path[256];
   char sw_path[256];

   flash_memory_map_type *flash_mem_map = NULL;

   fw_path[0] = sw_path[0] = 0;
   if (fwp[0])
      strncpy(fw_path, fwp, sizeof(fw_path));
   if (swp[0])
      strncpy(sw_path, swp, sizeof(sw_path));

   flash_mem_map = connect_flash(slot_nr, board_type, board_rev);
   if (flash_mem_map == NULL) {
      c.sprintf("Error: flash memory map not found (type %d, revision %d)\n", board_type, board_rev);
      disconnect();
      return;
   }

   if (strstr(flash_mem_map->default_fw_path, "/wdb/")) {
      /* WDB */
      if (load_fw) {
         if (!fw_path[0]) {
            /* set default path according to type and revision */
            strcpy(fw_path, flash_mem_map->default_fw_path);
            strcat(fw_path, wdb_fw_default_file);
         }
         if (c.show_default) {
            c.sprintf("Slot %2d firmware: %s\n", slot_nr, fw_path);
         } else {
            /* upload firmware */
            if (!c.percent && !c.erase) {
               c.sprintf("Uploading WDB firmware %s\n", fw_path);
               c.flush();
            }
            write_fw(c, slot_nr, fw_path, flash_mem_map, "fw");
         }
      }
      if (load_sw) {
         if (!sw_path[0]) {
            /* set default path according to type and revision */
            strcpy(sw_path, flash_mem_map->default_fw_path);
            strcat(sw_path, wdb_sw_default_file);
         }
         if (c.show_default) {
            c.sprintf("Slot %2d software: %s\n", slot_nr, sw_path);
         } else {
            /* upload sofware */
            if (!c.percent && !c.erase) {
               c.sprintf("Uploading WDB software %s\n", sw_path);
               c.flush();
            }
            write_sw(c, slot_nr, sw_path, flash_mem_map, "sw");
         }
      }
   } else if (strstr(flash_mem_map->default_fw_path, "/tcb/")) {
      /* TCB */
      if (load_fw) {
         if (!fw_path[0]) {
            /* set default path according to type and revision */
            strcpy(fw_path, flash_mem_map->default_fw_path);
            strcat(fw_path, tcb_fw_default_file);
         }
         if (c.show_default) {
            c.sprintf("Slot %2d firmware: %s\n", slot_nr, fw_path);
         } else {
            /* upload firmware */
            if (!c.percent) {
               c.sprintf("Uploading TCB firmware %s\n", fw_path);
               c.flush();
            }
            write_fw(c, slot_nr, fw_path, flash_mem_map, "fw");
         }
      }
   }

   disconnect();

   if (!c.show_default) {
      /* Apply init pulse to boards with old SPI scheme */
      if (bpl_spi_scheme[board_type][board_rev] == 0)
         init_slot(slot_nr, 1);

      // Wait 5 sec for board to boot
      for (int i=0 ; i<=50 ; i++) {
         char str[256];
         sprintf(str, "Slot %2d: Booting board     ", slot_nr);
         show_progress(c, 4, str, i/50.0*100, " ", PROG_BAR_REB_CHAR);
         usleep(100000);
      }
   }

   if (!c.percent)
      c.sprintf("\n");
}

//-------------------------------------------------------------------

void crate_upload(udp_connection &c, int slot[WDAQ_N_SLOTS], int load_fw, char *fwp, int load_sw, char *swp,
                  unsigned int board_type, unsigned int board_rev, unsigned int force) {
   int i;
   WDAQ_BRD slot_board_info;

   if (!c.percent && !c.show_default)
      c.sprintf("\e[?25l"); // hide cursor

   for (i = 0; i < WDAQ_N_SLOTS;  i++) {
      if (slot[i] && i != WDAQ_SLOT_DCB) {
         if (get_slot_board_info(i, &slot_board_info)) {
            if (force) {
               // get forced upload information
               if ((board_type != slot_board_info.type_id) || (board_rev != slot_board_info.rev_id)) {
                  c.sprintf("Error: present board in slot %d does not match type and revision\n", i);
                  continue;
               }
            }
         } else {
            if (force) {
               slot_board_info.type_id = board_type;
               slot_board_info.rev_id = board_rev;
            } else {
               // no slot board information for standard upload
               c.sprintf("Error: board information for slot %d could not be read or no board present\n", i);
               c.sprintf("\e[?25h"); // show cursor
               return;
            }
         }

         slot_upload(c, i, load_fw, fwp, load_sw, swp, slot_board_info.type_id, slot_board_info.rev_id);
      }
   }

   c.sprintf("\e[?25h"); // show cursor
   c.flush();
}

//-------------------------------------------------------------------

void upload(udp_connection &c, int n_param, const char **param) {
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
         for (int s = 0; s < 16; s++) {
            if (get_slot_board_info(s, &board_info)) {
               slot_sel[s] = 1;

               if (c.verbose) {

                  char name[32];
                  if (board_info.type_id == BRD_TYPE_ID_WDB) {

                     char buffer[10];
                     char rbuffer[10];

                     memset(buffer, 0, sizeof(buffer));
                     buffer[0] = CMD_READ32;
                     buffer[1] = 0;
                     buffer[2] = 0;
                     buffer[3] = 0;
                     buffer[4] = 0x24; // Status register SN
                     buffer[5] = 0; // dummy

                     spi_binary_cmd(buffer, rbuffer, 6 + 4, s, board_info.type_id, board_info.rev_id);

                     unsigned int sn = (rbuffer[8] << 8) | rbuffer[9];
                     snprintf(name, sizeof(name), "WD%03d", sn);
                  } else
                     snprintf(name, sizeof(name), "%s", wdaq_brd_type_name[board_info.type_id]);

                  c.sprintf("Slot %2d: Found board \"%s\", Revision \"%c\", Variant \"0x%02X\", Vendor \"%s\"\n",
                            s,
                            name,
                            'A' + board_info.rev_id,
                            board_info.variant_id,
                            wdaq_brd_vendor_name[board_info.vendor_id]);
               }
            }
         }
      }
   }
   
   int i;
   for (i = 0; i < WDAQ_N_SLOTS; i++)
      if (slot_sel[i])
         break;
   if (i == WDAQ_N_SLOTS) {
      c.sprintf("Please select slot(s) for upload or \"*\" for all slots\n");
      return;
   }

   // decode flags
   fwp[0] = 0;
   swp[0] = 0;
   c.verbose = 0;
   c.percent = 0;
   c.erase   = 0;
   c.show_default = 0;
   for (int i = 1; i < n_param; i++) {

      if (param[i][0] == '-' && param[i][1] == 'f') {
         if (++i >= n_param) {
            c.sprintf("Missing firmware file with \"-f\" option\n");
            return;
         }
         if (!is_file(param[i])) {
            c.sprintf("Firmware file \"%s\" not found\n", param[i]);
            return;
         } else {
            strncpy(fwp, param[i], sizeof(fwp));
         }
         load_fw = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 's') {
         if (++i >= n_param) {
            c.sprintf("Missing software file with \"-s\" option\n");
            return;
         }
         if (!is_file(param[i])) {
            c.sprintf("Software file \"%s\" not found\n", param[i]);
            return;
         } else {
            strncpy(swp, param[i], sizeof(swp));
         }
         load_sw = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 't') {
         if (++i >= n_param) {
            c.sprintf("Missing board type with \"-t\" option\n");
            return;
         }
         if (strcmp(param[i], "wdb") == 0) {
            board_type = BRD_TYPE_ID_WDB;
         } else if (strcmp(param[i], "tcb") == 0) {
            board_type = BRD_TYPE_ID_TCB;
         } else {
            c.sprintf("Unknown board type with \"-t\" option, must be \"wdb\" or \"tcb\"\n");
            return;
         }
         t_force = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 'r') {
         if (++i >= n_param) {
            c.sprintf("Missing board revision with \"-r\" option\n");
            return;
         }
         if (param[i][0] >= '1' && param[i][0] <= '3') {
            board_rev = strtoul(param[i], NULL, 0);
         } else if (param[i][0] >= 'e' && param[i][0] <= 'g') {
            board_rev = param[i][0] - 'a';
         } else if (param[i][0] >= 'F' && param[i][0] <= 'g') {
            board_rev = param[i][0] - 'A';
         } else {
            c.sprintf("Invalid board revision, must be \"1\" or \"2\" or \"3\" or \"e\" or \"g\"\n");
            return;
         }
         r_force = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 'd') {
         c.sprintf("Default firmware files:\n");
         c.show_default = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 'v') {
         c.verbose = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 'p') {
         c.percent = 1;
      }

      else if (param[i][0] == '-' && param[i][1] == 'e') {
         c.erase = 1;
      }

      else if (isdigit(param[i][0]) || param[i][0] == '*') {
         // parameter selects slot and is ignored here
      } else {
         c.sprintf("Invalid option \"%s\"\n\n", param[i]);
         return;
      }
   }

   if (load_fw == 0 && load_sw == 0) {
      load_fw = 1;
      load_sw = 1;
   }

   if (c.verbose)
      c.sprintf("\n");

   if (t_force && r_force) {
      /* forced upload */
      crate_upload(c, slot_sel, load_fw, fwp, load_sw, swp, board_type, board_rev, 1);
   } else {
      /* standard upload */
      crate_upload(c, slot_sel, load_fw, fwp, load_sw, swp, board_type, board_rev, 0);
   }

   return;
}

//-------------------------------------------------------------------

void init_reg_settings(udp_connection &c, int snr)
{
   unsigned int reg_val;

   c.sprintf("\r\nInitializing Control Register:\r\n");
   for(unsigned int i=0;i<NR_OF_REGS-1;i++) // Last register is the checksum
   {
      if(!dcb_reg_list[i].read_only)
         c.sprintf("[0x%08X]: 0x%08X\r\n", i*4, reg_default[i]);
      reg_bank_write(i*4, (unsigned int*)(&reg_default[i]), 1);
   }

   reg_bank_write(DCB_SERIAL_NUMBER_REG, (unsigned int*)(&snr), 1);

   // write software build date to status register
   reg_val = reg_sw_build_date();
   reg_bank_write(DCB_REG_SW_BUILD_DATE, &reg_val, 1);

   // write software build time to status register
   reg_val = reg_sw_build_time();
   reg_bank_write(DCB_REG_SW_BUILD_TIME, &reg_val, 1);

   // write software GIT hashtag to status register
   reg_val = get_sw_git_hash();
   reg_bank_write(DCB_REG_SW_GIT_HASH_TAG, &reg_val, 1);

   c.sprintf("\r\nStoring register bank contents in SPI flash\r\n");
   c.flush();
   
   reg_bank_store();
}
