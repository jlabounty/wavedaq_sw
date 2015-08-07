###########################################################
#
#  General purpose Makefile for Linux and Darwin, SR 2015
#
###########################################################

CFLAGS  = -O0

# search main file
GREP = grep -l "main(" *c *cpp
MAIN = $(shell $(GREP))
OUTNAME = $(basename $(MAIN))

# OS specific flags and libs
ifeq ($(shell uname),Linux)
LIBS    = -pthread
endif

ifeq ($(shell uname),Darwin)
CFLAGS  += -std=gnu++11 -x c++
LIBS    = -framework IOKit -framework CoreFoundation -lobjc
endif

# search *.c and *.cpp files
C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp)
C_OBJ = $(C_FILES:%.c=%.o)
CPP_OBJ = $(CPP_FILES:%.cpp=%.o)

all: $(OUTNAME)

$(OUTNAME): $(C_OBJ) $(CPP_OBJ)
	g++ $(C_OBJ) $(CPP_OBJ) -o $(OUTNAME) $(LIBS)

$(CPP_OBJ): %.o: %.cpp
	g++ $(CFLAGS) -c $<

$(C_OBJ): %.o: %.c
	g++ $(CFLAGS) -c $<

clean:
	rm $(C_OBJ) $(CPP_OBJ) $(OUTNAME)

