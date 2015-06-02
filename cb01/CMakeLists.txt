#set( chapter01_SOURCES  
#	scenebasic.cpp
#	main.cpp
#	scenebasic_uniformblock.cpp
#	scenebasic_attrib.cpp
#	scenebasic_uniform.cpp
#	scenebasic_debug.cpp )

message(STATUS "Runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

forEach(X a b c d e)
  add_executable(cb01${X} cb01${X}.cpp)
  target_link_libraries(cb01${X} ${glcblibs})
endForEach(X)
#add_executable( chapter01 ${chapter01_SOURCES} )
#target_link_libraries( chapter01 ${GLSLCOOKBOOK_LIBS} )
