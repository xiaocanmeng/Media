cmake_minimum_required(VERSION 3.16)
project(GST_TEST)

# -----------------------
# 基本设置
# -----------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -g")
add_definitions(-DIostream=1)
add_compile_options(-Wno-unused-parameter -Wno-sign-conversion)
add_definitions(-DPACKAGE="cecaudiosrc")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# -----------------------
# 寻找 GStreamer
# -----------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0 gstreamer-base-1.0)

include_directories(${GST_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS})

# -----------------------
# 寻找 Boost & Threads
# -----------------------
find_package(Boost 1.71.0 REQUIRED COMPONENTS system filesystem thread)
find_package(Threads REQUIRED)

# -----------------------
# 其他库
# -----------------------
find_library(ASOUND_LIB asound)
set(lib_DIR /usr/lib/x86_64-linux-gnu)
link_directories(${lib_DIR})

# -----------------------
# 源文件
# -----------------------
set(GST_TEST_SRC
    # somethingtest/async_gst_set_state.cpp
    somethingtest/test_videosrc_stop_start_pvm.c
    # 可以继续添加其他源文件
)

# -----------------------
# 可执行文件
# -----------------------
add_executable(${PROJECT_NAME} ${GST_TEST_SRC})

target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES} Threads::Threads ${ASOUND_LIB} libjsoncpp.so)

# -----------------------
# 生成预处理文件函数
# -----------------------
function(add_preprocessed_file SOURCE_FILE)
    # 获取源文件名
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME)
    # 输出到 build 目录
    set(OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.i)

    # 获取 GStreamer 编译 flags
    execute_process(
        COMMAND pkg-config --cflags gstreamer-1.0 gstreamer-base-1.0
        OUTPUT_VARIABLE GST_CFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    string(REPLACE " " ";" GST_CFLAGS_LIST "${GST_CFLAGS}")

    # 创建自定义 target
    add_custom_target(preprocess_${FILE_NAME}
        COMMAND ${CMAKE_CXX_COMPILER} -E
                ${SOURCE_FILE}
                -o ${OUTPUT_FILE}
                -I${CMAKE_CURRENT_SOURCE_DIR}/inc
                ${GST_CFLAGS_LIST}
        COMMENT "Generating preprocessed file ${FILE_NAME}.i"
        VERBATIM
    )
endfunction()

# -----------------------
# 使用函数生成预处理文件
# -----------------------
# add_preprocessed_file(${CMAKE_CURRENT_SOURCE_DIR}/somethingtest/async_gst_set_state.cpp)
# 如果有其他源文件需要生成 .i，只需要再 add_preprocessed_file(路径)

# -----------------------
# 安装插件
# -----------------------
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES src/prcess_plugin.c DESTINATION lib/gstreamer-1.0)
