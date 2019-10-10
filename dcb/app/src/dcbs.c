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
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "git-revision.h"

#include "drv_axi_dcb_reg_bank.h"
#include "update_config.h"

// port to start the UDP servers on
#define SERVER_PORT_ASC 3000
#define SERVER_PORT_BIN 4000

#define CMD_WRITE32     0x14
#define CMD_READ32      0x24

#define SWAP_UINT32(x) (((x) >> 24) | \
                       (((x) & 0x00FF0000) >> 8) | \
                       (((x) & 0x0000FF00) << 8) | \
                       ((x) << 24))

int _server_abort = 0;

void print_buffer(const unsigned char *buffer, int len);

int main(int argc, char *argv[]) {

   int verbose = 0;
   int daemon = 0;
   char hostname[256];

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

   gethostname(hostname, sizeof(hostname));

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
   int sock_bin;
   if ((sock_bin = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
      printf("Could not create socket\n");
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

   printf("DCB binary server listening on %s ports %d,%d\n", hostname, SERVER_PORT_BIN, SERVER_PORT_ASC);

   // socket address used for the server
   memset(&server_address, 0, sizeof(server_address));
   server_address.sin_family = AF_INET;

   // htons: host to network short: transforms a value in host byte
   // ordering format to a short value in network byte ordering format
   server_address.sin_port = htons(SERVER_PORT_ASC);

   // htons: host to network long: same as htons but to long
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);

   // create a UDP socket, creation returns -1 on failure
   int sock_asc;
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

   printf("DCB ASCII server listening on port %d\n", SERVER_PORT_ASC);

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
      unsigned char buffer[1600];
      fd_set fds;

      FD_ZERO(&fds);
      FD_SET(sock_bin, &fds);
      FD_SET(sock_asc, &fds);

      if (select(FD_SETSIZE, &fds, NULL, NULL, NULL) < 0)
         perror("select");

      if (FD_ISSET(sock_bin, &fds)) {
         // read content into buffer from an incoming client
         int len = recvfrom(sock_bin, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address,
                            &client_address_len);

         // inet_ntoa prints user friendly representation of the
         // ip address
         if (verbose) {
            buffer[len] = '\0';
            printf("Binary request received: %d bytes from client %s\n", len, inet_ntoa(client_address.sin_addr));
            print_buffer(buffer, len);
         }

         // interpret packet
         unsigned int cmd = buffer[0];
         unsigned int seq = (buffer[2] << 8) | buffer[3];
         unsigned int adr = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];

         if (cmd == CMD_WRITE32) {
            unsigned n = (len - 8) / 4;

            if (verbose)
               printf("Write to %04X, seq %d: ", adr, seq);

            unsigned int *p = (unsigned int *) (&buffer[8]);
            unsigned int d;
            for (int i = 0; i < n; i++, p++) {
               d = *p;
               reg_bank_write(adr + i * 4, &d, 1);
            }

            // send acknowledge back to client
            buffer[1] = 0x01;
            sendto(sock_bin, buffer, 4, 0, (struct sockaddr *) &client_address, sizeof(client_address));

            // propagate new register contents to hardware
            auto_update_configurations();
            trigger_update_configurations();

         } else if (cmd == CMD_READ32) {
            unsigned char rbuffer[1600];

            unsigned int n = (buffer[8] << 24) | (buffer[9] << 16) | (buffer[10] << 8) | buffer[11];

            // limit data to 1024 bytes for the moment
            n = n > 1024 ? 1024 : n;

            if (verbose)
               printf("Read %d bytes from 0x%08X, seq %d:\n", n, adr, seq);

            rbuffer[0] = 0x24;
            rbuffer[1] = 0x01;
            rbuffer[2] = buffer[2];
            rbuffer[3] = buffer[3];

            unsigned int *p = (unsigned int *) (&rbuffer[4]);
            unsigned int d;
            for (int i = 0; i < n / 4 && i < 1024 / 4; i++, p++) {
               reg_bank_read(adr + i * 4, &d, 1);
               *p = d;
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

         unsigned char rbuffer[1600];
         rbuffer[0] = 0;

         if (buffer[0] == 'h') {
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "List of available commands:\n\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "help        This help page\n");
            snprintf(rbuffer+strlen(rbuffer), sizeof(rbuffer), "reset       Reboot DCB\n\n");
         } else if (strncmp(buffer, "reset", 5) == 0) {
            snprintf(rbuffer, sizeof(rbuffer), "Rebooting...\n\n");
            sendto(sock_asc, rbuffer, strlen(rbuffer)+1, 0, (struct sockaddr *) &client_address, sizeof(client_address));
            system("reboot");
            exit(0);
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

void print_buffer(const unsigned char *buffer, int len) {
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
