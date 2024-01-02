#include "basic-tutorial.h"
#include "sample.h"
#include "log.h"
int main (int argc, char *argv[])
{
  InFunLOG();
#if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
  return gst_macos_main (tutorial_main, argc, argv, NULL);
#else
  // tutorial_main_1(argc,argv);
  int32_t ret = tutorial_main_4(argc,argv);
  
  // Sample sample {};
  // int32_t ret = sample.tutorial_main_3(argc,argv);
 
  printf("ret = %d\n",ret);
  return ret;
#endif
}