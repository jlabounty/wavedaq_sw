
import sys
import socket
import numpy as np
import bytearray as ba

UDP_IP = "129.129.193.58"
UDP_PORT = 4000

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

print "Sending command to to Host %s PORT %d ..." % (UDP_IP, UDP_PORT)

tx_array = bytearray(np.array[0x2400AFFE,0x0,0x1])

sock.sendto(tx_array, (UDP_IP, UDP_PORT))

print "Listening to PORT", UDP_PORT
print "..."

sock.bind((UDP_IP, UDP_PORT))
str_data = sock.recv(buffer_size) # buffer size is 1 frame = 25'088 bytes
#print "received message:", str_data

#data = np.fromstring(str_data, dtype=np.uint8)

#  # decode header
#  header_protocol_vers  = data[i]
#  header_board_id       = data[i+1]*256+data[i+2]
#  header_sampling_freq  = data[i+3]*256+data[i+4]
#  header_nr_of_samples  = data[i+5]*256+data[i+6]
#  header_adc_nr         = data[i+7]/16
#  header_ch_nr          = data[i+7]%16
#  header_ch_segment     = data[i+8]*256+data[i+9]
#  header_data_sequ_nr   = data[i+10]*256+data[i+11]
#  header_packet_sequ_nr = data[i+12]*256+data[i+13]
#  header_reserved       = data[i+14]*256+data[i+15]

