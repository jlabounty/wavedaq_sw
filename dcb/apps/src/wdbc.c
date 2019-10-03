#include "stdio.h"
#include "cmd_processor.h"

int main(int argc, char *argv[])
{
   if (argc > 2) { 
      argv[0] = "wdb";
      cmd_process(argc, argv);
   } else {
      printf("Usage: %s <slot number> <cmd>\n", argv[0]);
   }

   return 0;
}