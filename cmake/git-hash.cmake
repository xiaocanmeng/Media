# in case Git is not available, we default to "unknown"
set(GIT_BASH "unknown")
# in case Git is not available, we default to "unknown"
set(GIT_TIME "unknown")
find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:commit=%h
    OUTPUT_VARIABLE GIT_BASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY
    ${CMAKE_SOURCE_DIR}
    )
	execute_process(
		COMMAND git log -1 --date=format:%Y-%m-%d\ %H:%M:%S --pretty=format:date=%ad
		OUTPUT_VARIABLE GIT_TIME
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_QUIET
		WORKING_DIRECTORY
		${CMAKE_SOURCE_DIR}
		)	
else()
	message(STATUS "Git not found")
endif()
 
message(STATUS "Git hash is ${GIT_HASH}")
message(STATUS "Git time is ${GIT_TIME}")

# generate file version.hpp based on version.h.in
configure_file(
  ${CMAKE_SOURCE_DIR}/cec_hal_impl/inc/version.h.in
  ${CMAKE_SOURCE_DIR}/cec_hal_impl/inc/version.h
  @ONLY
  )