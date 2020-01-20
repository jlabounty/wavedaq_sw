#####################################################################
#
#  Name:         Makefile
#  Created by:   Stefan Ritt
#
#  Contents:     Makefile for MEG II WaveDREAM frontend
#
#####################################################################

# directories
MSCB_DIR      = ../mscb

# compiler, flags and libs
CPP           = g++
FLAGS         = -g -DOS_LINUX -Wall

ifeq ($(shell uname),Darwin)
FLAGS         += -DOS_DARWIN -DHAVE_STRLCPY
#LIBS          =  -framework IOKit -framework CoreFoundation
LIBS          =  
else
FLAGS         += 
LIBS          =  -lrt -lbsd
endif

FLAGS         += -I$(MSCB_DIR)/include 
FLAGS         += -I../include 
FLAGS         += -I../dcb/app/src
FLAGS         += -D DCB_DONT_INCLUDE_REG_ACCESS_VARS
FLAGS         += -std=c++11

LIBS          += -lm -lutil -lpthread

# system objects
MSCB_OBJ      = mscb.o mscbrpc.o strlcpy.o

#-------------------------------------------------------------------
# Drivers needed by the frontend program
#                 
DRV_OBJ       = TCBLib.o 
DCB_OBJ       = DCBLib.o 
OBJECTS       = $(MSCB_OBJ) $(DRV_OBJ) $(DCB_OBJ) 
OUTNAME       = tcb_cl

all: $(OUTNAME)

$(OUTNAME): $(OBJECTS)
	$(CPP) $(FLAGS) $(OBJECTS) -o $(OUTNAME) $(LIBS)

$(DRV_OBJ): %.o: ../src/%.cpp
	$(CPP) $(FLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

$(DCB_OBJ): %.o: ../src/%.cpp
	$(CPP) $(FLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

$(MSCB_OBJ): %.o: $(MSCB_DIR)/src/%.cxx
	$(CPP) $(FLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<

tcb_cl: tcb_cl.o $(OBJECTS)
	$(CPP)  $(FLAGS) $(OBJECTS) tcb_cl.o -o tcb_cl $(LIBS)

tcb_cl.o: tcb_cl.cpp
	$(CPP) $(FLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $<


clean:
	rm -f *.o *.d *~ \#* $(OUTNAME)

ifneq ($(MAKECMDGOALS), clean)
-include *.d
endif
