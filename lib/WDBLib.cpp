//
//  wd
//  WaveDAQ Ethernet Interface
//
//  Created by Stefan Ritt on 13/8/15.
//

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <assert.h>
#include <errno.h>

#ifdef __linux__
#include <linux/sockios.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>
#endif
#ifdef __APPLE__
#include <net/if_dl.h>
#include <pthread.h>
#endif

#include "WDBLib.h"
#include "register_map_wd2.h"

#define WD2_CMD_PORT          3000

#define WD2_MEM_OFS_CONTROL   0xc3000000
#define WD2_MEM_OFS_STATUS    0xc3010000

#pragma pack(1)

typedef struct {
   unsigned char  protocol_version;
   unsigned char  board_version;
   unsigned short board_id;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned char  adc_and_channel_info;
   unsigned char  channel_segment_number;
   unsigned short readout_sequence_number;
   unsigned short hardware_sequence_number;
   unsigned short sampling_frequency;
   unsigned short number_of_samples;
   unsigned short drs0_trigger_cell;
   unsigned short drs1_trigger_cell;
   unsigned short trigger_type;
   unsigned short packet_sequence_number;
} WD2_FRAME_HEADER;

int WDB::gDataSocket = 0;
int WDB::gServerPort = 0;
int WDB::gCmdSocket  = 0;

//--------------------------------------------------------------------

void WDB::Send(std::string str, int timeout_ms)
{
   std::string result;
   result = SendReceive(str, timeout_ms);
}

//--------------------------------------------------------------------

std::string WDB::SendReceive(std::string str, int timeout_ms)
{
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int    status, ms;
   struct sockaddr_in client_addr;
   char   rx_buffer[1600];
   std::string prompt, result;
   
   memcpy(&client_addr, mEthAddr, sizeof(client_addr));
   
   if (str.back() != '\n')
      str += '\n';
   
   result.clear();
   
   // assemble prompt
   prompt = mName + " > ";
   
   // retry max five times
   for (int retry=0 ; retry < 5 ; retry++) {

      // clear input queue
      do {
         FD_ZERO(&readfds);
         FD_SET(gCmdSocket, &readfds);
         
         timeout.tv_sec = 0;
         timeout.tv_usec = 0;
         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1); // don't return on interrupt
         
         if (!FD_ISSET(gCmdSocket, &readfds))
            break;
         
         i = recv(gCmdSocket, rx_buffer, sizeof(rx_buffer), 0);
      } while (true);
      
      // send request
      i = sendto(gCmdSocket,
                 str.c_str(),
                 str.size(),
                 0,
                 (struct sockaddr *)&client_addr,
                 sizeof(client_addr));
      
      if (i != str.size()) {
         if (this->mDebug)
            std::cout << mName << " send retry " << retry+1 << std::endl;
         continue;
      }
      
      // retrieve reply until prompt is found
      do {
         memset(rx_buffer, 0, sizeof(rx_buffer));
         
         FD_ZERO(&readfds);
         FD_SET(gCmdSocket, &readfds);
         
         ms = timeout_ms;
         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;
         
         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was cought */
         
         if (!FD_ISSET(gCmdSocket, &readfds))
            break;
         
         i = recv(gCmdSocket, rx_buffer, sizeof(rx_buffer), 0);
         assert(i > 0);
         
         if (rx_buffer[i-1] == 0) // don't count trailing zero
            i--;
         
         result += rx_buffer;
         
         // check for prompt
         if (result.substr(result.size()-prompt.size()) == prompt)
            break;
         
      } while (1);
      
      // check for prompt
      if (result.size() >= prompt.size() && result.substr(result.size()-prompt.size()) == prompt)
         break;
      
      if (this->mDebug)
         std::cout << mName << " retry " << retry+1 << std::endl;
      result.clear();
   }
   
   if (result.size() == 0) {
      if (str.back() == '\n')
        str = str.substr(0, str.size()-1);
      throw std::runtime_error(std::string("Error sending \"")+str+"\" to "+mName+".");
      return result;
   }
   
   // chop off prompt
   if (result.size() >= prompt.size())
      result = result.substr(0, result.size()-prompt.size());
   
   return result;
}

//--------------------------------------------------------------------

void WDB::Connect()
{
   struct sockaddr_in server_addr;
   struct sockaddr_in client_addr;
   struct hostent *phe;
   
#ifdef _MSC_VER
   {
   WSADATA WSAData;
   
   // Start windows sockets
   if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
      return -1;
   }
#endif
   
   // create UDB socket for command interpreter on any port
   if (gCmdSocket == 0)
      gCmdSocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(gCmdSocket);
   
   // create UDB socket to receive binary data on port WD2_DATA_PORT
   if (gDataSocket == 0) {
      gDataSocket = socket(AF_INET, SOCK_DGRAM, 0);
      assert(gDataSocket);
      
      // bind socket to port chosen by OS
      memset((char*)&server_addr, 0, sizeof(server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(0); // let OS choose port
      server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      if (::bind(gDataSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
         perror("bind");
         throw std::runtime_error(std::string("Cannot bind socket"));
      }
      auto size = sizeof(server_addr);
      getsockname(gDataSocket, (struct sockaddr *) &server_addr, (socklen_t *) &size);
      gServerPort = ntohs(server_addr.sin_port);
      
      if (this->mDebug)
         std::cout << std::endl << "Listening on data port " << gServerPort << "." << std::endl;
   }
   
   // retrieve Ethernet address of board
   phe = gethostbyname(mName.c_str());
   if (phe == NULL)
      throw std::runtime_error(std::string("Cannot resolve host name ")+mName+".");
   
   memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
   client_addr.sin_family = AF_INET;
   client_addr.sin_port = htons(WD2_CMD_PORT);
   memcpy(mEthAddr, &client_addr, sizeof(client_addr));
   
   // check if board is alive
   try {
      WDB::Send("", 500);
   } catch (...) {
      throw std::runtime_error(std::string("Cannot connect to board ")+mName+".");
   }
   
   // set dbglevel none
   Send("dbglvl none");
   
   // set destinantion port in WD board
   Send(std::string("setenv dstport ")+std::to_string(gServerPort));
   
   // set MAC address and IP address of this computer in WD board
   Send("cfgdst");
}

//--------------------------------------------------------------------

unsigned int bitExtract(unsigned int reg[], unsigned int rofs, unsigned int mask, unsigned int ofs)
{
   return (reg[rofs/4] & mask) >> ofs;
}

void bitReplace(unsigned int &reg, unsigned int mask, unsigned int ofs, unsigned int value)
{
   reg = reg & (~mask); // clear bits from mask
   value <<= ofs;       // shift values
   value &= mask;
   reg |= value;        // set makes bits
}

//--------------------------------------------------------------------

void WDB::ReceiveControlRegisters()
{
   std::string result;
   std::ostringstream req;
   req << "llrd " << std::hex << WD2_MEM_OFS_CONTROL << " " << std::dec << WD2_REG_CRC32_REG_BANK_OFS/4+1;
   
   result = SendReceive(req.str(), 500);
   std::stringstream ss(result);
   std::string line;
   
   for (auto i=0 ; i<WD2_REG_CRC32_REG_BANK_OFS/4 ; i++) {
      std::getline(ss, line, '\r');
      auto adr = (unsigned int)std::stoul(line.substr(3), nullptr, 16);
      if (adr > 0 && adr < WD2_REG_CRC32_REG_BANK_OFS/4)
         this->creg[adr] = (unsigned int)std::stoul(line.substr(14), nullptr, 16);
   }
}

void WDB::ReceiveStatusRegisters()
{
   std::string result;
   std::ostringstream req;
   req << "llrd " << std::hex << WD2_MEM_OFS_STATUS << " " << std::dec << WD2_REG_ADC_01_CLK_MOD_FLAG_OFS/4+1;
   
   result = SendReceive(req.str(), 500);
   std::stringstream ss(result);
   std::string line;
   
   for (auto i=0 ; i<WD2_REG_ADC_01_CLK_MOD_FLAG_OFS/4 ; i++) {
      std::getline(ss, line, '\r');
      this->sreg[i] = (unsigned int)std::stoul(line.substr(14), nullptr, 16);
   }
}

void WDB::ReceiveStatusRegister(int ofs)
{
   std::string result;
   std::ostringstream req;
   auto adr = WD2_MEM_OFS_STATUS + ofs;
   req << "llrd " << std::hex << adr << " 1";
      
   result = SendReceive(req.str());
   this->sreg[ofs/4] = (unsigned int)std::stoul(result.substr(13), nullptr, 16);
}

void WDB::SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v)
{
   unsigned int r = this->creg[rofs/4];
   
   bitReplace(r, mask, ofs, v);
   
   std::ostringstream req;
   req << "regwr " << std::hex << rofs << " " << r;
   
   Send(req.str());
   
   this->creg[rofs/4] = r;
}

//-- Status registers ------------------------------------------------

void WDB::PrintVersion()
{
   std::cout << GetFwBuild() << std::endl;
   std::cout << GetHwVersion() << std::endl;
   std::cout << "Protocol version:    " << GetProtocolVersion() << std::endl;
   std::cout << "Serial number:       " << GetSerialNumber() << std::endl;
}

std::string WDB::GetFwBuild()
{
   std::ostringstream s;
   std::vector<std::string> monthName = {"Jan", "Feb", "Mar", "Apr", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
   
   s << "Compatibility Level: ";
   s << bitExtract(sreg, WD2_REG_REG_LAYOUT_VER_OFS, WD2_BIT_FW_COMPAT_LEVEL_MASK, WD2_BIT_FW_COMPAT_LEVEL_OFS) << std::endl;
   s << "FW GIT Revision:     ";
   s << "0x" << std::hex << std::uppercase << bitExtract(sreg, WD2_REG_GIT_HASH_TAG_OFS, WD2_BIT_GIT_HASH_TAG_MASK, WD2_BIT_GIT_HASH_TAG_OFS) << std::endl;
   
   s << "FW Build:            ";
   s << std::dec << std::setw(2) << std::setfill('0');
   s << monthName[bitExtract(sreg, WD2_REG_FW_BUILD_DATE_OFS, WD2_BIT_FW_BUILD_MONTH_MASK, WD2_BIT_FW_BUILD_MONTH_OFS)-1] << ' ';
   s << bitExtract(sreg, WD2_REG_FW_BUILD_DATE_OFS, WD2_BIT_FW_BUILD_DAY_MASK, WD2_BIT_FW_BUILD_DAY_OFS) << ' ';
   s << bitExtract(sreg, WD2_REG_FW_BUILD_DATE_OFS, WD2_BIT_FW_BUILD_YEAR_MASK, WD2_BIT_FW_BUILD_YEAR_OFS) << "  ";
   
   s << std::setfill('0') << std::setw(2) << bitExtract(sreg, WD2_REG_FW_BUILD_TIME_OFS, WD2_BIT_FW_BUILD_HOUR_MASK, WD2_BIT_FW_BUILD_HOUR_OFS) << ':';
   s << std::setfill('0') << std::setw(2) << bitExtract(sreg, WD2_REG_FW_BUILD_TIME_OFS, WD2_BIT_FW_BUILD_MINUTE_MASK, WD2_BIT_FW_BUILD_MINUTE_OFS) << ':';
   s << std::setfill('0') << std::setw(2) << bitExtract(sreg, WD2_REG_FW_BUILD_TIME_OFS, WD2_BIT_FW_BUILD_SECOND_MASK, WD2_BIT_FW_BUILD_SECOND_OFS) << std::endl;
   
   return s.str();
}

std::string WDB::GetHwVersion()
{
   std::ostringstream s;
   
   assert(bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_MAGIC_MASK, WD2_BIT_BOARD_MAGIC_OFS) == 0xAC);
   
   s << "Board Type:          ";
   s << "WaveDREAM" << bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_TYPE_MASK, WD2_BIT_BOARD_TYPE_OFS) << std::endl;
   s << "Board Revision:      ";
   s << (char)('A'+bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_REVISION_MASK, WD2_BIT_BOARD_REVISION_OFS)) << std::endl;
   s << "Board Variant:       ";
   s << std::showbase << std::internal << std::setfill('0') << std::hex << std::setw(4) << bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_VARIANT_MASK, WD2_BIT_BOARD_VARIANT_OFS);
   s << std::endl;
   
   return s.str();
}

