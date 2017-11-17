#---- PREAMBLE
cmake_minimum_required(VERSION 3.5)
project(mdfds CXX)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -Wpedantic)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
	message (STATUS "Build type not specified: defaulting to ${CMAKE_BUILD_TYPE}")
endif()

#---- FIND SYSTEM THREADING LIBRARY
find_package(Threads REQUIRED)

#---- FIND ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS TreePlayer)
#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

#---- FIND GTEST OR DOWNLOAD IT AND COMPILE IT
enable_testing()
find_package(GTest)
if(GTest_FOUND)
	include_directories(${GTEST_INCLUDE_DIRS})
else()
	message (STATUS "GTest will be downloaded and installed as part of the build step")
	# Download and install googletest
	include(ExternalProject)
	ExternalProject_Add(googletest
		URL https://github.com/google/googletest/archive/release-1.8.0.zip
		URL_HASH SHA256=f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:string=${CMAKE_BINARY_DIR}/gtest)

	# Add gtest to our build
	include_directories(${CMAKE_BINARY_DIR}/gtest/include)
	set(GTEST_BOTH_LIBRARIES ${CMAKE_BINARY_DIR}/gtest/lib/libgtest.a ${CMAKE_BINARY_DIR}/gtest/lib/libgtest_main.a)
	set(EXTERNAL_GTEST TRUE)
endif(GTest_FOUND)

#--- BUILD MDFDS
add_subdirectory(src)

#--- BUILD TESTS
add_subdirectory(tests)
