cmake_minimum_required(VERSION 3.16)

project(GST_TEST)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")

# 寻找GStreamer库
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0)
# 将头文件路径和库路径添加到编译选项
include_directories(${GST_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS})


#增加宏
add_definitions(-DIostream=1)

# Warning option Suppression
add_compile_options(-Wno-unused-parameter)
add_compile_options(-Wno-sign-conversion)


set(GST_TEST
    # src/basic-tutorial-1.cpp
    # src/basic-tutorial-2.cpp
    # src/basic-tutorial-3.cpp
    # src/basic-tutorial-4.cpp
    # src/basic-tutorial-5.cpp
    # src/basic-tutorial-7.cpp
    # src/basic-tutorial-8.cpp
    src/basic-tutorial-12.cpp
    # src/log.c
    # RefactorSrc/sample-2.cpp
    # RefactorSrc/sample-3.cpp
    # RefactorSrc/sample-4.cpp
    # RefactorSrc/sample-5.cpp
    # RefactorSrc/app-test.cpp
    ./main.cpp)
# add debug
SET(CMAKE_BUILD_TYPE "Debug") 

# sudo apt-get install libjsoncpp-dev

find_package(Boost 1.71.0 REQUIRED
             COMPONENTS system filesystem thread)
find_package(Threads REQUIRED)


add_executable(${PROJECT_NAME}  ${GST_TEST})
add_definitions("-Wall -g")
set(lib_DIR /usr/lib/x84_64-linux-gnu)
link_directories(${lib_DIR})
target_link_libraries(${PROJECT_NAME} libjsoncpp.so)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# 链接GStreamer库
target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES})


# 查找 GTK3 包
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# 包含 GTK3 头文件目录
# include_directories(${GTK3_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME}  ${GTK3_LIBRARIES})