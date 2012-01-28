set(PROJECT_NAME "ogre-framework")

project(${PROJECT_NAME} CXX C)
cmake_minimum_required(VERSION 2.8)

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

# Add a sensible build type default and warning because empty means no optimization and no debug info.
if(NOT CMAKE_BUILD_TYPE)
	message("WARNING: CMAKE_BUILD_TYPE is not defined!\n         Defaulting to CMAKE_BUILD_TYPE=RelWithDebInfo. Use ccmake to set a proper value.")
	set(CMAKE_BUILD_TYPE RelWithDebInfo
	CACHE STRING "Type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Include path for additional CMake library finding scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# We want the binaries to be easily accessible
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if(WIN32)
	set(Boost_USE_STATIC_LIBS   ON)
endif(WIN32)

find_package(Boost COMPONENTS system thread filesystem REQUIRED QUIET)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

find_package(OGRE REQUIRED QUIET)
include_directories(${OGRE_INCLUDE_DIRS} ${OGRE_Terrain_INCLUDE_DIRS} ${OGRE_Paging_INCLUDE_DIRS} ${OGRE_RTShaderSystem_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS})
list(APPEND LIBS ${OGRE_LIBRARIES} ${OGRE_Terrain_LIBRARIES} ${OGRE_Paging_LIBRARIES} ${OGRE_RTShaderSystem_LIBRARIES})

#find_package(MyGUI REQUIRED QUIET)
#include_directories(${MYGUI_INCLUDE_DIRS})
#include_directories(${MYGUI_PLATFORM_INCLUDE_DIRS})
#link_directories(${MYGUI_LIB_DIR})

#IF(MSVC)
#	list(APPEND LIBS ${MYGUI_LIBRARIES} ${MYGUI_PLATFORM_LIBRARIES})
#ELSE(MSVC)
#	list(APPEND LIBS ${MYGUI_LIBRARIES} MyGUI.OgrePlatform) #TODO: MyGUI.OgrePlatform is not added by the find script
#ENDIF(MSVC)

#foreach(lib  OIS SDL OGG VorbisFile)    # Simple libraries added in a loop
foreach(lib  OIS)    # Simple libraries added in a loop
	find_package(${lib} REQUIRED QUIET)
	include_directories(${${lib}_INCLUDE_DIRS})
	list(APPEND LIBS ${${lib}_LIBRARIES})
endforeach()

#if(UNIX)
#	list(APPEND LIBS "rt") # For clock_gettime()
#endif()

# Search include files from all source sub directories
include_directories(source)

# Compile our libraries
#if (BUILD_GAME OR BUILD_EDITOR)
#	foreach(ourlib   tinyxml bullet oisb paged-geom)
#		add_subdirectory(${ourlib})
#		list(APPEND OURLIBS ${ourlib})
#	endforeach()
#endif()

file(GLOB FRAMEWORK_SOURCES
	source/*.cpp
)

add_executable(${PROJECT_NAME} ${FRAMEWORK_SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