unsigned int WDB::GetProtocolVersion()
// currently 4
{
   return bitExtract(sreg, WD2_REG_PROT_VER_OFS, WD2_BIT_PROTOCOL_VERSION_MASK, WD2_BIT_PROTOCOL_VERSION_OFS);
}

unsigned int WDB::GetSerialNumber()
{
   return bitExtract(sreg, WD2_REG_SN_OFS, WD2_BIT_SERIAL_NUMBER_MASK, WD2_BIT_SERIAL_NUMBER_OFS);
}

float WDB::GetTemperature()
// temperature in deg. C
{
   ReceiveStatusRegister(WD2_REG_STATUS_OFS);
   float temp = bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_TEMPERATURE_MASK, WD2_BIT_TEMPERATURE_OFS) * 0.0625;
   temp = std::roundf(temp * 10 + 0.5) / 10.0f;
   return temp;
}

bool WDB::IsFlashSelect()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_FLASH_SEL_MASK, WD2_BIT_FLASH_SEL_OFS) == 0;
}

bool WDB::IsBoardSelect()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_BOARD_SEL_MASK, WD2_BIT_BOARD_SEL_OFS) == 0;
}

bool WDB::IsSerialBusy()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_SERIAL_BUSY_MASK, WD2_BIT_SERIAL_BUSY_OFS) == 0;
}

bool WDB::IsSysBusy()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_SYS_BUSY_MASK, WD2_BIT_SYS_BUSY_OFS) == 0;
}

bool WDB::IsWDBBusy()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_WDB_BUSY_MASK, WD2_BIT_WDB_BUSY_OFS) == 0;
}

bool WDB::IsHvBoardPlugged()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_HV_BOARD_PLUGGED_MASK, WD2_BIT_HV_BOARD_PLUGGED_OFS) == 1;
}

bool WDB::IsBackplanePlugged()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_BACKPLANE_PLUGGED_MASK, WD2_BIT_BACKPLANE_PLUGGED_OFS) == 1;
}

unsigned int WDB::GetExtPllLck()
// external PLLs (DRS, LMK)
{
   ReceiveStatusRegister(WD2_REG_PLL_LOCK_OFS);
   return bitExtract(sreg, WD2_REG_PLL_LOCK_OFS, WD2_BIT_DRS_PLL_LOCK_0_MASK |
                     WD2_BIT_DRS_PLL_LOCK_1_MASK | WD2_BIT_LMK_PLL_LOCK_MASK,
                     WD2_BIT_LMK_PLL_LOCK_OFS);
}

bool WDB::IsExtPllLck()
{
   auto mask = WD2_BIT_DRS_PLL_LOCK_0_MASK |
               WD2_BIT_DRS_PLL_LOCK_1_MASK |
               WD2_BIT_LMK_PLL_LOCK_MASK;
   mask >>= WD2_BIT_LMK_PLL_LOCK_OFS;
   
   return (GetExtPllLck() == mask);
}

unsigned int WDB::GetIntPllLck()
// internal PLLs (FPGA DAQ, ISERDES, OSERDES)
{
   ReceiveStatusRegister(WD2_REG_PLL_LOCK_OFS);
   auto mask = WD2_BIT_SYS_DCM_LOCK_MASK |
   WD2_BIT_DAQ_PLL_LOCK_MASK |
   WD2_BIT_OSERDES_PLL_LOCK_DCB_MASK |
   WD2_BIT_OSERDES_PLL_LOCK_TCB_MASK |
   WD2_BIT_ISERDES_PLL_LOCK_0_MASK |
   WD2_BIT_ISERDES_PLL_LOCK_1_MASK;
   
   return bitExtract(sreg, WD2_REG_PLL_LOCK_OFS, mask, WD2_BIT_LMK_PLL_LOCK_OFS);
}

bool WDB::IsIntPllLck()
{
   auto mask = WD2_BIT_SYS_DCM_LOCK_MASK |
               WD2_BIT_DAQ_PLL_LOCK_MASK |
               WD2_BIT_OSERDES_PLL_LOCK_DCB_MASK |
               WD2_BIT_OSERDES_PLL_LOCK_TCB_MASK |
               WD2_BIT_ISERDES_PLL_LOCK_0_MASK |
               WD2_BIT_ISERDES_PLL_LOCK_1_MASK;
   mask >>= WD2_BIT_ISERDES_PLL_LOCK_1_OFS;
   
   return (GetExtPllLck() == mask);
}


unsigned int WDB::GetDrsSampleFreq()
// sampling frequency in MHz
{
   return bitExtract(sreg, WD2_REG_DRS_SAMPLE_FREQ_OFS, WD2_BIT_DRS_SAMPLE_FREQ_MASK, WD2_BIT_DRS_SAMPLE_FREQ_OFS);
}

unsigned int WDB::GetAdcSampleFreq()
// sampling frequency in MHz
{
   return bitExtract(sreg, WD2_REG_ADC_SAMPLE_FREQ_OFS, WD2_BIT_ADC_SAMPLE_FREQ_MASK, WD2_BIT_ADC_SAMPLE_FREQ_OFS);
}

