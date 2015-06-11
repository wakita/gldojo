cmake_minimum_required(VERSION 3.1)

set(META_PROJECT_NAME        "gldojo")
set(META_PROJECT_DESCRIPTION "A C++ sample code of modern-style OpenGL programming")
set(META_VERSION_MAJOR       "0")
set(META_VERSION_MINOR       "1")
set(META_VERSION_PATCH       "0")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_AUTHOR_ORGANIZATION "smartnova group")
set(META_AUTHOR_DOMAIN       "https://github.com/wakita/gldojo")
set(META_AUTHOR_MAINTAINER   "wakita@is.titech.ac.jp")

string(TOUPPER ${META_PROJECT_NAME} META_PROJECT_NAME_UPPER)

if (OPTION_BUILD_STATIC)
  set(BUILD_SHARED_LIBS OFF)
  message("Note: ${META_PROJECT_NAME_UPPER}_STATIC needs to be defined for static linking.")
  add_definitions("-DGLBINDING_STATIC")
else()
  set(BUILD_SHARED_LIBS ON)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++11)
add_definitions("-DOS_${CMAKE_SYSTEM_NAME}")
add_definitions("-DSYSTEM_NAME=\"${CMAKE_SYSTEM_NAME}\"")

if (${BREW_INCLUDE_PATH})
  include_directories(SYSTEM ${BREW_INCLUDE_PATH})
endif()

find_package(OpenGL)
find_package(glfw3)
find_package(PkgConfig REQUIRED)
#pkg_search_module(TCLAP REQUIRED tclap)
include_directories(${GLFW3_INCLUDE_DIR})
find_package(glbinding REQUIRED)
include_directories(${GLBINDING_INCLUDES})

set(gllibs ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${GLBINDING_LIBRARIES} ${OPENGL_LIBRARIES})

message(STATUS "Includes:")
message(STATUS "  GLFW:      ${GLFW3_INCLUDE_DIR}")
message(STATUS "  glbinding: ${GLBINDING_INCLUDES}")
message(STATUS "  tclap:     ${TCLAP_INCLUDE_DIRS}\n")

message(STATUS "Libraries:")
message(STATUS "  OpenGL:    ${OPENGL_LIBRARIES}")
message(STATUS "  GLFW:      ${GLFW3_LIBRARY}")
message(STATUS "  glbinding: ${GLBINDING_LIBRARIES}")

######################################################################
# The TCLAP header-only library

# include_directories(${TCLAP_INCLUDE_DIRS})

######################################################################
# The json11 library

add_subdirectory(others/json11)
include_directories(others/json11)
link_directories(others/json11)

######################################################################
# Test

add_subdirectory(test)

######################################################################
# The "smartnova" library

add_subdirectory(sn)
include_directories(sn)
link_directories(sn)

set(sblibs ${gllibs} smartnova)

######################################################################
# Utility

function(cook)
  foreach(X ${ARGV})
    add_executable(${chapter}${X} ${chapter}${X}.cpp)
    target_link_libraries(${chapter}${X} ${ingredients})
  endforeach(X)
endfunction(cook)

function (cookall)
  foreach(X ${ARGV})
    set(chapter ${booktitle}${X})
    add_subdirectory(${chapter})
  endforeach(X)
endfunction(cookall)

######################################################################
# Simple tests

set(ingredients ${sblibs})

foreach(X app glfw)
  add_executable(${X} sn/test/${X}.cpp)
  target_link_libraries(${X} ${ingredients})
endforeach(X)

######################################################################
# OpenGL Superbible

set(booktitle sb)
set(ingredients ${sblibs})
cookall(02 03 04 05)

######################################################################
# OpenGL Shader programming cookbook

include_directories(cb00)
set(glcblibs ${sblibs} cb)

set(booktitle cb)
set(ingredients ${glcblibs})
cookall(00 01 02)
