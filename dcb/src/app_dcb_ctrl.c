#include "cmd_processor.h"
#include "utilities.h"
#include "string.h"

int main(int argc, char *argv[])
{
  if(strstr(argv[0], "dcb"))
  {
    if(argc>1) cmd_process(argc-1, &argv[1]);
  }
  else if(strstr(argv[0], "wdb"))
  {
    if(argc>2) cmd_process(argc, argv);
  }

  return 0;
}