unsigned int WDB::GetAdcInfo()
// chip ID (0x93 for AD9637), speed grade (0=40MS, 1=80MS)
{
   auto mask = WD2_BIT_ADC_0_CHIP_ID_MASK | WD2_BIT_ADC_0_SPEED_MASK |
               WD2_BIT_ADC_1_CHIP_ID_MASK | WD2_BIT_ADC_1_SPEED_MASK;
   return bitExtract(sreg, WD2_REG_ADC_INFO_OFS, mask, WD2_BIT_ADC_1_SPEED_OFS);
}

void WDB::GetScalers(std::vector<unsigned long> &scaler)
{
   std::string result;
   std::ostringstream req;
   auto adr = WD2_MEM_OFS_STATUS + WD2_REG_SCALER_0_LSB_OFS;
   req << "llrd " << std::hex << adr << " 34";
   
   result = SendReceive(req.str(), 500); // increased timeout
   std::stringstream ss(result);
   std::string line;
   
   for (auto i=0 ; i<34 ; i++) {
      std::getline(ss, line, '\r');
      auto adr = ((unsigned int)std::stoul(line.substr(7), nullptr, 16)) / 4;
      if (adr >= WD2_REG_SCALER_0_LSB_OFS/4 && adr < WD2_REG_SCALER_EXT_CLK_OFS/4)
         this->sreg[adr] = (unsigned int)std::stoul(line.substr(14), nullptr, 16);
   }
   
   // channels 0-15 are 64 bit counters
   for (auto i=0 ; i<16 ; i++) {
      unsigned long v = this->sreg[WD2_REG_SCALER_0_LSB_OFS/4+i*2] |
      ((unsigned long)this->sreg[WD2_REG_SCALER_0_LSB_OFS/4+i*2+1] << 32);
      
      if (scaler.size() < i+1)
         scaler.push_back(v);
      else
         scaler[i] = v;
   }
   
   // channels 16 and 17 are 32 bit counters
   for (auto i=16 ; i<18 ; i++) {
      unsigned long v = this->sreg[WD2_REG_SCALER_TRG_OFS/4+i];
      
      if (scaler.size() < i+1)
         scaler.push_back(v);
      else
         scaler[i] = v;
   }
   
}

unsigned int WDB::GetCompChannelStatus()
// comparator status for 16 channels (1 = above threshold)
{
   return bitExtract(sreg, WD2_REG_COMP_CH_STAT_OFS, WD2_BIT_COMP_CH_STAT_MASK, WD2_BIT_COMP_CH_STAT_OFS);
}

unsigned int WDB::GetLastEventNumber()
// number of last event sent
{
   return bitExtract(sreg, WD2_REG_EVENT_NR_OFS, WD2_BIT_EVENT_NUMBER_MASK, WD2_BIT_EVENT_NUMBER_OFS);
}

unsigned int WDB::GetTriggerBusParityErrorCount()
// error counter for trigger bus parity errors
{
   return bitExtract(sreg, WD2_REG_TRB_PARITY_ERR_OFS, WD2_BIT_TRB_PARITY_ERROR_COUNT_MASK, WD2_BIT_TRB_PARITY_ERROR_COUNT_OFS);
}

unsigned int WDB::GetTriggerBusType()
// trigger type broadcasted via trigger bus
{
   return bitExtract(sreg, WD2_REG_TRB_INFO_OFS, WD2_BIT_TRB_TYPE_MASK, WD2_BIT_TRB_TYPE_OFS);
}

unsigned int WDB::GetTriggerBusNumber()
// event number LSB broadcasted via trigger bus
{
   return bitExtract(sreg, WD2_REG_TRB_INFO_OFS, WD2_BIT_TRB_NUMBER_MASK, WD2_BIT_TRB_NUMBER_OFS);
}

//-- Control registers -----------------------------------------------

unsigned int WDB::GetCrateId()
// id of crate (0-255)
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_CRATE_ID_MASK, WD2_BIT_CRATE_ID_OFS);
}

void WDB::SetCrateId(unsigned int value)
{
   SetRegMask(WD2_REG_WDB_LOC_OFS, WD2_BIT_CRATE_ID_MASK, WD2_BIT_CRATE_ID_OFS, value);
}

unsigned int WDB::GetSlotId()
// WaveDAQ crate slot number (0-15)
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_SLOT_ID_MASK, WD2_BIT_SLOT_ID_OFS);
}

void WDB::SetSlotId(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_SLOT_ID_MASK, WD2_BIT_SLOT_ID_OFS, value);
}

unsigned int WDB::GetValidDelayADC()
// delay of data valid at the ISERDES of the ADCs
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_VALID_DELAY_ADC_MASK, WD2_BIT_VALID_DELAY_ADC_OFS);
}

void WDB::SetValidDelayADC(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_VALID_DELAY_ADC_MASK, WD2_BIT_VALID_DELAY_ADC_OFS, value);
}

unsigned int WDB::GetDAQDataPhase()
// phase step setting of the PLL generating the common DAQ clock
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_DAQ_DATA_PHASE_MASK, WD2_BIT_DAQ_DATA_PHASE_OFS);
}

void WDB::SetDAQDataPhase(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_DATA_PHASE_MASK, WD2_BIT_DAQ_DATA_PHASE_OFS, value);
}

bool WDB::IsCompPowerEnable()
// comperator power enable
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_COMP_POWER_EN_MASK, WD2_BIT_COMP_POWER_EN_OFS) == 1;
}

void WDB::SetCompPowerEnable(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_COMP_POWER_EN_MASK, WD2_BIT_COMP_POWER_EN_OFS, value ? 1 : 0);
}

unsigned int WDB::GetReadoutSrcSel()
// 0x1 = DRS readout / 0x2 = ADC readout / 0x4 = TDC readout
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_READOUT_SRC_SEL_MASK, WD2_BIT_READOUT_SRC_SEL_OFS);
}

void WDB::SetReadoutSrcSel(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_READOUT_SRC_SEL_MASK, WD2_BIT_READOUT_SRC_SEL_OFS, value);
}

unsigned int WDB::GetDRSReadoutMode()
// 0 = start from first sampling cell / 1 = start from stop cell
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_DRS_READOUT_MODE_MASK, WD2_BIT_DRS_READOUT_MODE_OFS);
}

void WDB::SetDRSReadoutMode(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DRS_READOUT_MODE_MASK, WD2_BIT_DRS_READOUT_MODE_OFS, value);
}

bool WDB::IsDRSWaveContinous()
// run domino wave continously even during readout
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_DRS_WAVE_CONTINUOUS_MASK, WD2_BIT_DRS_WAVE_CONTINUOUS_OFS) == 1;
}

void WDB::SetDRSWaveContinous(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DRS_WAVE_CONTINUOUS_MASK, WD2_BIT_DRS_WAVE_CONTINUOUS_OFS, value ? 1 : 0);
}

void WDB::TrgDRSConfigure()
// tirggers a DRS chip register configuration
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DRS_CONFIGURE_MASK, WD2_BIT_DRS_CONFIGURE_OFS, 1);
}

void WDB::TrgDAQSoft()
// software trigger of a DRS readout
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_SOFT_TRIGGER_MASK, WD2_BIT_DAQ_SOFT_TRIGGER_OFS, 1);
}

void WDB::TrgDAQReinit()
// stop & reset the DRS readout state machine
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_REINIT_MASK, WD2_BIT_DAQ_REINIT_OFS, 1);
}

bool WDB::IsDAQNormal()
// "normal" acquisition mode like on an oscilloscope
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_DAQ_NORMAL_MASK, WD2_BIT_DAQ_NORMAL_OFS) == 1;
}

void WDB::SetDAQNormal(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_NORMAL_MASK, WD2_BIT_DAQ_NORMAL_OFS, value ? 1 : 0);
}

bool WDB::IsDAQSingle()
// "single" acquisition mode like on an oscilloscope
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_DAQ_SINGLE_MASK, WD2_BIT_DAQ_SINGLE_OFS) == 1;
}

void WDB::SetDAQSingle(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_SINGLE_MASK, WD2_BIT_DAQ_SINGLE_OFS, value ? 1 : 0);
}

unsigned int WDB::GetDRS0TimingRefSel()
// 0 = oscillator / 1 = LMK
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_0_TIMING_REF_SEL_MASK, WD2_BIT_DRS_0_TIMING_REF_SEL_OFS);
}

void WDB::SetDRS0TimingRefSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_0_TIMING_REF_SEL_MASK, WD2_BIT_DRS_0_TIMING_REF_SEL_OFS, value);
}

unsigned int WDB::GetDRS1TimingRefSel()
// 0 = oscillator / 1 = LMK
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_1_TIMING_REF_SEL_MASK, WD2_BIT_DRS_1_TIMING_REF_SEL_OFS);
}

