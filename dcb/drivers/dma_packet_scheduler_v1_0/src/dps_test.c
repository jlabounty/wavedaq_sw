#include "dma_packet_scheduler_v1_0.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//#define DO_UDP_SEND
#define PORT            8081
#define PC_IP           (inet_addr("129.129.193.185"))
#define EMS_RH7_LC_IP   (inet_addr("129.129.188.245"))
#define MAXLINE         1024

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
  struct dma_buf buffer[64];
  int sockfd;
  struct sockaddr_in servaddr;
  int i, j;
  char *data;
//  char *payload_data;
//  const char pld_1[10] = {0xF0, 0x0D, 0xC0, 0xDE, 0xDE, 0xAD, 0xBE, 0xEF, 0xAF, 0xFE};
//  payload_data = (char*)pld_1;

  if (argc < 2) {
    usage(argv[0]);
    return -1;
  }

  len = 1;
  len = (unsigned int)strtol(argv[1], NULL, 0);
  if(len>64)
  {
    printf("Reduced size to the maximum of 64\n");
    len = 64;
  }

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

  /* open device file */
  fd = open("/dev/dma_pkt_sched0", O_RDONLY);

  ret = read(fd, buffer, len);
  printf("%d buffers available...\n", ret);

  for(i=0;i<ret;i++)
  {
    printf("Buffer Information %d: slot %d   win %d   virt_addr 0x%08X   size %d\n", i, buffer[i].slot, buffer[i].win, (unsigned int)(buffer[i].data), buffer[i].len);
//    data = buffer[i].data;
//    for(j = 0; j<buffer[i].len; j++)
//    {
//      if( (j%16)==0 ) printf("\n");
//      printf(" %02X", data[j]);
//    }
//    printf("\n");
#ifdef DO_UDP_SEND
    printf("Sending via UDP...\n");
    sendto(sockfd, buffer[i].data, buffer[i].len,
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,
           sizeof(servaddr));
//    sendto(sockfd, (const char *)payload_data, 10,
//        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
//            sizeof(servaddr));
#endif
  }

#ifdef DO_UDP_SEND
  close(sockfd);
#endif

  ret = lseek(fd, ret, SEEK_SET);
  printf("%d window buffers released\n", ret);

  return 0;
}
