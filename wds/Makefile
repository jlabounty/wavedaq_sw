########################################################
#
#  Makefile for wds project
#
########################################################

OUTNAME = wds
CFLAGS  = -O0

ifeq ($(shell uname),Linux)
LIBS    = -pthread
endif

ifeq ($(shell uname),Darwin)
CFLAGS  += -std=gnu++11 -x c++
LIBS    = -framework IOKit -framework CoreFoundation -lobjc
endif

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

