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
FLAGS         += -I$(WDAQ_DIR)/software/lib 
FLAGS         += -I$(WDAQ_DIR)/software/tcb 
FLAGS         += -I$(WDAQ_DIR)/firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/
FLAGS         += -D WD2_DONT_INCLUDE_REG_ACCESS_VARS
LIBS          += -lm -lutil -lpthread

# system objects
MSCB_OBJ      = mscb.o mscbrpc.o strlcpy.o mxml.o

LIB_OBJ       = WDLib.o WDAQLib.o 
WDB_DRV_OBJ   = WDBLib.o averager.o 
TCB_DRV_OBJ   = TCBLib.o 
OBJECTS       = $(MSCB_OBJ) $(WDB_DRV_OBJ) $(TCB_DRV_OBJ) $(LIB_OBJ)
OUTNAME       = wd_cl

all: $(OUTNAME)

$(OUTNAME): $(OBJECTS) wd_cl.o
	$(CPP) $(FLAGS) $(OBJECTS) wd_cl.o -o $(OUTNAME) $(LIBS)

$(WDB_DRV_OBJ): %.o: $(WDAQ_DIR)/software/lib/%.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

$(TCB_DRV_OBJ): %.o: $(WDAQ_DIR)/software/tcb/%.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

$(MSCB_OBJ): %.o: $(MSCB_DIR)/src/%.c
	$(CC) $(FLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

$(LIB_OBJ): %.o: %.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

wd_cl.o: wd_cl.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

clean:
	rm -f *.o *.d *~ \#* $(OUTNAME)

ifneq ($(MAKECMDGOALS), clean)
-include *.d
endif
