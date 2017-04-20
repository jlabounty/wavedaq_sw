###########################################################
#
#  General purpose Makefile for Linux and Darwin, SR 2015
#
###########################################################

CFLAGS  = -O0 -g

ifeq ($(shell uname),Darwin)
CFLAGS  += -std=gnu++11 -x c++
LIBS    = -framework IOKit -framework CoreFoundation -lobjc
endif

CFLAGS += -I../lib -I../../firmware/WD2/wd2_hardware_test/wd2_xsdk_workspace/wd2_app_cmd_interpreter/src/

all: wdbtest

wdbtest: wdbtest.o WDBLib.o mongoose.o
	g++ wdbtest.o WDBLib.o mongoose.o -o wdbtest $(LIBS)

WDBLib.o: ../lib/WDBLib.cpp
	g++ $(CFLAGS) -c $<

wdbtest.o: wdbtest.cpp
	g++ $(CFLAGS) -c $<

mongoose.o: mongoose.c
	g++ $(CFLAGS) -c $<

clean:
	rm -f *.o wdbtest

