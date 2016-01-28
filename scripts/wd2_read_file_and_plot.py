
import datetime as dt
import sys
import numpy as np
import pylab as pl

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

#with open("../wddump/dump.txt") as dump_file:
#  data = dump_file.readlines()
noise_outfile   = "./noise.txt"
out_file = file(noise_outfile,'a')
outline = current_time.isoformat(' ') + "\n"
out_file.write(outline)
outline = "Frame ADC Ch Noise[LSBs] Noise[mV]\n"
out_file.write(outline)

data = np.split(np.loadtxt("./wddump/dump.txt", dtype=np.int32), 32)
current_frame = data[0][i_data_seq_nr]

ch_data_value = np.zeros((adcs, channels,frame_size), dtype=np.float32)
ch_data_mV    = np.zeros((adcs, channels,frame_size), dtype=np.int32)

for d in data:
  if d[i_data_seq_nr] != current_frame:
    print "Frame Error (" + str(current_frame) + ", " + str(d[i_data_seq_nr]) + ")"
    #quit()
    break;
  adc     = d[i_header_adc]
  ch      = d[i_header_ch]
  segment = d[i_ch_segment_nr]
  ch_data_value[adc, ch, segment*frame_size/2:(segment+1)*frame_size/2] = d[data_offset:(data_offset+frame_size/2)]                            # ADC Value
  ch_data_mV[adc, ch, segment*frame_size/2:(segment+1)*frame_size/2]    = d[data_offset:(data_offset+frame_size/2)]*1000*v_range/(2**res_bits) # mV

#print "Data read:", data
#print "Data size:", np.size(data)

time_step_us = 1.0/sampling_freq
#time = np.arange(1024)*time_step_us
time = np.arange(1024)

print "Plotting Frame " + str(current_frame) + "...\n"
for adc in np.arange(adcs):
  pl.figure(adc+1)
  for ch in np.arange(channels):
    pl.subplot(4, 2, ch+1)
    
    rms_noise_mV   = np.std(ch_data_mV[adc, ch])
    rms_noise_bits = np.std(ch_data_value[adc, ch])
    pl.title("ADC/Channel: %d/%d   Frame: %d   Noise = %.3f LSBs = %.3f mV" % (adc, ch, current_frame, rms_noise_bits, rms_noise_mV))
    pl.plot(time, ch_data_mV[adc, ch])
    #pl.plot(time, ch_data_value[adc, ch])
    pl.grid()
    if ch > 5:
#      pl.xlabel("time [us]")
      pl.xlabel("sample")
    pl.ylabel("Amplitude [mV]")
    #pl.ylabel("ADC value")
#    pl.xlim(0 , 12.5)
    pl.xlim(0 , 1023)
    pl.ylim(np.amin(ch_data_mV[adc, ch])-10,np.amax(ch_data_mV[adc, ch])+10)
    #pl.ylim(np.amin(ch_data_value[adc, ch])-10,np.amax(ch_data_value[adc, ch])+10)

    print "RMS Noise ADC/Channel %d/%d: %.3f LSBs = %.3f mV" % (adc, ch, rms_noise_bits, rms_noise_mV)
    #print "RMS Noise ADC " + str(adc) + " Channel " + str(ch) + ": " + str(rms_noise_mV) + "mV"
    #outline = str(current_frame) + " " + str(adc) + " " + str(ch) + " " + str(rms_noise_bits) + " " + str(rms_noise_mV) + "\n"
    outline = "%d %d %d %f %f\n" % (current_frame, adc, ch, rms_noise_bits, rms_noise_mV)
    out_file.write(outline)

outline = "\n"
out_file.write(outline)
out_file.close()
print "Writing noise.txt done.\n"
pl.show()
