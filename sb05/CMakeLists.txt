forEach(X a b c d e f f1 g)
  add_executable(sb05${X} sb05${X}.cpp)
  target_link_libraries(sb05${X} ${sblibs})
endForEach(X)
