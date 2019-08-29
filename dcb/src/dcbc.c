#include "cmd_processor.h"

int main(int argc, char *argv[])
{
   if (argc>1) 
      cmd_process(argc-1, &argv[1]);

  return 0;
}