void WDB::SetDRS1TimingRefSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_1_TIMING_REF_SEL_MASK, WD2_BIT_DRS_1_TIMING_REF_SEL_OFS, value);
}

bool WDB::IsTimingCalibBufferEnable()
// enable (power) buffers driving the timing calibration signal to the frontend MUX
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_TIMING_CALIB_BUFFER_EN_MASK, WD2_BIT_TIMING_CALIB_BUFFER_EN_OFS) == 1;
}

void WDB::SetTimingCalibBufferEnable(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_TIMING_CALIB_BUFFER_EN_MASK, WD2_BIT_TIMING_CALIB_BUFFER_EN_OFS, value ? 1 : 0);
}

bool WDB::IsTimingCalibSignalEnable()
// enable (power) buffers driving the timing calibration signal to the frontend MUX
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_TIMING_CALIB_SIGNAL_EN_MASK, WD2_BIT_TIMING_CALIB_SIGNAL_EN_OFS) == 1;
}

void WDB::SetTimingCalibSignalEnable(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_TIMING_CALIB_SIGNAL_EN_MASK, WD2_BIT_TIMING_CALIB_SIGNAL_EN_OFS, value ? 1 : 0);
}

unsigned int WDB::GetDAQClkSrcSel()
// 0 = crate clock / 1 = on-board oscillator
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DAQ_CLK_SRC_SEL_MASK, WD2_BIT_DAQ_CLK_SRC_SEL_OFS);
}

void WDB::SetDAQClkSrcSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DAQ_CLK_SRC_SEL_MASK, WD2_BIT_DAQ_CLK_SRC_SEL_OFS, value);
}

unsigned int WDB::GetExtClkInSel()
// 0 = crate clock / 1 = MCX connector input
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_EXT_CLK_IN_SEL_MASK, WD2_BIT_EXT_CLK_IN_SEL_OFS);
}

void WDB::SetExtClkInSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_EXT_CLK_IN_SEL_MASK, WD2_BIT_EXT_CLK_IN_SEL_OFS, value);
}

unsigned int WDB::GetExtClkFreq()
// external clock frequency in MHz
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_EXT_CLK_FREQ_MASK, WD2_BIT_EXT_CLK_FREQ_OFS);
}

unsigned int WDB::GetLocalClkFreq()
// on-board clock frequency in MHz
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_LOCAL_CLK_FREQ_MASK, WD2_BIT_LOCAL_CLK_FREQ_OFS);
}

unsigned int WDB::GetDRS1ChnTxEnable()
// channel transmission enable of DRS1 [CH8:CH0], CH8:clock channel
{
   return bitExtract(creg, WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_1_CH_TX_EN_MASK, WD2_BIT_DRS_1_CH_TX_EN_OFS);
}

void WDB::SetDRS1ChnTxEnable(unsigned int value)
{
   SetRegMask(WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_1_CH_TX_EN_MASK, WD2_BIT_DRS_1_CH_TX_EN_OFS, value);
}

unsigned int WDB::GetDRS0ChnTxEnable()
// channel transmission enable of DRS0 [CH8:CH0], CH8:clock channel
{
   return bitExtract(creg, WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_0_CH_TX_EN_MASK, WD2_BIT_DRS_0_CH_TX_EN_OFS);
}

void WDB::SetDRS0ChnTxEnable(unsigned int value)
{
   SetRegMask(WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_0_CH_TX_EN_MASK, WD2_BIT_DRS_0_CH_TX_EN_OFS, value);
}

unsigned int WDB::GetDRSControl()
/* bits
    18:  drs_wsrloop
    17:  drs_pllen
    16:  drs_dmode
    15:8 drs_wsr
     7:0 drs_wcr
*/
{
   auto mask = WD2_BIT_DRS_WSRLOOP_MASK |
               WD2_BIT_DRS_PLLEN_MASK |
               WD2_BIT_DRS_DMODE_MASK |
               WD2_BIT_DRS_WSR_MASK |
               WD2_BIT_DRS_WCR_MASK;
   
   return bitExtract(creg, WD2_REG_DRS_CTRL_OFS, mask, WD2_BIT_DRS_WCR_OFS);
}

void WDB::SetDRSControl(unsigned int value)
{
   auto mask = WD2_BIT_DRS_WSRLOOP_MASK |
   WD2_BIT_DRS_PLLEN_MASK |
   WD2_BIT_DRS_DMODE_MASK |
   WD2_BIT_DRS_WSR_MASK |
   WD2_BIT_DRS_WCR_MASK;

   SetRegMask(WD2_REG_DRS_CTRL_OFS, mask, WD2_BIT_DRS_WCR_OFS, value);
}

unsigned int WDB::GetDataDestination()
// 0 = Ethernet / 1 = oserdes to backplane
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_DATA_DESTINATION_MASK, WD2_BIT_DATA_DESTINATION_OFS);
}

void WDB::SetDataDestination(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_DATA_DESTINATION_MASK, WD2_BIT_DATA_DESTINATION_OFS, value);
}

unsigned int WDB::GetDCBSerdesTrain()
// enable training pattero for DCB serdes connection
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_DCB_SERDES_TRAIN_MASK, WD2_BIT_DCB_SERDES_TRAIN_OFS);
}

void WDB::SetDCBSerdesTrain(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_DCB_SERDES_TRAIN_MASK, WD2_BIT_DCB_SERDES_TRAIN_OFS, value);
}

unsigned int WDB::GetTCBSerdesTrain()
// enable training pattero for TCB serdes connection
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_TCB_SERDES_TRAIN_MASK, WD2_BIT_TCB_SERDES_TRAIN_OFS);
}

void WDB::SetTCBSerdesTrain(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_TCB_SERDES_TRAIN_MASK, WD2_BIT_TCB_SERDES_TRAIN_OFS, value);
}

unsigned int WDB::GetInterPacketDelay()
// delay between transmission of two UDP packages (in ticks?)
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_INTER_PKG_DELAY_MASK, WD2_BIT_INTER_PKG_DELAY_OFS);
}

void WDB::SetInterPacketDelay(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_INTER_PKG_DELAY_MASK, WD2_BIT_INTER_PKG_DELAY_OFS, value);
}

void WDB::ResetDAQPLL()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DAQ_PLL_RST_MASK, WD2_BIT_DAQ_PLL_RST_OFS, 1);
}

void WDB::ResetDCBOserdesPLL()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DCB_OSERDES_PLL_RST_MASK, WD2_BIT_DCB_OSERDES_PLL_RST_OFS, 1);
}

void WDB::ResetDCBOserdesIF()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DCB_OSERDES_IF_RST_MASK, WD2_BIT_DCB_OSERDES_IF_RST_OFS, 1);
}

void WDB::ResetTCBOserdesPLL()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_TCB_OSERDES_IF_RST_MASK, WD2_BIT_TCB_OSERDES_IF_RST_OFS, 1);
}

void WDB::ResetTCBOserdesIF()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_TCB_OSERDES_IF_RST_MASK, WD2_BIT_TCB_OSERDES_IF_RST_OFS, 1);
}

void WDB::ResetScaler()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_SCALER_RST_MASK, WD2_BIT_SCALER_RST_OFS, 1);
}

void WDB::ResetTriggerParityErrorCounter()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_TRB_PARITY_ERROR_COUNT_RST_MASK, WD2_BIT_TRB_PARITY_ERROR_COUNT_RST_OFS, 1);
}

void WDB::LMKSyncLocal()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_LMK_SYNC_LOCAL_MASK, WD2_BIT_LMK_SYNC_LOCAL_OFS, 1);
}

void WDB::ResetADCIF()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_ADC_IF_RST_MASK, WD2_BIT_ADC_IF_RST_OFS, 1);
}

void WDB::ResetPackager()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_WD_PKGR_RST_MASK, WD2_BIT_WD_PKGR_RST_OFS, 1);
}

void WDB::ResetEventCounter()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_EVENT_COUNTER_RST_MASK, WD2_BIT_EVENT_COUNTER_RST_OFS, 1);
}

void WDB::ResetDRSControlFSM()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DRS_CTRL_FSM_RST_MASK, WD2_BIT_DRS_CTRL_FSM_RST_OFS, 1);
}

void WDB::ReconfigureFPGA()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_RECONFIGURE_FPGA_MASK, WD2_BIT_RECONFIGURE_FPGA_OFS, 1);
}

void WDB::ApplyDRSSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_DRS_MASK, WD2_BIT_APPLY_SETTINGS_DRS_OFS, 1);
}

void WDB::ApplyDACSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_DAC_MASK, WD2_BIT_APPLY_SETTINGS_DAC_OFS, 1);
}

void WDB::ApplyFrontendSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_DRS_MASK, WD2_BIT_APPLY_SETTINGS_DRS_OFS, 1);
}

