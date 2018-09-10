###########################################################
#
#  General purpose Makefile for Linux and Darwin, SR 2015
#
###########################################################

CFLAGS  = -O0 -g

# search main file
GREP = grep -l "main(" *c *cpp
MAIN = $(shell $(GREP))
OUTNAME = $(basename $(MAIN))

# OS specific flags and libs
ifeq ($(shell uname),Linux)
CFLAGS  += -std=c++0x
LIBS    = -pthread
endif

ifeq ($(shell uname),Darwin)
CFLAGS  += -std=gnu++11 -x c++
LIBS    = -framework IOKit -framework CoreFoundation -lobjc
endif

CFLAGS += -I. -I../lib -I../../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/
CFLAGS += -D WD2_DONT_INCLUDE_REG_ACCESS_VARS
# search *.c and *.cpp files
C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp)
C_OBJ = $(C_FILES:%.c=%.o)
CPP_OBJ = $(CPP_FILES:%.cpp=%.o)

LIB_FILES = $(wildcard ../lib/*.cpp)
LIB_OBJ = $(notdir $(LIB_FILES:%.cpp=%.o))

all: $(OUTNAME)

$(OUTNAME): $(C_OBJ) $(CPP_OBJ) $(LIB_OBJ)
	g++ $(C_OBJ) $(CPP_OBJ) $(LIB_OBJ) -o $(OUTNAME) $(LIBS)

$(CPP_OBJ): %.o: %.cpp %.h ../lib/WDBLib.h
	g++ $(CFLAGS) -c $<

$(LIB_OBJ): %.o: ../lib/%.cpp ../lib/%.h
	g++ $(CFLAGS) -c $<

$(C_OBJ): %.o: %.c
	g++ $(CFLAGS) -c $<

clean:
	rm -f $(C_OBJ) $(CPP_OBJ) $(LIB_OBJ) $(OUTNAME)

