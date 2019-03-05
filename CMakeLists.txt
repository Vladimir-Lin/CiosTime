cmake_minimum_required(VERSION 3.0)
project(libstardate)
include(CheckIncludeFile)
file(READ "VERSION.txt" VERSION)

option(NONAMESPACE "Don't use namespace in the header" off)
string(TIMESTAMP COMPILE_DATETIME "%Y/%m/%d %H:%M:%S")

if(NONAMESPACE)
  add_definitions("-DDONT_USE_NAMESPACE=1")
endif(NONAMESPACE)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_definitions("-DCIOSDEBUG=1")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
else()
  set(CMAKE_BUILD_TYPE Release)
endif()

# Handling compilers in different platforms

# using Clang
if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
endif()

# using GCC
if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
endif()

# using Intel C++
if(CMAKE_CXX_COMPILER_ID STREQUAL Intel)
endif()

# using Visual Studio C++
if(MSVC)
  # message( ${CMAKE_CXX_COMPILER} )
  add_definitions("/wd4819")
  add_definitions("/nologo")
  if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(TARGET_ARCH x64)
    add_definitions("-DCIOS_X64=1")
  elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(TARGET_ARCH x86)
    add_definitions("-DCIOS_X86=1")
  endif()
endif(MSVC)

include_directories(include)

# Header
set(HEADERS include/stardate.hpp)

# Source codes
set(CORES
  src/stardate.cpp
  src/startime.cpp
  src/frequency.cpp
  src/estimator.cpp
  src/usleep.cpp
  src/hardware.cpp)

# Handling pkg-config file
configure_file(libstardate.pc.in libstardate.pc @ONLY)

if(BUILD_SHARED_LIBS)
  add_library(libstardate SHARED ${CORES} ${HEADERS})
#  target_link_libraries(libstardate m)
  add_definitions("-DBUILD_SHARED_LIBS=1")
  add_definitions("-DEXPORT_LIBSTARDATE=1")
  install(TARGETS libstardate
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
  install(FILES include/stardate.hpp DESTINATION include)
  install(FILES ${CMAKE_BINARY_DIR}/libstardate.pc DESTINATION lib/packages)
else(BUILD_SHARED_LIBS)
  add_library(libstardate STATIC ${CORES} ${HEADERS})
#  target_link_libraries(libnations m)
  install(TARGETS libstardate DESTINATION lib)
  install(FILES include/stardate.hpp DESTINATION include)
  install(FILES ${CMAKE_BINARY_DIR}/libstardate.pc DESTINATION lib/packages)
endif(BUILD_SHARED_LIBS)
