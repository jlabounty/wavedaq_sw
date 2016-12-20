###########################################################
#
#  General purpose Makefile for Linux and Darwin, SR 2015
#
###########################################################

CFLAGS  = -O0 -DOS_LINUX

# search main file
GREP = grep -l "main(" *cpp
MAIN = $(shell $(GREP))
OUTNAME = $(basename $(MAIN))

# OS specific flags and libs
ifeq ($(shell uname),Linux)
LIBS    = -pthread
endif

ifeq ($(shell uname),Darwin)
CFLAGS  += -DOS_DARWIN
LIBS    = -framework IOKit -framework CoreFoundation -lobjc
endif

# search *.c and *.cpp files
C_FILES = $(wildcard *.c)
C_OBJ = $(C_FILES:%.c=%.o)

# search *.c and *.cpp files
CPP_FILES = $(wildcard *.cpp)
CPP_OBJ = $(CPP_FILES:%.cpp=%.o)

all: $(OUTNAME)

$(OUTNAME): $(C_OBJ) $(CPP_OBJ)
	g++ $(C_OBJ) $(CPP_OBJ) -o $(OUTNAME) $(LIBS)

$(CPP_OBJ): %.o: %.cpp 
	g++ $(CFLAGS) -c $<

$(C_OBJ): %.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm $(C_OBJ) $(OUTNAME)
