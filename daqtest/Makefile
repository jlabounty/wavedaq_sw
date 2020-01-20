#####################################################################
#
#  Name:         Makefile
#  Created by:   Stefan Ritt
#
#  Contents:     Makefile for MEG II WaveDREAM frontend
#
#####################################################################

# directories
MXML_DIR      = ../mxml/
MSCB_DIR      = ../mscb
SW_DIR        = ../

# compiler, flags and libs
CC            = cc
CPP           = g++
FLAGS         = -g -DOS_LINUX -Wall -O3
FLAGS         += -std=c++11

ifeq ($(shell uname),Darwin)
FLAGS         += -DOS_DARWIN -DHAVE_STRLCPY 
LIBS          =  -framework IOKit -framework CoreFoundation
else
FLAGS         += 
LIBS          =  -lrt -lbsd
endif
FLAGS         += -D WD2_DONT_INCLUDE_REG_ACCESS_VARS
FLAGS         += -D DCB_DONT_INCLUDE_REG_ACCESS_VARS

FLAGS         += -I$(MSCB_DIR)/include -I$(SW_DIR)/include -I$(SW_DIR)/.. -I$(SW_DIR)/dcb/app/src/ -I$(MXML_DIR)
LIBS          += -lm -lutil -lpthread

# system objects
MSCB_OBJ      = mscb.o mscbrpc.o
MXML_OBJ      = mxml.o strlcpy.o

#-------------------------------------------------------------------
# Drivers needed by the frontend program
#                 
TCB_OBJ       = TCBLib.o
DCB_OBJ       = DCBLib.o
WDB_OBJ       = WDBLib.o averager.o

OBJECTS       = daqtest.o $(MXML_OBJ) $(WDB_OBJ) $(MSCB_OBJ) $(TCB_OBJ) $(DCB_OBJ) 
OUTNAME       = daqtest

all: $(OUTNAME)

$(OUTNAME): $(OBJECTS)
	$(CPP) $(FLAGS) $(OBJECTS) -o $(OUTNAME) $(LIBS)

$(TCB_OBJ): %.o: $(SW_DIR)/src/%.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

$(DCB_OBJ): %.o: $(SW_DIR)/src/%.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

$(WDB_OBJ): %.o: $(SW_DIR)/src/%.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

daqtest.o: daqtest.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

$(MSCB_OBJ): %.o: $(MSCB_DIR)/src/%.cxx
	$(CPP) $(FLAGS) -o $@ -c $<

$(MXML_OBJ): %.o: $(MXML_DIR)/%.cxx $(MXML_DIR)/mxml.h
	$(CPP) $(FLAGS) -o $@ -c $<

clean:
	rm -f *.o *~ \#* $(OBJECTS) $(OUTNAME)
