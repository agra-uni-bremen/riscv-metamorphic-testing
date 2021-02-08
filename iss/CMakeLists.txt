cmake_minimum_required(VERSION 2.8.12)
project(riscv-iss)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")			#"-Wall -Wextra"
#set(CMAKE_CXX_FLAGS_DEBUG "-g3")        #"-fsanitize=address -fno-omit-frame-pointer"
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  message(STATUS "Code coverage enabled.")
  set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
  include(CodeCoverage) 
  append_coverage_compiler_flags()
  setup_target_for_coverage_gcovr_html( NAME coverage EXECUTABLE mt-iss BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src")  
  #setup_target_for_coverage_lcov( NAME coverage EXECUTABLE mt-iss BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src" )
endif()


find_package( Boost REQUIRED COMPONENTS iostreams program_options )

find_package( SoftFloat REQUIRED )
include_directories( ${SoftFloat_INCLUDE_DIRS} )

subdirs(src)
