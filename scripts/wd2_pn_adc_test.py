
import datetime as dt
import sys
import numpy as np
import pylab as pl

if len(sys.argv) > 1:
  test_adc = int(sys.argv[1])
  test_ch  = int(sys.argv[2])
else:
  test_adc = 0
  test_ch  = 0

pn       = 9

# returns next value in pseudo random functions from
# polynomes PN23 = X^23 + X^18 + 1 (seed value 0x0007FF)
#        or PN9  = X^9  + X^5  + 1 (seed value 0x0007E0)
def pn_next( pn_type, current_value):
  if pn_type == 9:
    sr_value = current_value
    for i in np.arange(1,13):
      next_lsb = ((sr_value >> 8) ^ (sr_value >> 4)) & 0x01
      sr_value = (sr_value << 1) | next_lsb
  elif pn_type == 23:
    sr_value = 0x0007FF
    while (sr_value & 0x0FFF) != current_value:
      next_lsb = ((sr_value >> 22) ^ (sr_value >> 17)) & 0x01
      sr_value = (sr_value << 1) | next_lsb
    for i in np.arange(1,13):
      next_lsb = ((sr_value >> 22) ^ (sr_value >> 17)) & 0x01
      sr_value = (sr_value << 1) | next_lsb
  next_value = sr_value & 0x0FFF
  return next_value

# polynomes PN23 = X^23 + X^18 + 1 (seed value 0x0007FF)
#        or PN9  = X^9  + X^5  + 1 (seed value 0x0007E0)
def get_pn_seq( pn_type, start_value):
  calc = np.arange(1024)
  if pn_type == 9:
    sr_value = 0x0007E0
    while (sr_value & 0x0FFF) != (start_value & 0x0FFF):
      next_lsb = ((sr_value >> 8) ^ (sr_value >> 4)) & 0x01
      sr_value = (sr_value << 1) | next_lsb
    calc[0] = start_value
    for i in np.arange(1,1023):
      for j in np.arange(1,13):
        next_lsb = ((sr_value >> 8) ^ (sr_value >> 4)) & 0x01
        sr_value = (sr_value << 1) | next_lsb
      next_value = sr_value & 0x0FFF
      #if next_value > 0x7FF:
      #  next_value = next_value - 0x1000
      calc[i] = next_value
  elif pn_type == 23:
    sr_value = 0x0007FF
    while (sr_value & 0x0FFF) != (start_value & 0x0FFF):
      next_lsb = ((sr_value >> 22) ^ (sr_value >> 17)) & 0x01
      sr_value = (sr_value << 1) | next_lsb
    calc[0] = start_value
    for i in np.arange(1,1023):
      for j in np.arange(1,13):
        next_lsb = ((sr_value >> 22) ^ (sr_value >> 17)) & 0x01
        sr_value = (sr_value << 1) | next_lsb
      next_value = sr_value & 0x0FFF
      if next_value > 0x7FF:
        next_value = next_value - 0x1000
      calc[i] = next_value
      #print "calc " + str(i) + ": " + str(next_value)
  return calc

current_time = dt.datetime.now()

adcs = 2
channels = 8
frame_size = 1024
sampling_freq = 80 #MHz
v_range  = 2 #V
res_bits = 12 #Bits

i_board_id      = 0
i_sampling_freq = 1
i_nr_of_samples = 2
i_header_adc    = 3
i_header_ch     = 4
i_ch_segment_nr = 5
i_data_seq_nr   = 6
i_packet_seq_nr = 7
data_offset     = 8

with open("./wddump/dump.txt") as dump_file:
  data = dump_file.readlines()
pn_outfile   = "./pn.txt"
out_file = file(pn_outfile,'a')
outline = current_time.isoformat(' ') + "\n"
out_file.write(outline)
outline = "Frame ADC Ch Noise[LSBs] Noise[mV]\n"
out_file.write(outline)

data = np.split(np.loadtxt("./wddump/dump.txt", dtype=np.uint32), 32)
current_frame = data[0][i_data_seq_nr]

ch_data_value = np.zeros((adcs, channels,frame_size), dtype=np.uint32)
#ch_data_value = np.zeros((adcs, channels,frame_size), dtype=np.float32)
#ch_data_mV    = np.zeros((adcs, channels,frame_size), dtype=np.int32)

for d in data:
  if d[i_data_seq_nr] != current_frame:
    print "Frame Error (" + str(current_frame) + ", " + str(d[i_data_seq_nr]) + ")"
    #quit()
    break;
  adc     = d[i_header_adc]
  ch      = d[i_header_ch]
  segment = d[i_ch_segment_nr]
  ch_data_value[adc, ch, segment*frame_size/2:(segment+1)*frame_size/2] = d[data_offset:(data_offset+frame_size/2)]                            # ADC Value
  #ch_data_mV[adc, ch, segment*frame_size/2:(segment+1)*frame_size/2]    = d[data_offset:(data_offset+frame_size/2)]*1000*v_range/(2**res_bits) # mV

sample = np.arange(1024)

ch_data_calc = get_pn_seq( pn, ch_data_value[test_adc, test_ch, 0])
#ch_data_calc[0] = ch_data_value[test_adc, test_ch, 0]

#for d in np.arange(1023):
#  ch_data_calc[d+1] = pn_next( pn, ch_data_calc[d])

print "Plotting Frame " + str(current_frame) + "...\n"

data_error = ch_data_value[test_adc, test_ch]-ch_data_calc

pl.subplot(2, 1, 1)

pl.title("Received and Calculated Pattern of ADC/Channel: %d/%d" % (test_adc, test_ch))
#pl.plot(sample, ch_data_mV[test_adc, test_ch])
#pl.plot(sample, ch_data_value[test_adc, test_ch], 'b', sample, ch_data_calc, 'r')
pl.plot(sample, ch_data_value[test_adc, test_ch], 'b', label='RX data')
pl.plot(sample, ch_data_calc, '--r', label='PN target pattern')
#pl.plot(sample, ch_data_value[test_adc, test_ch], 'b')
pl.grid()
pl.xlabel("sample")
pl.ylabel("value")
pl.xlim(0 , 1023)
#pl.legend('RX', 'PN', loc='upper right')
pl.legend(loc='upper right')
#pl.ylim(np.amin(ch_data_value[test_adc, ch])-10,np.amax(ch_data_value[test_adc, ch])+10)

pl.subplot(2, 1, 2)

pl.title("Error of ADC/Channel: %d/%d" % (test_adc, test_ch))
#pl.plot(sample, ch_data_mV[test_adc, ch])
pl.plot(sample, data_error)
pl.grid()
pl.xlabel("sample")
pl.ylabel("error")
pl.xlim(0 , 1023)
pl.ylim(np.amin(data_error)-10,np.amax(data_error)+10)

outline = "\n"
out_file.write(outline)
out_file.close()
print "Writing noise.txt done.\n"
pl.show()
