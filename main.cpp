#include "basic-tutorial.h"
// #include "sample.h"
#include "log.h"


int32_t main(int32_t argc, char *argv[])
{
  InFunLOG();
#if 1
  int32_t ret = tutorial_main_7(argc,argv);
#endif

#if 1
  // Sample sample {};
  // int32_t ret = sample.tutorial_main_4(argc,argv);
#endif 
  printf("ret = %d\n",ret);
  return ret;

}