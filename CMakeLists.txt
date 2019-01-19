cmake_minimum_required(VERSION 3.0.0)
project(3DGameEngine)


add_definitions(
	-g
	-std=c++17
	-c
	-Wall
	-lstdc++fs
)

# This is needed for YouCompleteMe
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

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

file(GLOB_RECURSE SOURCES 3DGameEngine/Engine/*.cpp)
file(GLOB_RECURSE HEADERS 3DGameEngine/Engine/*.h)
file(GLOB IMGUI 3DGameEngine/include/imgui/*.cpp)
file(GLOB IMGUI_HEADERS 3DGameEngine/include/imgui/*.h)
file(GLOB BULLETMT 3DGameEngine/include/BulletMultiThreading/*.cpp)
file(GLOB BULLETMT_HEADERS 3DGameEngine/include/BulletMultiThreading/*.h)
set(SOURCES ${SOURCES} ${IMGUI} ${BULLETMT})
set(HEADERS ${HEADERS} ${IMGUI_HEADERS} ${BULLETMT_HEADERS})

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
find_package(OpenGL REQUIRED)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	# Bullet
	set(BULLET_ROOT /usr/local)
	set(BULLET_ROOT 3DGameEngine/lib)
	find_package(Bullet REQUIRED)

	# GLEW
	find_package(GLEW REQUIRED)

	# SDL2
	# INCLUDE(${3DEngineCpp_CMAKE_DIR}/FindSDL2.cmake)
	find_package(SDL2 REQUIRED)

	# ASSIMP
	find_package(Assimp REQUIRED)

	# FMOD
	find_library(FMOD_LIBRARIES
		NAMES libfmodL.so
		#PATH /usr/lib/x86_64-linux-gnu
		PATH 3DGameEngine/lib
		)
	if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
		find_library(FMOD_LIBRARIES
		NAMES libfmod.so
		#PATH /usr/lib/x86_64-linux-gnu
		PATH 3DGameEngine/lib
		)
	endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )
	set(FMOD_INCLUDE_DIRS /usr/include/FMOD)

	# Threading building blocks
	find_package(TBB REQUIRED)
	message( ${BULLET_LIBRARIES} )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	file(GLOB_RECURSE LIBS 3DGameEngine/lib/*.lib)
	file(GLOB_RECURSE WINDOWS_HEADERS 3DGameEngine/includeWindows/*.h)
	file(GLOB_RECURSE WINDOWS_ADDITIONAL_SOURCES 3DGameEngine/includeWindows/*.cpp)
	add_definitions(-DB3_USE_CLEW)
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")


add_executable(3DGameEngine ${HEADERS} ${SOURCES} ${WINDOWS_HEADERS} ${WINDOWS_ADDITIONAL_SOURCES})
# Define the include DIRs
include_directories( 
		${3DGameEngine_SOURCE_DIR}/3DGameEngine/Engine
		${3DGameEngine_SOURCE_DIR}/3DGameEngine/include
		${3DGameEngine_SOURCE_DIR}/3DGameEngine/includeWindows
		${OPENGL_INCLUDE_DIRS}
		${GLEW_INCLUDE_DIRS}
		${SDL2_INCLUDE_DIRS}
		${ASSIMP_INCLUDE_DIRS}
		${BULLET_INCLUDE_DIRS}
		${FMOD_INCLUDE_DIRS}
		)


# Define the link libraries
target_link_libraries( 3DGameEngine
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES}
		${SDL2_LIBRARIES}
		${ASSIMP_LIBRARIES}
		${BULLET_LIBRARIES}
		${FMOD_LIBRARIES}
		${LIBS}
		m
		tbb
		stdc++fs
		)

