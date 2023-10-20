cmake_minimum_required(VERSION 3.17)
project(VideoRecord)

# 设置ffmpeg依赖库及头文件所在目录，并存进指定变量
set(ffmpeg_libs_DIR /usr/lib/x86_64-linux-gnu)
set(ffmpeg_headers_DIR /usr/include/x86_64-linux-gnu)

#对于find_package找不到的外部依赖库，可以用add_library添加
# SHARED表示添加的是动态库
# IMPORTED表示是引入已经存在的动态库

add_library( avcodec SHARED IMPORTED)
add_library( avfilter SHARED IMPORTED )
add_library( swresample SHARED IMPORTED )
add_library( swscale SHARED IMPORTED )
add_library( avformat SHARED IMPORTED )
add_library( avutil SHARED IMPORTED )


#指定所添加依赖库的导入路径
set_target_properties( avcodec PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavcodec.so )
set_target_properties( avfilter PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavfilter.so )
set_target_properties( swresample PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libswresample.so )
set_target_properties( swscale PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libswscale.so )
set_target_properties( avformat PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavformat.so )
set_target_properties( avutil PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavutil.so )


# 添加头文件路径到编译器的头文件搜索路径下，多个路径以空格分隔
include_directories( ${ffmpeg_headers_DIR} )
link_directories(${ffmpeg_libs_DIR} )


set(CMAKE_CXX_STANDARD 14)
set(${PROJECT_NAME}
    ./main.cpp)
add_executable(${PROJECT_NAME}  ${VideoRecord})
target_link_libraries(${PROJECT_NAME}  avcodec avformat avutil swresample swscale swscale avfilter )
