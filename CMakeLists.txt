# -------------------------------------------------------------------------------
# applications
# -------------------------------------------------------------------------------
project(ejian)
cmake_minimum_required(VERSION 3.15)

# -------------------------------------------------------------------------------
# CMake flags
# -------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/lib")
set(EJIAN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EJIAN_INCLUDE_DIR ${EJIAN_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O2 -std=c++11 -rdynamic -lpthread -fPIC -lstdc++ -pipe -lrt -lpthread")

if(WIN32)
  add_definitions(-D__win__)
  add_definitions(-D__use_iocp__)
endif()

file(GLOB_RECURSE SOURCES
  "include/*.h"
  "include/*.hpp"
  "src/*.*"
)

include_directories(
	"${EJIAN_INCLUDE_DIR}"
)

# -------------------------------------------------------------------------------
# apps
# -------------------------------------------------------------------------------
add_library(ejian STATIC ${SOURCES}) # 生成静态库

if(UNIX)
  message(" Current platform: Linux ")
  target_link_libraries(${PROJECT_NAME} rt pthread)
endif()

# add_subdirectory(test)