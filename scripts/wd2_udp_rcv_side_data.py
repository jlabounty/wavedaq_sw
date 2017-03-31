
import sys
import os
import socket
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