void WDB::ApplyControlSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_CTRL_MASK, WD2_BIT_APPLY_SETTINGS_CTRL_OFS, 1);
}

void WDB::ApplyADCSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_ADC_MASK, WD2_BIT_APPLY_SETTINGS_ADC_OFS, 1);
}

void WDB::ApplyLMKSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_LMK_MASK, WD2_BIT_APPLY_SETTINGS_LMK_OFS, 1);
}

unsigned int WDB::GetDacRofs()
{
   return bitExtract(creg, WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_A_MASK, WD2_BIT_DAC0_CH_A_OFS);
}

void WDB::SetDacRofs(unsigned int v)
{
   SetRegMask(WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_A_MASK, WD2_BIT_DAC0_CH_A_OFS, 1);
}

unsigned int WDB::GetDacOfs()
{
   return bitExtract(creg, WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_B_MASK, WD2_BIT_DAC0_CH_B_OFS);
}

void WDB::SetDacOfs(unsigned int v)
{
   SetRegMask(WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_B_MASK, WD2_BIT_DAC0_CH_B_OFS, 1);
}

unsigned int WDB::GetDacCalDc()
{
   return bitExtract(creg, WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_C_MASK, WD2_BIT_DAC0_CH_C_MASK);
}

void WDB::SetDacCalDc(unsigned int v)
{
   SetRegMask(WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_C_MASK, WD2_BIT_DAC0_CH_C_OFS, 1);
}

unsigned int WDB::GetDacPulseAmp()
{
   return bitExtract(creg, WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_D_MASK, WD2_BIT_DAC0_CH_D_OFS);
}

void WDB::SetDacPulseAmp(unsigned int v)
{
   SetRegMask(WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_D_MASK, WD2_BIT_DAC0_CH_D_OFS, 1);
}

unsigned int WDB::GetDacPZCLevel()
{
   return bitExtract(creg, WD2_REG_DAC0_E_F_OFS, WD2_BIT_DAC0_CH_E_MASK, WD2_BIT_DAC0_CH_E_OFS);
}

void WDB::SetDacPZCLevel(unsigned int v)
{
   SetRegMask(WD2_REG_DAC0_E_F_OFS, WD2_BIT_DAC0_CH_E_MASK, WD2_BIT_DAC0_CH_E_OFS, 1);
}

unsigned int WDB::GetDacBias()
{
   return bitExtract(creg, WD2_REG_DAC0_G_H_OFS, WD2_BIT_DAC0_CH_H_MASK, WD2_BIT_DAC0_CH_H_OFS);
}

void WDB::SetDacBias(unsigned int v)
{
   SetRegMask(WD2_REG_DAC0_G_H_OFS, WD2_BIT_DAC0_CH_H_MASK, WD2_BIT_DAC0_CH_H_OFS, 1);
}

float WDB::GetDacTlevel(int chn)
{
   unsigned int v;
   
   assert(chn < 16);
   if (chn % 2 == 0)
      v = bitExtract(creg, WD2_REG_DAC1_A_B_OFS/4+(chn/2), WD2_BIT_DAC1_CH_A_MASK, WD2_BIT_DAC1_CH_A_OFS);
   else
      v = bitExtract(creg, WD2_REG_DAC1_A_B_OFS/4+(chn/2), WD2_BIT_DAC1_CH_B_MASK, WD2_BIT_DAC1_CH_B_OFS);
   
   // convert to Volts taking WDB comparator offset into account
   return ((v / 4095.0 * 2500) - 900) / 500.0;
}

void WDB::SetDacTlevel(int chn, float v)
{
   // convert to mV taking WDB comparator offset into account
   v = v*500 + 900;
   
   // convert from mV to DAC bits
   auto d = (unsigned int)(v / 2500.0 * 4095 + 0.5);
   
   assert(chn < 16);
   if (chn % 2 == 0)
      SetRegMask(WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_A_MASK, WD2_BIT_DAC1_CH_A_OFS, d);
   else
      SetRegMask(WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_B_MASK, WD2_BIT_DAC1_CH_B_OFS, d);
}

unsigned int WDB::GetFEPZC(int chn)
// pole-zero canellation
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_MASK : WD2_BIT_FE1_PZC_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_OFS  : WD2_BIT_FE1_PZC_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFEPZC(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_MASK : WD2_BIT_FE1_PZC_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_OFS  : WD2_BIT_FE1_PZC_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFEAmp2Comp(int chn)
// amplifier 2 compensation enable
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFEAmp2Comp(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFEAmp2Enable(int chn)
// amplifier 2 enable (gain 10)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFEAmp2Enable(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFEAmp1Comp(int chn)
// amplifier 1 compensation enable
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFEAmp1Comp(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFEAmp1Enable(int chn)
// amplifier 1 enable (gain 10)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFEAmp1Enable(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFEAttenuation(int chn)
// attenuation: 0 = 0dB / 1 = 6dB / 2 = 12dB / 8 = 18dB
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_MASK : WD2_BIT_FE1_ATTENUATION_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_OFS  : WD2_BIT_FE1_ATTENUATION_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFEAttenuation(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_MASK : WD2_BIT_FE1_ATTENUATION_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_OFS  : WD2_BIT_FE1_ATTENUATION_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFEMux(int chn)
// multiplexer: 0 = next channel / 1 = previous channel / 2 = input / 3 = cal source
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_MASK : WD2_BIT_FE1_MUX_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_OFS  : WD2_BIT_FE1_MUX_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFEMux(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_MASK : WD2_BIT_FE1_MUX_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_OFS  : WD2_BIT_FE1_MUX_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetLMK(int reg)
{
   assert(reg < 16);
   return creg[WD2_REG_LMK_0_OFS/4+reg];
}

void WDB::SetLMK(int reg, unsigned int v)
{
   assert(reg < 16);
   SetRegMask(WD2_REG_LMK_0_OFS+reg*4, 0xFFFFFFFF, 0, v);
}

bool WDB::IsTriggerShaperEnable()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_SHAPER_ENABLE_MASK, WD2_BIT_TRIGGER_SHAPER_ENABLE_OFS);
}

void WDB::SetTriggerShaperEnable(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_SHAPER_ENABLE_MASK, WD2_BIT_TRIGGER_SHAPER_ENABLE_OFS, 1);
}

unsigned int WDB::GetTriggerPulseLength()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_OFS);
}

void WDB::SetTriggerPulseLength(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_OFS, 1);
}

bool WDB::IsTriggerEnable()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_ENABLE_MASK, WD2_BIT_TRIGGER_ENABLE_OFS);
}

void WDB::SetTriggerEnable(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_ENABLE_MASK, WD2_BIT_TRIGGER_ENABLE_OFS, 1);
}

bool WDB::IsTriggerFallingEdge()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_FALLING_EDGE_MASK, WD2_BIT_TRIGGER_FALLING_EDGE_OFS);
}

void WDB::SetTriggerFallingEdge(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_FALLING_EDGE_MASK, WD2_BIT_TRIGGER_FALLING_EDGE_OFS, 1);
}

bool WDB::IsTriggerExternalOr()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_OR_MASK, WD2_BIT_TRIGGER_CFG_EXT_OR_OFS);
}

void WDB::SetTriggerExternalOr(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_OR_MASK, WD2_BIT_TRIGGER_CFG_EXT_OR_OFS, 1);
}

bool WDB::IsTriggerExternalAnd()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_AND_MASK, WD2_BIT_TRIGGER_CFG_EXT_AND_OFS);
}

void WDB::SetTriggerExternalAnd(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_AND_MASK, WD2_BIT_TRIGGER_CFG_EXT_AND_OFS, 1);
}

bool WDB::IsTriggerDelayEnable()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_ENABLE_MASK, WD2_BIT_TRIGGER_DELAY_ENABLE_OFS);
}

void WDB::SetTriggerDelayEnable(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_ENABLE_MASK, WD2_BIT_TRIGGER_DELAY_ENABLE_OFS, 1);
}

unsigned int WDB::GetTriggerDelay()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_MASK, WD2_BIT_TRIGGER_DELAY_OFS);
}

void WDB::SetTriggerDelay(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_MASK, WD2_BIT_TRIGGER_DELAY_OFS, 1);
}

unsigned int WDB::GetTriggerComparatorMask()
{
   return bitExtract(creg, WD2_REG_TRG_COMP_MASK_OFS, WD2_BIT_TRIGGER_COMP_MASK_MASK, WD2_BIT_TRIGGER_COMP_MASK_OFS);
}

void WDB::SetTriggerComparatorMask(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_COMP_MASK_OFS, WD2_BIT_TRIGGER_COMP_MASK_MASK, WD2_BIT_TRIGGER_COMP_MASK_OFS, 1);
}

unsigned int WDB::GetTriggerCfgOr()
{
   return bitExtract(creg, WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_OR_MASK, WD2_BIT_TRIGGER_CFG_OR_OFS);
}

