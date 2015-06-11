add_library(smartnova Utility.cpp Program.cpp)
target_link_libraries(smartnova json11 ${gllibs})
