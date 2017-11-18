#####################################################################
#
#  Name:         Makefile
#  Created by:   Stefan Ritt
#
#  Contents:     Makefile for MEG II WaveDREAM frontend
#
#####################################################################

# directories
MXML_DIR      = ../../../mxml/
MSCB_DIR      = ../../../mscb
WDB_DIR       = ../lib
TCB_DIR       = ../tcb
FW_DIR        = ../../firmware/WD2/wd2_hardware_test/wd2_xsdk_workspace/wd2_app_cmd_interpreter/src/

# compiler, flags and libs
CC            = cc
CPP           = g++
FLAGS         = -g -DOS_LINUX -Wall -O3
CPPFLAGS      = -std=c++0x

ifeq ($(shell uname),Darwin)
FLAGS         += -DOS_DARWIN -DHAVE_STRLCPY 
LIBS          =  -framework IOKit -framework CoreFoundation
else
FLAGS         += 
LIBS          =  -lrt -lbsd
endif

FLAGS         += -I$(MSCB_DIR)/include -Iinclude -I$(WDB_DIR) -I$(TCB_DIR) -I$(FW_DIR) -I$(MXML_DIR)
LIBS          += -lm -lutil -lpthread

# system objects
MSCB_OBJ      = mscb.o mscbrpc.o
MXML_OBJ      = mxml.o strlcpy.o

#-------------------------------------------------------------------
# Drivers needed by the frontend program
#                 
TCB_OBJ       = TCBLib.o
WDB_OBJ       = WDBLib.o averager.o

OBJECTS       = trgbustest.o $(MXML_OBJ) $(WDB_OBJ) $(MSCB_OBJ) $(TCB_OBJ) 
OUTNAME       = trgbustest

all: $(OUTNAME)

$(OUTNAME): $(OBJECTS)
	$(CPP) $(FLAGS) $(OBJECTS) -o $(OUTNAME) $(LIBS)

$(TCB_OBJ): %.o: $(TCB_DIR)/%.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

$(WDB_OBJ): %.o: $(WDB_DIR)/%.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -o $@ -c $<

trgbustest.o: trgbustest.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -o $@ -c $<

$(MSCB_OBJ): %.o: $(MSCB_DIR)/src/%.c
	$(CC) $(FLAGS) -o $@ -c $<

$(MXML_OBJ): %.o: $(MXML_DIR)%.c $(MXML_DIR)mxml.h
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f *.o *~ \#* $(OBJECTS) $(OUTNAME)
