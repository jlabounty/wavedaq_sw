#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mscb.h"
#include "TCBLib.h"
#include <ctime>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
// global variables to be copied
TCB TCBBoard(17);
int handle;
u_int32_t memdata[128], memaddr, tdc[32], totaltime, livetime, hwevecou, trgtype, trgpattern, trgcounters[5];
u_int32_t fadcmode;
u_int32_t trgena, trgbusmask, presca[5], multthr, chamask[4], trgdly;
FILE *infile;
