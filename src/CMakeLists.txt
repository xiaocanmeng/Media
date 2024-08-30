# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
#cmake_minimum_required(VERSION 3.14)
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Project name
# --------------------------------------------------------------
project(gstalsa)

# --------------------------------------------------
# path configuration
# --------------------------------------------------

find_package(PkgConfig)
pkg_check_modules(_gstreamer-1.0 QUIET gstreamer-1.0)
pkg_check_modules(_gstreamer-base-1.0 QUIET gstreamer-base-1.0)
pkg_check_modules(_gstreamer-audio-1.0 QUIET gstreamer-audio-1.0)
pkg_check_modules(_gstreamer-app-1.0 QUIET gstreamer-app-1.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${_gstreamer-1.0_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    # ${_gstreamer-video-1.0_INCLUDE_DIRS}
    # ${_gstreamer-app-1.0_INCLUDE_DIRS}
)

set(PLUGIN_SRC_LIST
	gstalsa.c
	gstalsadeviceprobe.c
	gstalsamidisrc.c
	gstalsaplugin.c
	gstalsasink.c
	gstalsasrc.c
)

add_library(${PROJECT_NAME} SHARED ${PLUGIN_SRC_LIST})

target_link_libraries(${PROJECT_NAME} 
    ${_gstreamer-1.0_LIBRARIES}
    ${_gstreamer-base-1.0_LIBRARIES}
    ${GLIB_LIBRARIES}
    ${_gstreamer-audio-1.0_LIBRARIES}
	asound
)