void WDB::SetTriggerCfgOr(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_OR_MASK, WD2_BIT_TRIGGER_CFG_OR_OFS, 1);
}

unsigned int WDB::GetTriggerCfgAnd()
{
   return bitExtract(creg, WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_AND_MASK, WD2_BIT_TRIGGER_CFG_AND_OFS);
}

void WDB::SetTriggerCfgAnd(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_AND_MASK, WD2_BIT_TRIGGER_CFG_AND_OFS, 1);
}

unsigned int WDB::GetTriggerLocalScheme()
// 0 = simple trigger / 2 = pattern trigger
{
   return bitExtract(creg, WD2_REG_TRG_SCH_SEL_OFS, WD2_BIT_PATTERN_TRIGGER_SELECT_MASK, WD2_BIT_PATTERN_TRIGGER_SELECT_OFS);
}

void WDB::SetTriggerLocalScheme(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_SCH_SEL_OFS, WD2_BIT_PATTERN_TRIGGER_SELECT_MASK, WD2_BIT_PATTERN_TRIGGER_SELECT_OFS, 1);
}

unsigned int WDB::GetTriggerBackplaneScheme(int chn)
{
   assert(chn < 8);
   auto mask = WD2_BIT_BACKPLANE_TRIGGER0_MASK >> (chn * 2);
   return bitExtract(creg, WD2_REG_TRG_SCH_SEL_OFS, mask, WD2_BIT_BACKPLANE_TRIGGER0_OFS - chn * 2);
}

void WDB::SetTriggerBackplaneScheme(int chn, unsigned int v)
{
   assert(chn < 8);
   auto mask = WD2_BIT_BACKPLANE_TRIGGER0_MASK >> (chn * 2);
   SetRegMask(WD2_REG_TRG_SCH_SEL_OFS, mask, WD2_BIT_BACKPLANE_TRIGGER0_OFS - chn * 2, v);
}

unsigned int WDB::GetTriggerPatternEnLocal()
// a 1 enables the corresponding trigger pattern for the local trigger
{
   return bitExtract(creg, WD2_REG_TRG_PTRN_EN_LOCAL_OFS, WD2_BIT_TRG_PTRN_EN_LOCAL_MASK, WD2_BIT_TRG_PTRN_EN_LOCAL_OFS);
}

void WDB::SetTriggerPatternEnLocal(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_PTRN_EN_LOCAL_OFS, WD2_BIT_TRG_PTRN_EN_LOCAL_MASK, WD2_BIT_TRG_PTRN_EN_LOCAL_OFS, v);
}

unsigned int WDB::GetTriggerPatternEnBackplane(int chn)
// a 1 enables the corresponding trigger pattern for the local trigger
{
   assert(chn < 8);
   return bitExtract(creg, WD2_REG_TRG_PTRN_EN_BPL0_OFS+chn*4, WD2_BIT_TRG_PTRN_EN_BPL0_MASK, WD2_BIT_TRG_PTRN_EN_BPL0_OFS);
}

void WDB::SetTriggerPatternEnBackplane(int chn, unsigned int v)
{
   assert(chn < 8);
   SetRegMask(WD2_REG_TRG_PTRN_EN_BPL0_OFS+chn*4, WD2_BIT_TRG_PTRN_EN_BPL0_MASK, WD2_BIT_TRG_PTRN_EN_BPL0_OFS, v);
}

unsigned int WDB::GetTriggerPattern(int i)
{
   assert(i < 32);
   return bitExtract(creg, WD2_REG_TRG_PTRN0_OFS+i*4, WD2_BIT_TRG_PTRN0_MASK, WD2_BIT_TRG_PTRN0_OFS);
}

void WDB::SetTriggerPattern(int i, unsigned int v)
{
   assert(i < 32);
   SetRegMask(WD2_REG_TRG_PTRN0_OFS+i*4, WD2_BIT_TRG_PTRN0_MASK, WD2_BIT_TRG_PTRN0_OFS, v);
}

unsigned int WDB::GetCrc32RegBank()
{
   return bitExtract(creg, WD2_REG_CRC32_REG_BANK_OFS, WD2_BIT_CRC32_REG_BANK_MASK, WD2_BIT_CRC32_REG_BANK_OFS);
}

//--------------------------------------------------------------------

   /*
   SetGain(ts->wdb[iwd].gain);
   SetPZC(ts->wdb[iwd].pzc);
   SetTriggerLevel(&ts->wdb[iwd].trigger_level[0]);
   SetClockSource(1);
   SetSamplingFrequency(ts->wdb[iwd].sampling_frequency);
   
   // Now some trigger setup: comparator mask and patterns
   SetMasks(ts, iwd);
   SetPatterns(ts, iwd);
   
   ConfigureBoard(iwd);
   
   // load voltage calibration for board from file (for now...)
   sprintf(str, "/home/meg/meg2/online/frontends/wd_fe/calib/%s.vcal", fName);
   int fh = open(str, O_RDONLY, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot find voltage calibration file \"")+str+"\""".");
   
   size = read(fh, &fVCalib, sizeof(VCALIB_DATA));
   if (size != sizeof(VCALIB_DATA)) {
      close(fh);
      throw std::runtime_error(std::string("Invalid voltage calibration file size of \"")+str+"\""".");
   }
   
   if (memcmp(fVCalib.version_id, "CAL1", 4) != 0) {
      close(fh);
      throw std::runtime_error(std::string("Invalid voltage calibration file format in \"")+str+"\""".");
   }
   
   // set sampling frequency from calibration data
   if (fabs(fVCalib.sampling_frequency - fSamplingFrequency) > 0.01) {
      char err[1000];
      sprintf(err, "Warning: Voltage calibration data in \"%s/%s\" is for %3g GSPS, running now at %3g GSPS\n",
              dir, str, fVCalib.sampling_frequency, fSamplingFrequency);
      close(fh);
      throw std::runtime_error(std::string(err));
   }
   close(fh);
   
   // load timing calibration for board from file (for now...)
   sprintf(str, "/home/meg/meg2/online/frontends/wd_fe/calib/%s.tcal", fName);
   fh = open(str, O_RDONLY, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot find time calibration file \"")+str+"\""".");
   
   size = read(fh, &fTCalib, sizeof(TCALIB_DATA));
   if (size != sizeof(TCALIB_DATA)) {
      close(fh);
      throw std::runtime_error(std::string("Invalid time calibration file size of \"")+str+"\""".");
   }
   
   if (memcmp(fTCalib.version_id, "CAL1", 4) != 0) {
      close(fh);
      throw std::runtime_error(std::string("Invalid time calibration file format in \"")+str+"\""+".");
   }
   
   close(fh);

    */
/*-----------------------------------------------------------------------------------------*/

