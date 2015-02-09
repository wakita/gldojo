cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(OpenGL)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glm)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(
  ${OPENGL_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  include)

set(COMMON_LIBS
  ${OPENGL_LIBRARIES}
  ${GLFW_LDFLAGS}
  ${GLEW_LDFLAGS})

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(sn src/sngl.cpp src/snshader.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXAMPLES
  chap02a chap02b chap02c
  chap03a chap03b chap03c chap03d chap03d1 chap03e chap03f chap03g
  chap04
  chap05a chap05b chap05c chap05d chap05e chap05f chap05f1 chap05g
  )

foreach(EXAMPLE ${EXAMPLES})
  add_executable(${EXAMPLE} src/${EXAMPLE}.cpp)
  target_link_libraries(${EXAMPLE} sn ${COMMON_LIBS})
endforeach(EXAMPLE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)

set(TESTS glew glfw glm glm_sample)

foreach(TEST ${TESTS})
  add_executable(${TEST} src/test/${TEST}.cpp)
  target_link_libraries(${TEST} ${COMMON_LIBS})
endforeach(TEST)

foreach (TEST app)
  add_executable(${TEST} src/test/${TEST}.cpp)
  target_link_libraries(${TEST} sn ${COMMON_LIBS})
endforeach(TEST)
