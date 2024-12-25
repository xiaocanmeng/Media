#include <stdio.h>

#define InFunLOG() printf("IN %s\n",__func__);
#define OutFunLOG() printf("Leave %s\n",__func__);
// #define LOG() printf("%s:%d ",__func__,__LINE__);

#define LOG(format, ...) printf("[%s:%d] " format "\n", __func__, __LINE__, ##__VA_ARGS__)
