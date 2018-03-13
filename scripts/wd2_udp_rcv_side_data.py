
import sys
import os
import socket
import ctypes 
import numpy as np

UDP_IP = "" #"129.129.188.323"
UDP_PORT = 2000

buffer_size  = 1500 # maximum ethernet payload size

print "Listening to PORT", UDP_PORT
print "..."

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

str_data = sock.recv(buffer_size) # buffer size is 1 frame = 25'088 bytes
#print "received message:", str_data

data = np.fromstring(str_data, dtype=np.uint8)

### start decoding frame ###
# decode header
header_protocol_vers  =  data[0]
header_board_revision =  data[1]
header_board_id       = (data[2]<<8)+data[3]
header_crate_id       =  data[4]
header_slot_id        =  data[5]
header_adc_nr         =  data[6]>>8
header_ch_nr          =  data[6]&0x0F
header_ch_segment_nr  =  data[7]>>8
header_package_type   =  data[7]&0x0F
header_event_nr       = (data[8]<<24)+(data[9]<<16)+(data[10]<<8)+data[11]
header_sampling_freq  = (data[12]<<8)+data[13]
header_payload_length = (data[14]<<8)+data[15]
header_trigger_number = (data[16]<<8)+data[17]
header_drs0_stop_cell = (data[18]<<8)+data[19]
header_drs1_stop_cell = (data[20]<<8)+data[21]
header_trigger_type   = (data[22]<<8)+data[23]
header_temperature    = (data[24]<<8)+data[25]
header_reserved       = (data[26]<<24)+(data[27]<<16)+(data[28]<<8)+data[29]
header_packet_sequ_nr = (data[30]<<8)+data[31]

print "Protocol Version.....", header_protocol_vers
print "Board Revision.......", header_board_revision
print "Board ID.............", header_board_id
print "Crate ID.............", header_crate_id
print "Slot ID..............", header_slot_id
print "ADC..................", header_adc_nr
print "Channel..............", header_ch_nr
print "Channel Segment......", header_ch_segment
print "Package Type.........", header_package_type
print "Event Nr        .....", header_event_nr
print "Sampling Frequency...", header_sampling_freq
print "Payload Length.......", header_payload_length
print "Trigger Nr...........", header_trigger_number
print "DRS0 Stop Cell.......", header_drs0_stop_cell
print "DRS1 Stop Cell.......", header_drs1_stop_cell
print "Trigger Type.........", header_trigger_type
print "Temperature..........", header_temperature
print "Reserved.............", header_reserved
print "Packet Sequence Nr...", header_packet_sequ_nr
print " "
print " "

# decode data

path = os.path.abspath('.')
outfile = "udp_rcv_data.dat"
out_file = file(path+os.sep+outfile,'w')

data_size = 32+header_payload_length
if data_size > buffer_size:
  data_size = buffer_size

for i in np.arange(32,data_size):
  outline = data[i]
  out_file.write(outline)

out_file.close()

#-----------------------------------------------
# Header
#-----------------------------------------------

class header_struct(ctypes.BigEndianStructure):  # ctypes.Structure / ctypes.LittleEndianStructure
  _pack_   = 1  # alignment to 1 byte only, must be defined before __fields__
  _fields_ = [
               ('protocol_version'         , ctypes.c_uint8),      # 1 byte  Protocol_Version                   
               ('board_revision'           , ctypes.c_uint8),      # 1 byte  Board_Revision               
               ('board_id'                 , ctypes.c_uint16),     # 2 byte  Board_ID                                   
               ('crate_id'                 , ctypes.c_uint8),      # 1 byte  Crate_ID                   
               ('slot_id'                  , ctypes.c_uint8),      # 1 byte  Slot_ID                  
               ('adc'                      , ctypes.c_uint8, 1),   # 1 bit   ADC 
               ('channel'                  , ctypes.c_uint8, 7),   # 7 bit   Channel
               ('data_type'                , ctypes.c_uint8, 8),   # 4 bit   package type
               ('tx_enable'                , ctypes.c_uint32),     # 4 byte  TX_Enable
               ('reserved_flag0'           , ctypes.c_uint8, 6),   # 6 bit   reserved
               ('trig_info_perr_flag'      , ctypes.c_uint8, 1),   # 1 bit   Trigger_Info_Parity_Error_Flag
               ('trig_info_new_flag'       , ctypes.c_uint8, 1),   # 1 bit   Trigger_Info_New_Flag
               ('reserved_flag1'           , ctypes.c_uint8, 2),   # 2 bit   reserved
               ('start_of_type_flag'       , ctypes.c_uint8, 1),   # 1 bit   Start_of_Type_Flag
               ('end_of_type_flag'         , ctypes.c_uint8, 1),   # 1 bit   End_of_Type_Flag
               ('reserved_flag2'           , ctypes.c_uint8, 2),   # 2 bit   reserved
               ('daq_pll_lock_flag'        , ctypes.c_uint8, 1),   # 1 bit   DAQ_PLL_Lock_Flag
               ('drs_pll_lock_flag'        , ctypes.c_uint8, 1),   # 1 bit   DRS_PLL_Lock_Flag
               ('trigger_source'           , ctypes.c_uint8),      # 1 byte  Trigger_Source
               ('bits_per_sample'          , ctypes.c_uint8),      # 1 byte  Bits_per_Sample
               ('samples_per_event_per_ch' , ctypes.c_uint16),     # 2 byte  Samples_per_Event_per_Channel
               ('payload_length'           , ctypes.c_uint16),     # 2 byte  Payload_Length in ...
               ('data_offset'              , ctypes.c_uint16),     # 2 byte  Data_Offset in ...
               ('trigger_info2'            , ctypes.c_uint16),     # 2 byte  Trigger_Info (MSBs, Trigger_Type)
               ('trigger_info1'            , ctypes.c_uint16),     # 2 byte  Trigger_Info (Reserved)
               ('trigger_info0'            , ctypes.c_uint16),     # 2 byte  Trigger_Info (LSBs, Trigger_Number)
               ('event_number'             , ctypes.c_uint32),     # 4 byte  Event_Number             
               ('time_stamp'               , ctypes.c_uint64),     # 8 byte  Time_Stamp
               ('sampling_frequency'       , ctypes.c_uint32),     # 4 byte  Sampling_Frequency
               ('drs_trigger_cell'         , ctypes.c_uint16),     # 2 byte  DRS_Trigger_Cell                              
               ('temperature'              , ctypes.c_uint16),     # 2 byte  Temperature                                  
               ('dac_ofs'                  , ctypes.c_uint16),     # 2 byte  DAC_OFS DAC channel
               ('dac_rofs'                 , ctypes.c_uint16),     # 2 byte  DAC_ROFS DAC channel
               ('frontend_settings'        , ctypes.c_uint16),     # 2 byte  Frontend_Settings
               ('reserved2'                , ctypes.c_uint16),     # 2 byte  Reserved                               
               ('reserved1'                , ctypes.c_uint32),     # 4 byte  Reserved
               ('reserved0'                , ctypes.c_uint32),     # 4 byte  Reserved
             ]

  def info(self):
    for a in self._fields_:
      print ("%-25s : %8d"%(a[0], self.__getattribute__(a[0])))

#-----------------------------------------------