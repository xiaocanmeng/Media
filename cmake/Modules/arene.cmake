#----------------------------------------------------------------------
# Arene
#----------------------------------------------------------------------
# Arene Default Path Reference settings
set(LOCAL_ARENE_SYSROOT_PREFIX "${CMAKE_SYSROOT}/opt/arene")
include_directories(${LOCAL_ARENE_SYSROOT_PREFIX}/include)
link_directories(${LOCAL_ARENE_SYSROOT_PREFIX}/lib)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${LOCAL_ARENE_SYSROOT_PREFIX}/lib")
