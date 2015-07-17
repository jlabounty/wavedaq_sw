
import sys
import socket
import numpy as np
import pylab as pl

# get parameters
nr_of_frames = int(sys.argv[1])
#target_adc     = int(sys.argv[1])
#target_channel = int(sys.argv[2])

UDP_IP = "129.129.195.102"
UDP_PORT = 1850

adcs     = 2
channels = 8
payload_size = 768 # = 512 samples * 1.5 bytes_per_sample
packet_size  = 16 + payload_size # = 16 header_bytes + (512 samples * 1.5 bytes_per_sample) data_bytes
buffer_size  = adcs*channels*2*packet_size # 2 ADCs * 8 channels_per_adc * 2 packets_per_channel * packet_size
samples_per_packet = 512
samples_per_frame  = 2*samples_per_packet

print "Listening to PORT", UDP_PORT
print "..."

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

first_frame = -1
frame_nr = np.full((adcs, channels),-1)
segments = np.full((adcs, channels), 0)

ch_raw_data = np.empty((adcs, channels,2*payload_size), dtype=np.uint8)

header_data_sequ_nr = -1

while header_data_sequ_nr < first_frame+nr_of_frames:
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

  if first_frame == -1:
    first_frame = header_data_sequ_nr

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
  
  # decode data
  if header_ch_segment == 0:
    ch_raw_data[header_adc_nr, header_ch_nr, 0:payload_size] = data[i+16:i+16+payload_size]
    frame_nr[header_adc_nr, header_ch_nr] = header_data_sequ_nr
    segments[header_adc_nr, header_ch_nr] += 1
  elif header_data_sequ_nr == frame_nr[header_adc_nr, header_ch_nr]:
    ch_raw_data[header_adc_nr, header_ch_nr, payload_size:2*payload_size] = data[i+16:i+16+payload_size]
    segments[header_adc_nr, header_ch_nr] += 1
  else:
    frame_nr[header_adc_nr, header_ch_nr] = -1
    segments[header_adc_nr, header_ch_nr] = 0
  
# decode data
time_step_us = 1.0/header_sampling_freq
time = np.arange(1024)*time_step_us

print "plotting...\n"
for adc in np.arange(adcs):
  pl.figure(adc+1)
  for ch in np.arange(channels):
    pl.subplot(4, 2, ch+1)
    ch_data = np.zeros(samples_per_frame, dtype=np.int32)

    if segments[adc, ch] == 2:
      y = 0
      for x in np.arange(0,2*payload_size-1,3):
        ch_data[y]   = np.uint32(ch_raw_data[adc, ch, x+1])%16*256 + np.uint32(ch_raw_data[adc, ch, x+0])
        if ch_data[y] >= 0x0800:
          ch_data[y] = ch_data[y] - 0x1000
        ch_data[y+1] = np.uint32(ch_raw_data[adc, ch, x+2])*16     + np.uint32(ch_raw_data[adc, ch, x+1])/16
        if ch_data[y+1] >= 0x0800:
          ch_data[y+1] = ch_data[y+1] - 0x1000
        y += 2
      pl.title("ADC " + str(adc) + " Channel " + str(ch) + "   Frame " + str(frame_nr[adc, ch]))
    else:
      pl.title("ADC " + str(adc) + " Channel " + str(ch) + "   !!! INVALID !!!")

    pl.plot(time, ch_data)
    pl.grid()
    if ch > 5:
      pl.xlabel("time [us]")
    pl.ylabel("ADC value")
    pl.ylim(np.amin(ch_data)-10,np.amax(ch_data)+10)
    
pl.show()

