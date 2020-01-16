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
MSCB_DIR      = ../../../mscb
WDB_DIR       = ../
TCB_DIR       = ../tcb
FW_DIR        = ../../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/

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

FLAGS         += -I$(MSCB_DIR)/include -Iinclude -I$(WDB_DIR)/include -I$(WDB_DIR)/dcb/app/src -I$(TCB_DIR) -I$(FW_DIR) -I$(MXML_DIR)
LIBS          += -lm -lutil -lpthread

# system objects
MSCB_OBJ      = mscb.o mscbrpc.o
MXML_OBJ      = mxml.o strlcpy.o

#-------------------------------------------------------------------
# Drivers needed by the frontend program
#                 
TCB_OBJ       = TCBLib.o
WDB_OBJ       = WDBLib.o DCBLib.o averager.o

OBJECTS       = serdestest.o $(MXML_OBJ) $(WDB_OBJ) $(MSCB_OBJ) $(TCB_OBJ) 
OUTNAME       = serdestest

all: $(OUTNAME)

$(OUTNAME): $(OBJECTS)
	$(CPP) $(FLAGS) $(OBJECTS) -o $(OUTNAME) $(LIBS)

$(TCB_OBJ): %.o: $(TCB_DIR)/%.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

$(WDB_OBJ): %.o: $(WDB_DIR)/src/%.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

serdestest.o: serdestest.cpp
	$(CPP) $(FLAGS) -o $@ -c $<

$(MSCB_OBJ): %.o: $(MSCB_DIR)/src/%.cxx
	$(CPP) $(FLAGS) -o $@ -c $<

$(MXML_OBJ): %.o: $(MXML_DIR)/%.cxx $(MXML_DIR)/mxml.h
	$(CPP) $(FLAGS) -o $@ -c $<

clean:
	rm -f *.o *~ \#* $(OBJECTS) $(OUTNAME)
