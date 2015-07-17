
import sys
import socket
import numpy as np
import pylab as pl

# get parameters
#target_adc     = int(sys.argv[1])
#target_channel = int(sys.argv[2])

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

count = 0
while True:
  str_data = sock.recv(784) # buffer size is 1 frame = 25'088 bytes
  count += 1
  #print "received message:", str_data
  print "size:", len(str_data)
  print "count:", count
  print "channel:", hex(np.fromstring(str_data[7], dtype=np.uint8))
  print " "
