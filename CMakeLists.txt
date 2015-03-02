cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(OpenGL)

find_package(Boost COMPONENTS system filesystem)

find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glm)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  sn)

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(sn sn/sngl.cpp sn/snshader.cpp)
add_library(smartnova sn/Program.cpp)

set(COMMON_LIBS
  ${Boost_LIBRARIES}
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
  target_link_libraries(${X} sn ${COMMON_LIBS})
endforeach(X)

foreach(X
    sb02ax sb02bx sb02cx
    sb03ax sb03bx sb03cx sb03dx sb03ex sb03fx sb03gx
    sb05ax sb05bx sb05cx sb05dx sb05ex sb05fx)
  add_executable(${X} sb/${X}.cpp)
  target_link_libraries(${X} smartnova ${COMMON_LIBS})
endforeach(X)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/sn/test)

set(SNTS glm glm_sample)

foreach(X ${SNTS})
  add_executable(${X} sn/test/${X}.cpp)
  target_link_libraries(${X} sn ${COMMON_LIBS})
endforeach(X)

foreach(X app glew glfw)
  add_executable(${X} sn/test/${X}.cpp)
  target_link_libraries(${X} smartnova ${COMMON_LIBS})
endforeach(X)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/cb)
