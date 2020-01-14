#####################################################################
#
#  Name:         Makefile
#  Created by:   Stefan Ritt
#
#  Contents:     Makefile for WaveDAQ Library
#
#####################################################################

# directories
MSCB_DIR      = ../../../mscb
WDAQ_DIR      = ../../

# compiler, flags and libs
CC            = cc
CPP           = g++
FLAGS         = -O3 -g -DOS_LINUX -Wall
CPPFLAGS      = -std=c++11

ifeq ($(shell uname),Darwin)
FLAGS         += -DOS_DARWIN -DHAVE_STRLCPY
LIBS          =  -lobjc 
else
FLAGS         += 
LIBS          =  -lrt -lbsd
endif

FLAGS         += -I$(MSCB_DIR)/include 
FLAGS         += -I$(WDAQ_DIR)/software/include 
FLAGS         += -I$(WDAQ_DIR)/firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/
FLAGS         += -D WD2_DONT_INCLUDE_REG_ACCESS_VARS
FLAGS         += -D DCB_DONT_INCLUDE_REG_ACCESS_VARS
LIBS          += -lm -lutil -lpthread

# system objects
MSCB_OBJ      = mscb.o mscbrpc.o strlcpy.o mxml.o

WDB_DRV_OBJ   = WDBLib.o DCBLib.o averager.o 
OBJECTS       = $(MSCB_OBJ) $(WDB_DRV_OBJ)
OUTNAME       = wdbdiscr

all: $(OUTNAME)

$(OUTNAME): $(OBJECTS) wdbdiscr.o
	$(CPP) $(FLAGS) $(OBJECTS) wdbdiscr.o -o $(OUTNAME) $(LIBS)

$(WDB_DRV_OBJ): %.o: $(WDAQ_DIR)/software/src/%.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

$(MSCB_OBJ): %.o: $(MSCB_DIR)/src/%.cxx
	$(CC) $(FLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

wdbdiscr.o: wdbdiscr.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

clean:
	rm -f *.o *.d *~ \#* $(OUTNAME)

ifneq ($(MAKECMDGOALS), clean)
-include *.d
endif
