#include "stdio.h"
#include "cmd_processor.h"

int main(int argc, char *argv[])
{
   argv[0] = "upload";
   cmd_process(argc, argv);

   return 0;
}