cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(OpenGL)

find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glm)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(
  ${OPENGL_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  sn)

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(sn sn/sngl.cpp sn/snshader.cpp)

set(COMMON_LIBS
  sn
  ${OPENGL_LIBRARIES}
  ${GLFW_LDFLAGS}
  ${GLEW_LDFLAGS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/sb)

set(SBSRC
  sb02a sb02b sb02c
  sb03a sb03b sb03c sb03d sb03d1 sb03e sb03f sb03g
  sb04
  sb05a sb05b sb05c sb05d sb05e sb05f sb05f1 sb05g
  )

foreach(X ${SBSRC})
  add_executable(${X} sb/${X}.cpp)
  target_link_libraries(${X} ${COMMON_LIBS})
endforeach(X)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/sn/test)

set(SNTS glew glfw glm glm_sample app)

foreach(X ${SNTS})
  add_executable(${X} sn/test/${X}.cpp)
  target_link_libraries(${X} ${COMMON_LIBS})
endforeach(X)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/cb)
