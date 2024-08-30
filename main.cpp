// #include "basic-tutorial.h"
// // #include "sample.h"
// #include "log.h"
// #include "app-test.h"

// int32_t main(int32_t argc, char *argv[])
// {
//   InFunLOG();
// #if 1
//   int32_t ret = tutorial_main_12(argc,argv);
// #endif

// #if 1
//   // Sample sample {};
//   // int32_t ret = sample.tutorial_main_4(argc,argv);
// #endif 
//   // int32_t ret = build_pipeline(argc,argv);
//   // printf("ret = %d\n",ret);
//   return ret;

// }


#include <gst/gst.h>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);
    
    // 创建自定义插件实例
    GstElement *element = gst_element_factory_make("cecaudiosrc", "source");
    if (!element) {
        g_printerr("Failed to create element\n");
        return -1;
    }

    // 创建管道并添加元素
    GstElement *pipeline = gst_pipeline_new("audio-pipeline");
    gst_bin_add(GST_BIN(pipeline), element);

    // 设置管道状态
    gst_element_set_state(pipeline, GST_STATE_READY);
    gst_element_set_state(pipeline, GST_STATE_PAUSED); // 这里将调用 `start` 函数
    gst_element_set_state(pipeline, GST_STATE_PLAYING); // 开始处理数据

    // 等待一段时间以便查看效果
    g_usleep(2 * G_USEC_PER_SEC);

    // 释放资源
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
