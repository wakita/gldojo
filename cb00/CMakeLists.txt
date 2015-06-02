set(cblib_SOURCES
  vboteapotpatch.cpp
  vboteapot.cpp
  drawable.cpp 
  vbomeshadj.cpp 
  vbotorus.cpp 
  glutils.cpp 
  vbomesh.cpp 
  glslprogram.cpp 
  vbocube.cpp 
  vboplane.cpp 
  vbosphere.cpp
  bmpreader.cpp
  tgaio.cpp
)

add_library(cb ${cblib_SOURCES})
target_link_libraries(cb ${OPENGL_LIBRARIES} ${GLBINDING_LIBRARIES} ${OPENGL_LIBRARIES})

add_executable(h h.cpp)