/*
int WDB::Init(TRIGGER_SETTINGS *ts, int iwd)
{
   struct sockaddr_in server_addr;
   struct sockaddr_in client_addr;
   char str[256], dir[256];
   struct hostent *phe;
   int size;
   
#ifdef _MSC_VER
   {
   WSADATA WSAData;
   
   // Start windows sockets
   if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
   return -1;
   }
#endif

   // create UDB socket for command interpreter on any port
   fCmdSocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(fCmdSocket);
   
   // create UDB socket to receive binary data on port WD2_DATA_PORT
   if (fDataSocket == 0) {
      fDataSocket = socket(AF_INET, SOCK_DGRAM, 0);
      assert(fDataSocket);
      
      // bind socket to port chosen by OS
      memset((char*)&server_addr, 0, sizeof(server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(0); // let OS choose port
      server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      if (bind(fDataSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
         perror("bind");
         throw std::runtime_error(std::string("Cannot bind socket"));
      }
      size = sizeof(server_addr);
      getsockname(fDataSocket, (struct sockaddr *) &server_addr, (socklen_t *) &size);
      fServerPort = ntohs(server_addr.sin_port);
      
      if (this.mDebug)
         std::cout << "Listening on data port " << fServerPort << std::endl;
   }
   
   // retrieve Ethernet address of board
   phe = gethostbyname(fName);
   if (phe == NULL)
      throw std::runtime_error(std::string("Cannot resolve host name ")+fName);

   memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
   client_addr.sin_family = AF_INET;
   client_addr.sin_port = htons(WD2_CMD_PORT);
   size = sizeof(client_addr);
   memcpy(fEthAddr, &client_addr, sizeof(client_addr));
   
   // check if board is alive
   try {
      SendReceive("", NULL, NULL, 500);
   } catch (...) {
      throw std::runtime_error(std::string("Cannot connect to board ")+fName);
   }
   
   // derive serial number from network name (for now...)
   fSerialNumber = atoi(fName+2);
   
   // set dbglevel none
   Send("dbglvl none");
   
   // set destinantion port in WD board
   sprintf(str, "setenv dstport %d", fServerPort);
   Send(str);
   
   // set MAC address and IP address of this computer in WD board
   Send("cfgdst");
   
   SetGain(ts->wdb[iwd].gain);
   SetPZC(ts->wdb[iwd].pzc);
   SetTriggerLevel(&ts->wdb[iwd].trigger_level[0]);
   SetClockSource(1);
   SetSamplingFrequency(ts->wdb[iwd].sampling_frequency);
  
   // Now some trigger setup: comparator mask and patterns
   SetMasks(ts, iwd);
   SetPatterns(ts, iwd);

   ConfigureBoard(iwd);
   
   // load voltage calibration for board from file (for now...)
   sprintf(str, "/home/meg/meg2/online/frontends/wd_fe/calib/%s.vcal", fName);
   int fh = open(str, O_RDONLY, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot find voltage calibration file \"")+str+"\"");

   size = read(fh, &fVCalib, sizeof(VCALIB_DATA));
   if (size != sizeof(VCALIB_DATA)) {
      close(fh);
      throw std::runtime_error(std::string("Invalid voltage calibration file size of \"")+str+"\"");
   }

   if (memcmp(fVCalib.version_id, "CAL1", 4) != 0) {
      close(fh);
      throw std::runtime_error(std::string("Invalid voltage calibration file format in \"")+str+"\"");
   }
   
   // set sampling frequency from calibration data
   if (fabs(fVCalib.sampling_frequency - fSamplingFrequency) > 0.01) {
      char err[1000];
      sprintf(err, "Warning: Voltage calibration data in \"%s/%s\" is for %3g GSPS, running now at %3g GSPS\n",
              dir, str, fVCalib.sampling_frequency, fSamplingFrequency);
      close(fh);
      throw std::runtime_error(std::string(err));
   }
   close(fh);
   
   // load timing calibration for board from file (for now...)
   sprintf(str, "/home/meg/meg2/online/frontends/wd_fe/calib/%s.tcal", fName);
   fh = open(str, O_RDONLY, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot find time calibration file \"")+str+"\"");

   size = read(fh, &fTCalib, sizeof(TCALIB_DATA));
   if (size != sizeof(TCALIB_DATA)) {
      close(fh);
      throw std::runtime_error(std::string("Invalid time calibration file size of \"")+str+"\"");
   }
   
   if (memcmp(fTCalib.version_id, "CAL1", 4) != 0) {
      close(fh);
      throw std::runtime_error(std::string("Invalid time calibration file format in \"")+str+"\"");
   }
   
   close(fh);
   
   return SUCCESS;
}


void WDB::SetTriggerLevel(int *tl)
{
   fTriggerLevel[0] = tl[0];
   fTriggerLevel[1] = tl[1];
   fTriggerLevel[2] = tl[2];
   fTriggerLevel[3] = tl[3];
}


void WDB::ConfigureBoard(int iwd)
{
   char str[80];
   int byte;
   
   // set LED red
   Send("ledset r");

   // set dbglevel none
   Send("dbglvl none");
   
   // set input configuration
   byte = 0;
   if (fPZC) { // pole zero cancellation on (bit=0)
      if (fGain == 0)
         byte = 0x02;
      else if (fGain == 1)
         byte = 0x0a;
      else if (fGain == 2)
         byte = 0x2a;
   } else { // pole zero cancellation off (bit=1)
      if (fGain == 0)
         byte = 0x82;
      else if (fGain == 1)
         byte = 0x8a;
      else if (fGain == 2)
         byte = 0xaa;
   }
   
   sprintf(str, "feset all %02X", byte);
   Send(str);
   
   // trun on comparator power
   Send("pwrcmp on");

   // set comparator level
   Send("dacset tlevel1 %d", fTriggerLevel[0]/2+900);
   Send("dacset tlevel2 %d", fTriggerLevel[1]/2+900);
   Send("dacset tlevel3 %d", fTriggerLevel[2]/2+900);
   Send("dacset tlevel4 %d", fTriggerLevel[3]/2+900);

   // set range to -0.95V ... +0.05V
   if (fGain == 2)
      Send("dacset ofs 1640");
   else
      Send("dacset ofs 2000");
   
   // set DACs
   Send("dacset bias 700");
   Send("dacset rofs 1550");
   Send("dacset caldc 1280");

   // disable local trigger
   Send("regwr %02x 00000000", WD2_REG_TRIGGER_CFG_A_OFS);
   
   // trigger_enable, trigger_falling_edge, enable external trigger
   // set the trigger delay to be 0x3F and the signal shaping 4 (80MHz clk cycles)
   Send("regwr %02x 040E0034", WD2_REG_TRIGGER_CFG_OFS);
   
   // set DRS readout mode to ROI and drs_active
   Send("regwr %02x 17170030", WD2_REG_CONTROL_OFS);
   
   // set clock source
   if (fClockSource == 1)
      Send("regclr %02x 20000", WD2_REG_CLK_CALIB_CTRL_OFS);
   else
      Send("regset %02x 20000", WD2_REG_CLK_CALIB_CTRL_OFS);
   
   // set inter-packet delay
   Send("regwr %02x FF00", WD2_REG_COM_CONTROL_OFS);
   
   // set LMK registers to their defaults, see "LMK regs.xls"
   Send("regwr %02x 00032800", WD2_REG_LMK_0_OFS);
   Send("regwr %02x 00020101", WD2_REG_LMK_1_OFS);
   Send("regwr %02x 00020102", WD2_REG_LMK_2_OFS);
   Send("regwr %02x 029900AD", WD2_REG_LMK_13_OFS);
   Send("regwr %02x 0830140E", WD2_REG_LMK_14_OFS);
   Send("regwr %02x D800280F", WD2_REG_LMK_15_OFS);

   // set LMK register to current sampling frequency
   int divider = (int) (200.0 / fSamplingFrequency * 2.048 / 2 + 0.5);
   Send("regwr %02x 0003%02X00", WD2_REG_LMK_0_OFS, divider);

   // initialize FSM and frame counter
   Send("drsreinit");
   
   // set LED red
   Send("ledset g");
}


int WDB::StartDRS()
{
   return Send("drsstart");
}


#define Sleep(x) usleep(x*1000)

double time_ms()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec*1000 + tv.tv_usec/1000.0;
}


namespace {
  // waveform buffer for one event
  float wf[16][16][1024];
  float waveform[16][16][1024];
  int   triggerCell[16][2];
  float wft[16][16][1024];
  float wftime[16][16][1024];
  int   new_event = 0;
  int   _nWdb;
}

void *wdb_collector(void *param);


int wdb_start_collector(WDB *wdb[], int nWdb)
{
   INT status;
   pthread_t thread_id;

   _nWdb = nWdb;
   status = pthread_create(&thread_id, NULL, wdb_collector, (void *)wdb);
   return status;
}

int wdb_read_waveform(float *pwf, int *ptc, float *pwft)
{
   double start_time;
   
   start_time = time_ms();
   while (!new_event) {
      sleep(10);
      
      // time-out after one second
      if (time_ms() - start_time > 1000)
         return 0;
   }
   
   memcpy(pwf, waveform, sizeof(float)*_nWdb*16*1024);
   memcpy(ptc, triggerCell, sizeof(int)*_nWdb*2);
   memcpy(pwft, wftime, sizeof(float)*_nWdb*16*1024);
   
   new_event = 0;
   return 1;
}

void *wdb_collector(void *param)
{
   int i, b, c, s, status, current_frame, np;
   fd_set readfds;
   struct timeval timeout;
   struct sockaddr_in remote_addr;
   WD2_FRAME_HEADER *ph;
   unsigned char *pd;
   short data1, data2;
   unsigned char buffer[1800];
   int header_adc, header_channel, waveform_channel, board;

   WDB **wdb = (WDB **)param;
   s = wdb[0]->fDataSocket;
   current_frame = -1;
   np = 0;
   for (int b=0 ; b<_nWdb ; b++)
      for (int c=0 ; c<16 ; c++) {
         wf[b][c][0]   = nanf("");
         wf[b][c][512] = nanf("");
      }

   while (1) {

      FD_ZERO(&readfds);
      FD_SET(s, &readfds);
      
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      
      do {
         status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
      } while (status == -1 && errno == EINTR);  // don't return if an alarm signal was caught
      
      if (status == -1)
         perror("select");
      
      if (FD_ISSET(s, &readfds)) {
         int len, n;
         
         // packet is available, so receive it
         len = sizeof(remote_addr);
         n = (int)recvfrom(s, (char *)buffer, sizeof(buffer), 0,
                           (struct sockaddr *)&remote_addr, (socklen_t *)&len);
         if (n > (int)sizeof(WD2_FRAME_HEADER)) {
            ph = (WD2_FRAME_HEADER *)buffer;
            np++;
            
            // correct endianness of header data
            ph->board_id                 = SWAP_UINT16(ph->board_id);
            header_adc                   = (ph->adc_and_channel_info >> 4) & 0x0f;
            header_channel               = (ph->adc_and_channel_info) & 0x0f;
            ph->readout_sequence_number  = SWAP_UINT16(ph->readout_sequence_number);
            ph->hardware_sequence_number = SWAP_UINT16(ph->hardware_sequence_number);
            ph->sampling_frequency       = SWAP_UINT16(ph->sampling_frequency);
            ph->number_of_samples        = SWAP_UINT16(ph->number_of_samples);
            ph->drs0_trigger_cell        = SWAP_UINT16(ph->drs0_trigger_cell);
            ph->drs1_trigger_cell        = SWAP_UINT16(ph->drs1_trigger_cell);
            ph->trigger_type             = SWAP_UINT16(ph->trigger_type);
            ph->packet_sequence_number   = SWAP_UINT16(ph->packet_sequence_number);

            printf("%5d, From %s, Board %2d, Frame %5d, ADC/Chn/Segment %d/%d/%d\n",
                   np,
                   inet_ntoa(remote_addr.sin_addr),
                   ph->board_id,
                   ph->readout_sequence_number,
                   header_adc,
                   header_channel,
                   ph->channel_segment_number);
            
            if (current_frame == -1)
               current_frame = ph->readout_sequence_number;
            
            // drop package if it belongs to older frame
            if (ph->readout_sequence_number < current_frame) {
               printf("Package dropped, package frame=%d, current frame=%d, board id = %d\n", ph->readout_sequence_number, current_frame, ph->board_id);
               continue;
            }
            
            // drop whole frame if package of next frame received
            if (ph->readout_sequence_number > current_frame) {
               printf("Frame dropped, package frame=%d, current frame=%d\n", ph->readout_sequence_number, current_frame);
               
               // switch to new frame
               current_frame = ph->readout_sequence_number;
               
               // tag waveforms as invalid
               for (int b=0 ; b<_nWdb ; b++)
                  for (int c=0 ; c<16 ; c++) {
                     wf[b][c][0]   = nanf("");
                     wf[b][c][512] = nanf("");
                  }

               np = 1;
            }
            
            waveform_channel = header_adc*8+header_channel;
            assert(waveform_channel < 16);
            
            // ensure board id is in our receive list
            for (i=0 ; i<_nWdb ; i++)
               if (ph->board_id == wdb[i]->fSerialNumber)
                  break;
            assert(i < _nWdb);
            board = i;
            
            // copy trigger cell
            if (waveform_channel < 8)
               triggerCell[board][0] = ph->drs0_trigger_cell;
            else
               triggerCell[board][1] = ph->drs1_trigger_cell;
            
            // decode waveform data
            pd = (unsigned char*)(ph+1);
            for (i=0 ; i<512 ; i+=2) {
               data1   = ((pd[1] & 0x0F) << 8) | pd[0];
               if(data1 >= 0x0800) {
                  // expand two's complement
                  data1 -= 0x1000;
               }
               data2 = ((unsigned short)pd[2] << 4) | (pd[1] >> 4);
               if(data2 >= 0x0800) {
                  // expand two's complement
                  data2 -= 0x1000;
               }
               pd+=3;
               
               if (ph->channel_segment_number == 0) {
                  // first segment
                  wf[board][waveform_channel][i]       = (float)data1 * (1 / 4096.0); // 1V DRS range with 12 bits
                  wf[board][waveform_channel][i+1]     = (float)data2 * (1 / 4096.0);
               } else {
                  // second segment
                  wf[board][waveform_channel][512+i]   = (float)data1 * (1 / 4096.0);
                  wf[board][waveform_channel][512+i+1] = (float)data2 * (1 / 4096.0);
               }
            }
         }
      }
      
      // check if we got all fragments
      for (b=i=0 ; b<_nWdb ; b++)
         for (c=0 ; c<16 ; c++)
            if (!isnan(wf[b][c][0]) && !isnan(wf[b][c][512]))
               i++;
      if (i == _nWdb*16) {

         // cell-by-cell offset calibration
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++) {
               int tc = c<8 ? triggerCell[b][0] : triggerCell[b][1];
               for (i=0 ; i<1024 ; i++)
                  wf[b][c][i] -= wdb[b]->fVCalib.wf_OFS1[c][(i+tc)%1024];
            }
         }

         // gain calibration
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++) {
               int tc = c<8 ? triggerCell[b][0] : triggerCell[b][1];
               for (int i=0 ; i<1024 ; i++) {
                  if (wf[b][c][i] > 0)
                     wf[b][c][i] /= wdb[b]->fVCalib.wf_gain1[c][(i+tc) % 1024];
                  else
                     wf[b][c][i] /= wdb[b]->fVCalib.wf_gain2[c][(i+tc) % 1024];
               }
            }
         }

         // start-to-end offset calibration
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++)
               for (i=0 ; i<1024 ; i++)
                  wf[b][c][i] -= wdb[b]->fVCalib.wf_OFS2[c][i];
         }
         
         // range calibration
         for (b=0 ; b<_nWdb ; b++)
            for (c=0 ; c<16 ; c++)
               for (int i=0 ; i<1024 ; i++)
                  wf[b][c][i] -= wdb[b]->fVCalib.drs_OFS_range0[c]; // -0.95 ... 0.05 V

         // calculate calibrated time for each bin

         // integrate time from delta-t values
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++) {
               int tc = c<8 ? triggerCell[b][0] : triggerCell[b][1];
               wft[b][c][0] = 0;
               for (int i=1 ; i<1024 ; i++)
                  wft[b][c][i] = wft[b][c][i-1] + wdb[b]->fTCalib.dt[c][(i-1+tc)%1024];
            }
            // align cell#0 of all channels inside chip0
            float t1 = wft[b][0][(1024-triggerCell[b][0]) % 1024];
            for (c=1 ; c<8 ; c++) {
               float t2 = wft[b][c][(1024-triggerCell[b][0]) % 1024];
               float dt = t1 - t2;
               for (int i=0 ; i<1024 ; i++)
                  wft[b][c][i] += dt;
            }
            // align cell#0 of all channels inside chip1 to chip0
            for (c=8 ; c<16 ; c++) {
               float t2 = wft[b][c][(1024-triggerCell[b][1]) % 1024];
               float dt = t1 - t2;
               for (int i=0 ; i<1024 ; i++)
                  wft[b][c][i] += dt;
            }
         }
         
         // copy waveform to buffer and signal new event
         memcpy(waveform, wf, sizeof(waveform));
         memcpy(wftime, wft, sizeof(wftime));
         new_event = 1;
         current_frame = -1;
         np = 0;

         // tag waveforms as invalid
         for (int b=0 ; b<_nWdb ; b++)
            for (int c=0 ; c<16 ; c++) {
               wf[b][c][0]   = nanf("");
               wf[b][c][512] = nanf("");
            }

      }
   }
}

// this funtion sets a link from WD to TCB to be AND/OR/Pattern
// this is written on the word type
// 0 = AND
// 1 = OR
// 2 = PATTERN
// 3 = UNUSED
void WDB::SetTCBLink(int ltype, int port)
{
   //first reset the bits
   Send("regclr %x %x", WD2_REG_TRIGGER_SCHEME_SELECT_OFS, (3<<14)>>(port*2));
   // then set them
   Send("regset %x %x", WD2_REG_TRIGGER_SCHEME_SELECT_OFS, (ltype<<14)>>(port*2));
}

//THIS FUNCTION SET THE PATTERNS TO A WDB TAKEN FROM ODB (ONE SET FOR THE WHOLE SYSTEM SO FAR)
void WDB::SetPatterns(TRIGGER_SETTINGS *ts,int iwd)
{
   // first load the pattern enable
   for(int ipatten = 0; ipatten<8; ipatten++)
      Send("regwr %x %x", 4*ipatten+WD2_REG_TRIGGER_PATTERN_EN_BPL0_OFS, ts->wdb[iwd].pattern_enable[ipatten]);
   // then load the patterns itself
   for(int ipatt = 0; ipatt<32; ipatt++)
      Send("regwr %x %x", 4*ipatt+WD2_REG_TRIGGER_PATTERN0_OFS, ts->wdb[iwd].pattern[ipatt]);
}

// SET THE MASKS FROM ODB (ONE MASK SETTING PER BOARD PER CHANNEL)
void WDB::SetMasks(TRIGGER_SETTINGS *ts, int iwd)
{
   Send("regwr %x %x", WD2_REG_TRIGGER_COMP_MASK_OFS, ts->wdb[iwd].masks);
}

*/
