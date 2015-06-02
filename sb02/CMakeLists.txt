forEach(X a b c)
  add_executable(sb02${X} sb02${X}.cpp)
  target_link_libraries(sb02${X} ${sblibs})
endForEach(X)
