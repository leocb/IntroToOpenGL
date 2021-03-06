# Copyright (C) 2014 Barry Deeney
# Copyright (C) 2014 Benny Bobaganoosh
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

################
# CMAKE RULES! #
################
# Huge thanks to mxaddict for setting up the CMake build system!

# we need features that are 2.6 >= dependent
cmake_minimum_required(VERSION 2.6)

# lets name the project
project(ITMOG)

# add the -c and -Wall flags
if(MSVC)
	add_definitions(
		-c
		-W4
	)
else()
	add_definitions(
		-c
		-Wall
		-msse2
	)
endif()

if ( CMAKE_BUILD_TYPE STREQUAL "" )
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	# differentiation between debug and release builds.
	set(
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
	)
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
add_definitions( -O2 )
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

# Lets LOAD app our headers!
file(GLOB_RECURSE HDRS
	${ITMOG_SOURCE_DIR}/src/*.h
	${ITMOG_SOURCE_DIR}/src/*.hpp
	${ITMOG_SOURCE_DIR}/libs/*.h
	${ITMOG_SOURCE_DIR}/libs/*.hpp
)

# Lets LOAD app our sources!
file(GLOB_RECURSE SRCS
	${ITMOG_SOURCE_DIR}/src/*.cpp
	${ITMOG_SOURCE_DIR}/src/*.c
	${ITMOG_SOURCE_DIR}/libs/*.cpp
	${ITMOG_SOURCE_DIR}/libs/*.c
)

# Define the executable
add_executable(ITMOG ${HDRS} ${SRCS})

# We need a CMAKE_DIR with some code to find external dependencies
SET(ITMOG_CMAKE_DIR "${ITMOG_SOURCE_DIR}/cmake")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
INCLUDE(${ITMOG_CMAKE_DIR}/FindGLEW.cmake)

# SDL2
INCLUDE(${ITMOG_CMAKE_DIR}/FindSDL2.cmake)

# ASSIMP
INCLUDE(${ITMOG_CMAKE_DIR}/FindASSIMP.cmake)

# Define the include DIRs
include_directories(
	${ITMOG_SOURCE_DIR}/headers
	${ITMOG_SOURCE_DIR}/sources
	${ITMOG_SOURCE_DIR}/src
	${ITMOG_SOURCE_DIR}/libs
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries( ITMOG
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	${ASSIMP_LIBRARIES}
)

if(WIN32)
	string(REPLACE "/" "\\" source_path_windows "${ITMOG_SOURCE_DIR}/res")
	string(REPLACE "/" "\\" build_path_windows "${ITMOG_BINARY_DIR}/res")
	execute_process(COMMAND cmd.exe /c mklink /J "${build_path_windows}" "${source_path_windows}" RESULT_VARIABLE exitcode)
else()
	execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${ITMOG_SOURCE_DIR}/res ${ITMOG_BINARY_DIR}/res RESULT_VARIABLE exitcode)
endif()

if(NOT ${exitcode} EQUAL 0)
	MESSAGE("SYMLINKING FAILED: ${exitcode}")
	MESSAGE("FALLING BACK TO COPYING")
endif()

#Copy file if the build resource folder contains an older version. This is ignored when the symlink was succesful because the files are already the newest version.
file(GLOB_RECURSE RES RELATIVE ${ITMOG_SOURCE_DIR}/res/ ${ITMOG_SOURCE_DIR}/res/*.*)
foreach(file IN LISTS RES)
	configure_file(${ITMOG_SOURCE_DIR}/res/${file} ${ITMOG_BINARY_DIR}/res/${file} COPYONLY)
endforeach()

#Create virtual folders to make it look nicer in VS
if(MSVC_IDE)
	foreach(source IN LISTS SRCS HDRS)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${ITMOG_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()
