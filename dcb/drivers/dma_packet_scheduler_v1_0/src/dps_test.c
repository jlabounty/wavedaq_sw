#include "dma_packet_scheduler_v1_0.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
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

struct wdaq_header
{
  uint8_t  protocol_version;
  uint8_t  board_type_revision;
  uint16_t serial_number;
  uint8_t  crate_id;
  uint8_t  slot_id;
  uint16_t packet_number;
  uint8_t  data_type;
  uint8_t  wdaq_flags;
  uint16_t trigger_information[3];
  uint32_t event_number;
  uint16_t payload_length;
  uint16_t data_chunk_offset;
};

void usage(char *name)
{
  printf("Usage: %s <nr of windows>\n", name);
}

int get_bufsize_ioctl (int fd)
{
  return ioctl(fd, DPS_IOCQ_BUFSIZE);
}

int get_bufsize_sysfs (void)
{
  char buffer[32];
  int ret;
  int fd;

  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/data_bytes", O_RDONLY);
  if (fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/data_bytes");
    return fd;
  }
  ret = read(fd, buffer, sizeof(buffer));
  close(fd);
  buffer[ret] = 0;
  return strtol(buffer, NULL, 0);
}

int release_buffer_ioctl (int fd)
{
  return ioctl(fd, DPS_IOCT_FREE_BUF);
}

int release_buffer_sysfs (int n_buffers)
{
  char buffer[32];
  int ret;
  int fd;

  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/next_buffer", O_RDWR);
  if (fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/next_buffer");
    return fd;
  }
  ret = sprintf(buffer, "%d\n\0", n_buffers);
  write(fd, buffer, ret);
  close(fd);
  return 0;
}

void print_header(struct wdaq_header * wdaq_header)
{
  printf("\nPacket header:\n");
  printf("protocol version:       0x%02X (%d)\n", wdaq_header->protocol_version, wdaq_header->protocol_version);
  printf("board type revision:    0x%02X (%d)\n", wdaq_header->board_type_revision, wdaq_header->board_type_revision);
  printf("serial number:          0x%04X (%d)\n", ntohs(wdaq_header->serial_number), ntohs(wdaq_header->serial_number));
  printf("crate id:               0x%02X (%d)\n", wdaq_header->crate_id, wdaq_header->crate_id);
  printf("slot id:                0x%02X (%d)\n", wdaq_header->slot_id, wdaq_header->slot_id);
  printf("packet number:          0x%04X (%d)\n", ntohs(wdaq_header->packet_number), ntohs(wdaq_header->packet_number));
  printf("data type:              0x%02X (%d)\n", wdaq_header->data_type, wdaq_header->data_type);
  printf("wdaq flags:             0x%02X (%d)\n", wdaq_header->wdaq_flags, wdaq_header->wdaq_flags);
  printf("trigger information[0]: 0x%04X (%d)\n", ntohs(wdaq_header->trigger_information[0]), ntohs(wdaq_header->trigger_information[0]));
  printf("trigger information[1]: 0x%04X (%d)\n", ntohs(wdaq_header->trigger_information[1]), ntohs(wdaq_header->trigger_information[1]));
  printf("trigger information[2]: 0x%04X (%d)\n", ntohs(wdaq_header->trigger_information[2]), ntohs(wdaq_header->trigger_information[2]));
  printf("event number:           0x%08X (%d)\n", ntohl(wdaq_header->event_number), ntohl(wdaq_header->event_number));
  printf("payload length:         0x%04X (%d)\n", ntohs(wdaq_header->payload_length), ntohs(wdaq_header->payload_length));
  printf("data chunk offset:      0x%04X (%d)\n", ntohs(wdaq_header->data_chunk_offset), ntohs(wdaq_header->data_chunk_offset));
}

int read_data (void)
{
  int ret;
  unsigned int len;
//  FILE * f;
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
  time_t sys_time;
  struct tm loc_time;
  struct wdaq_header * wdaq_header;

  len = 0;

#ifdef DO_UDP_SEND
  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
  {
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

  FD_ZERO(&readfds);
  FD_SET(fd, &readfds);
  nfds = fd+1;

  ready = select(nfds, &readfds, NULL, NULL, NULL);

  sys_time = time(NULL);
  loc_time = *localtime(&sys_time);

  //len = get_bufsize_ioctl(fd);
  len = get_bufsize_sysfs();
  printf("%d.%02d.%02d %02d:%02d:%02d - ", loc_time.tm_mday, loc_time.tm_mon + 1, loc_time.tm_year + 1900, loc_time.tm_hour, loc_time.tm_min, loc_time.tm_sec);
  printf("packet size %d bytes, ", len);

#if 0
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
#endif

  /* Test mmap */
  data = mmap(NULL, BUF_SIZE, PROT_READ, MAP_SHARED, fd, 0);
  if(data != MAP_FAILED)
  {
    wdaq_header = (struct wdaq_header *)data;

    printf("slot 0x%02X, ",   wdaq_header->slot_id);
    printf("packet nr %d, ",  ntohs(wdaq_header->packet_number));
    printf("event nr %d, ",   ntohl(wdaq_header->event_number));
    printf("trigger nr %d, ", ntohs(wdaq_header->trigger_information[2]));
    printf("trigger type %d", ntohs(wdaq_header->trigger_information[0]));
    printf("\n");

#if 0
    print_header(wdaq_header);
#endif

#if 0
    for(i = 0; i<len; i++)
    {
      if( (i%16)==0 ) printf("\n");
      printf(" %02X", data[i]);
    }
    printf("\n");
#endif

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
  }
  else
  {
    printf("No data available\n");
  }

  if (0 != release_buffer_sysfs(1))
  {
    printf("\n Failed to release current window buffer\n");
  }
#if 0
//  if (release_buffer_ioctl(fd) == 0)
  if (release_buffer_sysfs(1) == 0)
  {
    printf("\nCurrent window buffer released\n");
  }
#endif

  return close(fd);
}

int main (int argc, char *argv[])
{
  int ret;

  printf("Waiting for data...\n");

  for (;;)
  {
    ret = read_data();
  }

  return ret;
}
