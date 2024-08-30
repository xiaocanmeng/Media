# --------------------------------------------------------------  
# Required CMake version  
# --------------------------------------------------------------  
cmake_minimum_required(VERSION 3.10)  

# --------------------------------------------------------------  
# Project name  
# --------------------------------------------------------------  
project(alsa_src)  

# --------------------------------------------------  
# path configuration  
# --------------------------------------------------  
include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)  

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)  

# Warning option Suppression  
# 关闭所有警告  
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")  
elseif(MSVC)  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")  
endif()  

# 关闭C编译器的所有警告  
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")  
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")  
elseif(MSVC)  
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W0")  
endif()  

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  

if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")  
    set(CMAKE_BUILD_TYPE "Debug")  
endif()  

# set(CMAKE_BUILD_TYPE "Debug")  

if (CMAKE_BUILD_TYPE STREQUAL "Debug")   
    # ADD_DEFINITIONS(-DDEBUG)   
else()  
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g0")  
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g0")  
    ADD_DEFINITIONS(-DNDEBUG)  
endif()  

ADD_DEFINITIONS(-DENABLE_AI)  

# 加入标准和PIC选项  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")  
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fPIC")  
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -fPIC")  

# --------------------------------------------------------------------------------------  
# add target directories  
# --------------------------------------------------------------------------------------  
add_subdirectory(src)  

# --------------------------------------------------------------------------------------  
# CPack configuration  
# see https://cmake.org/cmake/help/v3.3/module/CPackDeb.html  
# --------------------------------------------------------------------------------------  

# Convert to Debian package using CPack  
set(CPACK_GENERATOR "DEB")  
# Settings that do not separate packages for each install COMPONENT  
set(CPACK_DEB_COMPONENT_INSTALL OFF)  
# Package version  
set(CPACK_PACKAGE_VERSION "1.0.0")  
# Assign the project name that you specified in project ()  
set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")  
# Package Provider Vendor  
set(CPACK_PACKAGE_VENDOR "TOYOTA MOTOR CORPORATION")  
# Maintainer  
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "TOYOTA MOTOR CORPORATION")  
# Using this variable, advanced users can add custom scripts to control.tar.gz.   
# A typical usage is for conffiles, Postinst, POSTRM, Prerm.  
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/postinst;${CMAKE_CURRENT_SOURCE_DIR}/postrm;" )  
# Convert and reconfigure the architecture of the Debian package.  
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "aarch64")  
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "arm64")  
elseif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")  
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")  
else()  
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})  
    set(CPACK_RPM_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})  
endif()  
#strip  
# set(CPACK_STRIP_FILES TRUE)  

set(RELEASE "r0")  
# The file name of the package. In addition, the suffix is given the name specified in COMPONENT during install.  
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-${RELEASE}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE})  

include(CPack)  

# --------------------------------------------------------------------------------------  
# debug information  
# --------------------------------------------------------------------------------------  
# Top directory of the source tree (directory with top-level CMakeLists.txt)  
message(STATUS "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")  
# Build directory corresponding to the CMAKE_SOURCE_DIR  
message(STATUS "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")  
# Directory with CMakeLists.txt currently being processed  
message(STATUS "CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")  
# Build directory corresponding to the CMAKE_CURRENT_BINARY_DIR  
message(STATUS "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")  
# Top Directory of current project (directory with project command CMakeLists.txt)  
message(STATUS "PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")  
# Build directory corresponding to the PROJECT_SOURCE_DIR  
message(STATUS "PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")  
# CMake Cross Compiling variable  
message(STATUS "CMAKE_CROSSCOMPILING=${CMAKE_CROSSCOMPILING}")  
message(STATUS "CMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")  
message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR=${CMAKE_HOST_SYSTEM_PROCESSOR}")  
message(STATUS "CMAKE_C_COMPILER=${CMAKE_C_COMPILER}")  
message(STATUS "CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")  
message(STATUS "CMAKE_INSTALL_SYSCONFDIR=${CMAKE_INSTALL_SYSCONFDIR}")  
message(STATUS "CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")  

# custom target  
add_custom_target(doc   
    COMMAND bash ${CMAKE_SOURCE_DIR}/test/tools/genflow.sh  
)