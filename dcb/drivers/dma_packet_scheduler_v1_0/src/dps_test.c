#include "dma_packet_scheduler_v1_0.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//#define DO_UDP_SEND
#define PORT            8081
#define PC_IP           (inet_addr("129.129.193.185"))
#define EMS_RH7_LC_IP   (inet_addr("129.129.188.245"))
#define MAXLINE         1024
#define BUF_SIZE        4096

void usage(char *name)
{
  printf("Usage: %s <nr of windows>\n", name);
}


int main(int argc, char *argv[])
{
  int ret;
  unsigned int len;
  FILE *f;
  int fd;
  char buffer[BUF_SIZE];
  int sockfd;
  struct sockaddr_in servaddr;
  int i;
  char *data;
  fd_set readfds;
  int nfds;
  int ready;
  int read_len;
  int fpos;

  len = 0;

#ifdef DO_UDP_SEND
  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
//  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_addr.s_addr = PC_IP;
#endif

  printf("Waiting for data...\n");

  /* open device file */
  fd = open("/dev/dma_pkt_sched0", O_RDONLY);

  FD_ZERO(&readfds);
  FD_SET(fd, &readfds);
  nfds = fd+1;

  ready = select(nfds, &readfds, NULL, NULL, NULL);

  len = ioctl(fd, DPS_IOCQ_BUFSIZE);
  printf("\nFile size %d bytes\n", len);

  /* Test read and lseek */
  printf("\nUser Reading File (%d bytes):\n", len);
  read_len = len/4;
  if( read_len>16 ) read_len = 16;
  else if ( read_len = 0 ) read_len = 1;
  ret = read(fd, buffer, read_len);
  if(ret == 0)
  {
    printf("No data");
  }
  else
  {
    for(i=0;i<ret;i++) printf(" %02X", buffer[i]);
    printf("\n .\n .\n");
    fpos = lseek(fd, -read_len, SEEK_END);
    ret = read(fd, buffer, read_len);
    for(i=0;i<ret;i++) printf(" %02X", buffer[i]);
  }
  printf("\n");

  /* Test mmap */
  printf("\nUser Reading Memory Mapped Data:");
  data = mmap(NULL, BUF_SIZE, PROT_READ, MAP_SHARED, fd, 0);
  if(data != MAP_FAILED)
  {
    for(i = 0; i<len; i++)
    {
      if( (i%16)==0 ) printf("\n");
      printf(" %02X", data[i]);
    }
    printf("\n");

#ifdef DO_UDP_SEND
    printf("Sending via UDP...\n");
    sendto(sockfd, data, len,
          MSG_CONFIRM, (const struct sockaddr *) &servaddr,
          sizeof(servaddr));
    close(sockfd);
#endif

    if(munmap(data, BUF_SIZE) == -1)
    {
      printf("Unmap failed");
    }

    if( !ioctl(fd, DPS_IOCT_FREE_BUF) ) printf("\nCurrent window buffer released\n");
  }
  else
  {
    printf("No data available\n");
  }

  return close(fd);
}
