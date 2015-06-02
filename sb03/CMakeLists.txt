forEach(X a b c d e f g)
  add_executable(sb03${X} sb03${X}.cpp)
  target_link_libraries(sb03${X} ${sblibs})
endForEach(X)
