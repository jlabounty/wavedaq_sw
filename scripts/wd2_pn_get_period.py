
import datetime as dt
import sys
import numpy as np
import pylab as pl

# polynomes PN23 = X^23 + X^18 + 1 (seed value 0x003AFF)
#        or PN9  = X^9  + X^5  + 1 (seed value 0x000092)
#  next_lsb = ((sr_value >> 8) ^ (sr_value >> 4)) & 0x01
#  sr_value = (sr_value << 1) | next_lsb
samples = 0
start_value = 0x003AFF
mask = 0x007FFFFF
#start_value = 0x000092
#mask = 0x000001FF
sr_value = start_value
while ((sr_value & mask) != start_value) or (samples == 0):
#  next_lsb = ((sr_value >> 8) ^ (sr_value >> 4)) & 0x01
#  sr_value = (sr_value << 1) | next_lsb
  next_lsb = ((sr_value >> 22) ^ (sr_value >> 17)) & 0x01
  sr_value = (sr_value << 1) | next_lsb
  #print "0x%08X" % (sr_value & mask)
  samples += 1
print "Repeats after " + str(samples) + " samples"

