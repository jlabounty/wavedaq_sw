//
//  wds.h
//  WaveDAQ Server Application Header File
//
//  Created by Stefan Ritt on 5/8/15.
//

#ifndef __wds__wds__
#define __wds__wds__

#define SUCCESS 1
#define FAILURE 0

typedef struct {
   int  serial_number;
   char name[32];
   int  cmd_socket;
   int  data_socket;
   unsigned char eth_addr[16];
   int  trigger_level;
   char trigger_mask[10];
   int  gain;
   int  pzc;
   int  offset;
   float wf_offset[16][1024];
} WDB;

typedef struct {
   int  demo_flag;
   int  calibrate_flag;
   int  verbose_flag;
   int  adc_flag;
   int  raw_flag;
   int  http_port;
   int  n_boards;
   WDB  board[16];
} GLOBALS;

// interface functions
int wd_init(GLOBALS *gl);
int wd_read_waveform(GLOBALS *gl, int board, int timeout, float wf[16][1024]);
int wd_send(GLOBALS *gl, int board, int timeout_ms, const char *str, char *result, int *size);
int wd_calibrate(GLOBALS *gl);

size_t strlcpy(char *dst, const char *src, size_t size);
size_t strlcat(char *dst, const char *src, size_t size);

// linux and MAC specific things
#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#define sleep(x) usleep(x*1000)
#endif // __linux__ || __APLE__

// Windows specific things
#if defined(_WIN32)
#include <windows.h>
#define sleep(x) Sleep(x)
#endif // _WIN32

/* Byte and Word swapping big endian <-> little endian */
#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

#endif /* defined(__wds__wds__) */
