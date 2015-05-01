cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 -DOS_${CMAKE_SYSTEM_NAME} -DSYSTEM_NAME=\\\"${CMAKE_SYSTEM_NAME}\\\"")

find_package(OpenGL)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} sn)

set(COMMON_LIBS ${OPENGL_LIBRARIES} ${GLFW_LDFLAGS})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  pkg_search_module(GLEW REQUIRED glew)
  include_directories(${GLEW_INCLUDE_DIRS} $ENV{BREW_INCLUDE_PATH})
  list(APPEND COMMON_LIBS ${GLEW_LDFLAGS})
elseif (${MSYS})
elseif (${UNIX})
endif  ()

######################################################################
add_library(smartnova sn/Program.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)

# foreach(X glm glm_sample)
#   add_executable(${X} sn/test/${X}.cpp)
#   target_link_libraries(${X} smartnova ${COMMON_LIBS})
# endforeach(X)

foreach(X app glm glew glfw)
  add_executable(${X} sn/test/${X}.cpp)
  target_link_libraries(${X} smartnova ${COMMON_LIBS})
endforeach(X)

######################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
