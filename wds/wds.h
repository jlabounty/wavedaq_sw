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

#define WD_N_CHANNELS 18 // 8+1 * 2
#define WD_N_BOARDS   16 // 16 boards per crate

typedef struct {
   char           version_id[4];
   unsigned int   crc;
   float          sampling_frequency;
   float          temperature;
   float          wf_offset1[WD_N_CHANNELS][1024];
   float          wf_offset2[WD_N_CHANNELS][1024];
   float          wf_gain1[WD_N_CHANNELS][1024];
   float          wf_gain2[WD_N_CHANNELS][1024];
   float          drs_offset_range0[WD_N_CHANNELS];
   float          drs_offset_range1[WD_N_CHANNELS];
   float          drs_offset_range2[WD_N_CHANNELS];
   float          adc_offset_range0[WD_N_CHANNELS];
   float          adc_offset_range1[WD_N_CHANNELS];
   float          adc_offset_range2[WD_N_CHANNELS];
} VCALIB_DATA;

typedef struct {
   char           version_id[4];
   unsigned int   crc;
   float          sampling_frequency;
   float          temperature;
   float          dt[WD_N_CHANNELS][1024];
   float          period[WD_N_CHANNELS][1024];
   float          offset[WD_N_CHANNELS];
} TCALIB_DATA;

typedef struct {
   int            serial_number;
   char           name[32];
   int            cmd_socket;
   int            data_socket;
   int            server_port;
   unsigned char  eth_addr[16];
   float          trigger_level;
   float          trigger_delay;
   char           trigger_mask[10];
   int            gain;
   int            pzc;
   float          range;
   float          temperature;
   int            pll_locked;
   unsigned int   scaler[18];

   VCALIB_DATA    vcalib;
   TCALIB_DATA    tcalib;
} WDB;

typedef struct {
   int            demo_flag;
   int            rotate_flag;
   int            verbose_flag;
   int            adc_flag;
   int            ofs_calib1_flag;
   int            ofs_calib2_flag;
   int            gain_calib_flag;
   int            range_calib_flag;
   int            time_calib1_flag;
   int            time_calib2_flag;
   int            time_calib3_flag;
   int            remove_spikes;
   int            http_port;
   int            n_boards;
   float          nominal_sampling_frequency;
   float          actual_sampling_frequency;
   int            trigger_mode;
   int            osctca_flag;
   int            read_channel9;
   int            clock_source;
   int            mux_flag;
   int            dcv_flag;
   float          dcv;
   WDB            board[WD_N_BOARDS];
   int            cmd;
} GLOBALS;

typedef struct {
   unsigned short board_id;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned short readout_sequence_number;
   unsigned short hardware_sequence_number;
   unsigned short sampling_frequency;
   unsigned short number_of_samples;
   unsigned short drs0_trigger_cell;
   unsigned short drs1_trigger_cell;
   unsigned short trigger_type;
} WD2_EVENT;

typedef struct {
   int            state;
   double         progress;
   int            n_board;
   int            i_board;
   int            n_iter1;
   int            i_iter1;
   int            n_iter2;
   int            i_iter2;
   int            n_iter3;
   int            i_iter3;
   int            n_iter4;
   int            i_iter4;
   int            index;
   Averager       *ave;
   int            fh;
   float          prev_range;
} VCALIB_PROGRESS;

typedef struct {
   int            state;
   double         progress;
   int            n_board;
   int            i_board;
   int            n_iter1;
   int            i_iter1;
   int            n_iter2;
   int            i_iter2;
   int            n_iter3;
   int            i_iter3;
   int            index;
   Averager       *ave;
   int            fh;
   float          prev_range;
} TCALIB_PROGRESS;

// calibration states
#define CS_INACTIVE     0
#define CS_SINGLE_BOARD 1
#define CS_FIRST_BOARD  2
#define CS_FIRST_SAMPLE 3
#define CS_RUNNING      4

// trigger modes
#define TM_NORMAL       0
#define TM_AUTO         1

// interface functions
int wd_init(GLOBALS *gl);
void wd_set_fe(GLOBALS *gl, int index);
void wd_set_trigger_level(GLOBALS *gl, int index);
void wd_set_trigger_mode(GLOBALS *gl, int index);
void wd_set_sampling_frequency(GLOBALS *gl, int index);
void wd_set_range(GLOBALS *gl, int index);
void wd_set_osctca(GLOBALS *gl, int index);
void wd_set_channel9(GLOBALS *gl, int index);
void wd_set_clocksource(GLOBALS *gl, int index);
void wd_set_dcv_flag(GLOBALS *gl, int index);
void wd_set_dcv(GLOBALS *gl, int index);

int wd_read_waveform(GLOBALS *gl, int board, int timeout, WD2_EVENT *pe, float wfU[WD_N_CHANNELS][1024], float wfT[WD_N_CHANNELS][1024]);
int wd_send(GLOBALS *gl, int board, int timeout_ms, const char *str, char *result, int *size);
int wd_calibrate_voltage(GLOBALS *gl, VCALIB_PROGRESS *p);
int wd_calibrate_time(GLOBALS *gl, TCALIB_PROGRESS *p);
void wd_read_board_status(GLOBALS *gl, int index);
void wd_read_scalers(GLOBALS *gl, int index);

size_t strlcpy(char *dst, const char *src, size_t size);
size_t strlcat(char *dst, const char *src, size_t size);

// linux and MAC specific things
#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#define sleep_ms(x) usleep(x*1000)
#endif // __linux__ || __APLE__

// Windows specific things
#if defined(_MSC_VER)
#pragma warning( disable: 4996)
#define isnan(x) _isnan(x)
#define sleep_ms(x) Sleep(x)
typedef int socklen_t;
#endif // _WIN32

/* Byte and Word swapping big endian <-> little endian */
#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

#endif /* defined(__wds__wds__) */
