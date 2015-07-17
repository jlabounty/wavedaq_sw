
import sys
import numpy as np
import pylab as pl

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
i_reserved      = 8
data_offset     = 9

#with open("../wddump/dump.txt") as dump_file:
#  data = dump_file.readlines()

data = np.split(np.loadtxt("../wddump/dump.txt", dtype=np.int32), 32)
current_frame = data[0][i_data_seq_nr]

ch_data = np.zeros((adcs, channels,frame_size), dtype=np.int32)

for d in data:
  if d[i_data_seq_nr] != current_frame:
    print "Frame Error (" + str(current_frame) + ", " + str(d[i_data_seq_nr]) + ")"
    quit()
  adc     = d[i_header_adc]
  ch      = d[i_header_ch]
  segment = d[i_ch_segment_nr]
  #ch_data[adc, ch, segment*frame_size/2:(segment+1)*frame_size/2] = d[data_offset:] # ADC Value
  ch_data[adc, ch, segment*frame_size/2:(segment+1)*frame_size/2] = d[data_offset:]*1000*v_range/(2**res_bits) # mV

#print "Data read:", data
#print "Data size:", np.size(data)

time_step_us = 1.0/sampling_freq
time = np.arange(1024)*time_step_us

print "Plotting Frame " + str(current_frame) + "...\n"
for adc in np.arange(adcs):
  pl.figure(adc+1)
  for ch in np.arange(channels):
    pl.subplot(4, 2, ch+1)
    
    pl.title("ADC " + str(adc) + " Channel " + str(ch) + "   Frame " + str(current_frame))
    pl.plot(time, ch_data[adc, ch])
    pl.grid()
    if ch > 5:
      pl.xlabel("time [us]")
    #pl.ylabel("ADC value")
    pl.ylabel("Amplitude [mV]")
    pl.xlim(0 , 12.5)
    pl.ylim(np.amin(ch_data[adc, ch])-10,np.amax(ch_data[adc, ch])+10)

    rms_noise = np.std(ch_data[adc, ch])
    #print "RMS Noise ADC " + str(adc) + " Channel " + str(ch) + ": " + str(rms_noise) + "LSBs = " + str(rms_noise*1000*v_range/(2**res_bits)) + "mV"
    print "RMS Noise ADC " + str(adc) + " Channel " + str(ch) + ": " + str(rms_noise) + "mV"
    
pl.show()
