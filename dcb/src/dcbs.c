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

// port to start the UDP server on
#define SERVER_PORT 4000

#define CMD_WRITE32 0x14
#define CMD_READ32  0x24

int _server_abort = 0;

int main(int argc, char *argv[]) {

   int verbose = 0;
   int daemon = 0;
   int server_port = SERVER_PORT;

   /* parse command line parameters */
   for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'D')
         daemon = 1;
      else if (argv[i][0] == '-' && argv[i][1] == 'v')
         verbose = 1;
      else if (argv[i][0] == '-') {
         if (i + 1 >= argc || argv[i + 1][0] == '-')
            goto usage;
         else if (argv[i][1] == 'p')
            server_port = atoi(argv[++i]);
      } else {
         usage:
         printf("usage: dcbs [-p port] [-v]\n\n");
         printf("       -D     Become a daemon\n");
         printf("       -h     Print this help page\n");
         printf("       -p     Server port to listen at\n");
         printf("       -v     Produce verbose debugging output\n\n");
         return 0;
      }
   }

   // socket address used for the server
   struct sockaddr_in server_address;
   memset(&server_address, 0, sizeof(server_address));
   server_address.sin_family = AF_INET;

   // htons: host to network short: transforms a value in host byte
   // ordering format to a short value in network byte ordering format
   server_address.sin_port = htons(server_port);

   // htons: host to network long: same as htons but to long
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);

   // create a UDP socket, creation returns -1 on failure
   int sock;
   if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
      printf("Could not create socket\n");
      return 1;
   }

   // bind it to listen to the incoming connections on the created server
   // address, will return -1 on error
   if ((bind(sock, (struct sockaddr *) &server_address, sizeof(server_address))) < 0) {
      printf("Could not bind socket to port %d\n", server_port);
      return 1;
   }

   // socket address used to store client address
   struct sockaddr_in client_address;
   socklen_t client_address_len = sizeof(client_address);

   printf("Server listening on port %d\n", server_port);


   if (daemon) {
      printf("Becoming a daemon...\n");
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

      // read content into buffer from an incoming client
      int len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address,
                         &client_address_len);

      // inet_ntoa prints user friendly representation of the
      // ip address
      if (verbose) {
         buffer[len] = '\0';
         printf("received: %d bytes from client %s\n", len, inet_ntoa(client_address.sin_addr));
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

      // interpret packet
      unsigned int cmd = buffer[0];
      unsigned int seq = (buffer[2] << 8) | buffer[3];
      unsigned int adr = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];

      if (cmd == CMD_WRITE32) {
         unsigned n = (len - 8) / 4;

         printf("Write to %04X, seq %d: ", adr, seq);

         unsigned int *p = (unsigned int *) (&buffer[8]);
         for (int i = 0; i < n; i++,p++)
            printf("%08X ", *p);

      } else if (cmd == CMD_READ32) {
         unsigned char rbuffer[1600];

         unsigned int n = (buffer[8] << 24) | (buffer[9] << 16) | (buffer[10] << 8) | buffer[11];

         // limit data to 1024 bytes for the moment
         n = n > 256 ? 256 : n;

         printf("Read %d from %04X, seq %d:", n, adr, seq);

         rbuffer[0] = 0x24;
         rbuffer[1] = 0x01;
         rbuffer[2] = buffer[2];
         rbuffer[3] = buffer[3];

         unsigned int *p = (unsigned int *) (&rbuffer[4]);
         for (int i = 0; i < n && i < 256; i++,p++) {
            *p = i;
         }

         // send same content back to the client ("echo")
         sendto(sock, rbuffer, n*4+4, 0, (struct sockaddr *) &client_address, sizeof(client_address));

      } else {

         // send same content back to the client ("echo")
         sendto(sock, buffer, len, 0, (struct sockaddr *) &client_address, sizeof(client_address));

      }
   }

   return 0;
}
