
import sys
import socket
import numpy as np
import pylab as pl

# get parameters
target_adc     = int(sys.argv[1])
target_channel = int(sys.argv[2])

UDP_IP = "129.129.195.102"
UDP_PORT = 1850

payload_size = 768 # = 512 samples * 1.5 bytes_per_sample
packet_size  = 16 + payload_size # = 16 header_bytes + (512 samples * 1.5 bytes_per_sample) data_bytes
buffer_size  = packet_size # 2 ADCs * 8 channels_per_adc * 2 packets_per_channel * packet_size
#buffer_size  = 2*8*2*packet_size # 2 ADCs * 8 channels_per_adc * 2 packets_per_channel * packet_size
samples_per_packet = 512
samples_per_frame  = 2*samples_per_packet

print "Listening to PORT", UDP_PORT
print "..."

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

frame_nr = -1
segments = 0

ch_raw_data = np.empty(2*payload_size, dtype=np.uint8)

while segments<2:
  str_data = sock.recv(buffer_size) # buffer size is 1 frame = 25'088 bytes
  #print "received message:", str_data

  data = np.fromstring(str_data, dtype=np.uint8)

  ### start decoding frame ###
  i = 0
  # decode header
  header_protocol_vers  = data[i]
  header_board_id       = data[i+1]*256+data[i+2]
  header_sampling_freq  = data[i+3]*256+data[i+4]
  header_nr_of_samples  = data[i+5]*256+data[i+6]
  header_adc_nr         = data[i+7]/16
  header_ch_nr          = data[i+7]%16
  header_ch_segment     = data[i+8]*256+data[i+9]
  header_data_sequ_nr   = data[i+10]*256+data[i+11]
  header_packet_sequ_nr = data[i+12]*256+data[i+13]
  header_reserved       = data[i+14]*256+data[i+15]

  if (header_adc_nr == target_adc) and (header_ch_nr == target_channel):
    # decode data
    if header_ch_segment == 0:
      ch_raw_data[0:payload_size] = data[i+16:i+16+payload_size]
      frame_nr = header_data_sequ_nr
      segments += 1
    elif header_data_sequ_nr == frame_nr:
      ch_raw_data[payload_size:2*payload_size] = data[i+16:i+16+payload_size]
      segments += 1
    else:
      frame_nr = -1
      segments = 0
  
# decode data
print "Protocol Version.....", header_protocol_vers
print "Board ID.............", header_board_id
print "Sampling Frequency...", header_sampling_freq
print "Nr of Samples........", header_nr_of_samples
print "ADC..................", header_adc_nr
print "Channel..............", header_ch_nr
print "Channel Segment......", header_ch_segment
print "Data Sequence Nr.....", header_data_sequ_nr
print "Packet Sequence Nr...", header_packet_sequ_nr
print "Reserved.............", header_reserved
print " "

#ch_segm_data = np.empty(samples_per_packet, dtype=np.int32)
ch_data = np.empty(samples_per_frame, dtype=np.int32)
y = 0
for x in np.arange(0,2*payload_size-1,3):
  ch_data[y]   = np.uint32(ch_raw_data[x+1])%16*256 + np.uint32(ch_raw_data[x+0])
  if ch_data[y] >= 0x0800:
    ch_data[y] = ch_data[y] - 0x1000
  ch_data[y+1] = np.uint32(ch_raw_data[x+2])*16     + np.uint32(ch_raw_data[x+1])/16
  if ch_data[y+1] >= 0x0800:
    ch_data[y+1] = ch_data[y+1] - 0x1000
  y += 2

#sampling_frequency = header_sampling_freq * 1e6
time_step_us = 1.0/header_sampling_freq
time = np.arange(1024)*time_step_us
#segm_time = np.arange(512)*time_step_us
rms_noise = np.std(ch_data)
print "RMS Noise: " + str(rms_noise) + " LSBs"

print "plotting...\n"
pl.plot(time, ch_data)
pl.grid()
pl.title("Output of ADC " + str(target_adc) + " Channel " + str(target_channel))
pl.xlabel("time [us]")
pl.ylabel("ADC value")
pl.ylim(np.amin(ch_data)-10,np.amax(ch_data)+10)
pl.show()

