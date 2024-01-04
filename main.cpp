#include "basic-tutorial.h"
#include "sample.h"
#include "log.h"
int32_t main (int32_t argc, char *argv[])
{
  InFunLOG();
#if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
  return gst_macos_main (tutorial_main, argc, argv, NULL);
#else

#if 0
  // int32_t ret = tutorial_main_5(argc,argv);
#endif

#if 1
  Sample sample {};
  int32_t ret = sample.tutorial_main_4(argc,argv);
#endif 
  printf("ret = %d\n",ret);
  return ret;
#endif
}