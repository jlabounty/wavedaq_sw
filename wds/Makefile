###########################################################
#
#  General purpose Makefile for Linux and Darwin, SR 2015
#
###########################################################

CFLAGS  = -O0 -g

# search main file
GREP = grep -l "main(" src/*c src/*cpp
MAIN = $(shell $(GREP))
OUTNAME = $(basename $(notdir $(MAIN)))

# OS specific flags and libs
ifeq ($(shell uname),Linux)
CFLAGS  += -std=c++0x
LIBS    = -pthread
endif

ifeq ($(shell uname),Darwin)
CFLAGS  += -std=gnu++11 -x c++
LIBS    = -lobjc
endif

CFLAGS += -I./src -I../src -I../../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/common/src/
CFLAGS += -D WD2_DONT_INCLUDE_REG_ACCESS_VARS
# search *.c and *.cpp files
C_FILES = $(wildcard src/*.c)
CPP_FILES = $(wildcard src/*.cpp)
#C_OBJ = $(C_FILES:%.c=%.o)
C_OBJ = $(notdir $(C_FILES:%.c=%.o))
#CPP_OBJ = $(CPP_FILES:%.cpp=%.o)
CPP_OBJ = $(notdir $(CPP_FILES:%.cpp=%.o))

LIB_FILES = $(wildcard ../src/*.cpp)
LIB_OBJ = $(notdir $(LIB_FILES:%.cpp=%.o))

all: $(OUTNAME)

$(OUTNAME): $(C_OBJ) $(CPP_OBJ) $(LIB_OBJ)
	g++ $(C_OBJ) $(CPP_OBJ) $(LIB_OBJ) -o $(OUTNAME) $(LIBS)

$(CPP_OBJ): %.o: src/%.cpp src/%.h ../src/WDBLib.h
	g++ $(CFLAGS) -c $<

$(LIB_OBJ): %.o: ../src/%.cpp ../src/%.h
	g++ $(CFLAGS) -c $<

$(C_OBJ): %.o: src/%.c
	g++ $(CFLAGS) -c $<

clean:
	rm -f $(C_OBJ) $(CPP_OBJ) $(LIB_OBJ) $(OUTNAME)

