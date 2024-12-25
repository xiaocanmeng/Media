#include <stdio.h>
#include <string.h>
#include <gst/gst.h>
#include "log.h"

/**
 * 特性对比：GstMemory 与 GstBuffer
 *
 * +--------------------+---------------------------------------------+--------------------------------------------+
 * | 特性               | GstMemory                                   | GstBuffer                                  |
 * +--------------------+---------------------------------------------+--------------------------------------------+
 * | 用途               | 管理单个内存块                             | 管理多个内存块，作为数据的逻辑容器          |
 * +--------------------+---------------------------------------------+--------------------------------------------+
 * | 表示级别           | 底层内存管理                               | 高层次的数据封装                          |
 * +--------------------+---------------------------------------------+--------------------------------------------+
 * | 内容               | 原始数据块                                 | 包含一个或多个 GstMemory                   |
 * +--------------------+---------------------------------------------+--------------------------------------------+
 * | 元数据支持         | 无                                          | 支持时间戳、标记、大小等元信息             |
 * +--------------------+---------------------------------------------+--------------------------------------------+
 * | 引用计数           | 支持                                        | 支持                                        |
 * +--------------------+---------------------------------------------+--------------------------------------------+
 * | 适用场景           | 处理和操作原始数据片段                     | 在管道中传递音视频帧或数据包              |
 * +--------------------+---------------------------------------------+--------------------------------------------+
 */


//GstBuffer 是对多个 GstMemory 的高层次封装，提供了对数据段的分组管理功能。
//每个 GstBuffer 通常包含多个 GstMemory，而每个 GstMemory 则管理实际的数据存储。
bool test_gst_buffer(void) 
{

    GstBuffer *buffer = gst_buffer_new();
    // 分配一块内存
    guint8 *data = (guint8 *)g_malloc0(1024); // 假设需要 1024 字节
    // 创建 GstMemory 并将其包装到 buffer
    GstMemory *memory = gst_memory_new_wrapped(GST_MEMORY_FLAG_READONLY, data, 1024, 0, 1024, data, g_free);
    gst_buffer_append_memory(buffer, memory);
    GstMemory *mem=NULL;

    /* keep the buffer alive */
    LOG("2024  buffer ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(buffer));
    // (void)gst_buffer_ref(buffer);
    LOG("2024  buffer ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(buffer));
    

    mem = gst_buffer_get_memory(buffer, 0);
    LOG("2024  buffer ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(buffer));
    LOG("2024  mem ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(mem));

    gst_memory_unref(mem);
    LOG("2024  buffer ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(buffer));
    LOG("2024  mem ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(mem));

    gst_buffer_remove_memory(buffer, 0);
    LOG("2024  mem ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(mem));
    LOG("2024  buffer ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(buffer));

    // gst_buffer_unref(buffer);
    // LOG("2024  mem ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(mem));
    // LOG("2024  buffer ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(buffer));

    // gst_buffer_unref(buffer);
    // LOG("2024  mem ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(mem));
    // LOG("2024  buffer ref count =  %d", GST_OBJECT_REFCOUNT_VALUE(buffer));

    return true;
}