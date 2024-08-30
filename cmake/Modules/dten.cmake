#----------------------------------------------------------------------
# dten-ivi
#----------------------------------------------------------------------
# dten-ivi Default Path Reference settings
set(LOCAL_DTEN_SYSROOT_PREFIX "${CMAKE_SYSROOT}/opt/dc-ivi-pf")
include_directories(${LOCAL_DTEN_SYSROOT_PREFIX}/include)
link_directories(${LOCAL_DTEN_SYSROOT_PREFIX}/lib)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${LOCAL_DTEN_SYSROOT_PREFIX}/lib")
