//
//  WDBLib.h
//  WaveDAQ Library Header File
//
//  Created by Stefan Ritt on 31 Jan 2017
//

#ifndef __wdblib_h__
#define __wdblib_h__

#include <string>

using namespace std;

#define SUCCESS 1
#define FAILURE 0

typedef struct {
   char           version_id[4];
   unsigned int   crc;
   float          sampling_frequency;
   float          temperature;
   float          wf_offset1[16][1024];
   float          wf_offset2[16][1024];
   float          wf_gain1[16][1024];
   float          wf_gain2[16][1024];
   float          drs_offset_range0[16];
   float          drs_offset_range1[16];
   float          drs_offset_range2[16];
   float          adc_offset_range0[16];
   float          adc_offset_range1[16];
   float          adc_offset_range2[16];
} VCALIB_DATA;

typedef struct {
   char           version_id[4];
   unsigned int   crc;
   float          sampling_frequency;
   float          temperature;
   float          dt[16][1024];
   float          period[16][1024];
   float          offset[16];
} TCALIB_DATA;

class WDB {
   string fName;

   static int fDataSocket;
   static int fServerPort;

public:
   
   // constructor
   WDB(string name) {
      fName = name;
   }

   // setter & getter
   string getName() { return fName; }
   
   // interface functions
   void Connect();
};

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

#endif /* defined(__wdblib_h__) */
