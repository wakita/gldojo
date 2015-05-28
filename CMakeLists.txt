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

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++11)
add_definitions("-DOS_${CMAKE_SYSTEM_NAME}")
add_definitions("-DSYSTEM_NAME=\"${CMAKE_SYSTEM_NAME}\"")

if (${BREW_INCLUDE_PATH})
  include_directories(SYSTEM ${BREW_INCLUDE_PATH})
endif()

find_package(OpenGL)
find_package(glfw3)
#find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW3_INCLUDE_DIR})
set(gllibs ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES})

find_package(glbinding REQUIRED)
include_directories(${GLBINDING_INCLUDES})
list(APPEND gllibs ${GLBINDING_LIBRARIES} ${OPENGL_LIBRARIES})

message(STATUS "Includes:")
message(STATUS "  GLFW:      ${GLFW3_INCLUDE_DIR}")
message(STATUS "  glbinding: ${GLBINDING_INCLUDES}\n")

message(STATUS "Libraries:")
message(STATUS "  OpenGL:    ${OPENGL_LIBRARIES}")
message(STATUS "  GLFW:      ${GLFW3_LIBRARY}")
message(STATUS "  glbinding: ${GLBINDING_LIBRARIES}")

######################################################################
add_library(smartnova sn/Program.cpp)
target_link_libraries(smartnova ${gllibs})

message(STATUS "GLFW_LIBRARIES =   ${GLFW_LIBRARY}")
message(STATUS "OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")

include_directories(sn)
list(APPEND gllibs smartnova)

foreach(X app glfw)
  add_executable(${X} sn/test/${X}.cpp)
  target_link_libraries(${X} ${gllibs})
endforeach(X)

######################################################################
set(SBSRC
    sb02a sb02b sb02c
    sb03a sb03b sb03c sb03d sb03e sb03f sb03g
    sb04
    sb05a sb05b sb05c sb05d sb05e sb05f sb05f1 sb05g
    )

foreach(X ${SBSRC})
  add_executable(${X} sb/${X}.cpp)
  target_link_libraries(${X} smartnova ${COMMON_LIBS})
endforeach(X)

######################################################################
# add_subdirectory(cb)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/cb)
#
#foreach(X cb02a)
#  add_executable(${X} cb/cb02/${X}.cpp)
#  target_link_libraries(${X} smartnova ${COMMON_LIBS})
#endforeach(X)
