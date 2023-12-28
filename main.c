#include "basic-tutorial-1.h"
int main (int argc, char *argv[])
{
// #if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
//   return gst_macos_main (tutorial_main, argc, argv, NULL);
// #else
int tmp = tutorial_main (argc, argv);
if(tmp < 0)
{
  printf("tutorial_main() failed\n");
}
else
{
  printf("tutorial_main() returned %d\n", tmp);
}

  return 0;
// #endif
}