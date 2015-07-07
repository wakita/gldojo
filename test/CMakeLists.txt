add_executable(json json.cpp)
target_link_libraries(json json11)

add_executable(config config.cpp)
target_link_libraries(config smartnova json11)

add_executable(test-config test-config.cpp)
target_link_libraries(test-config smartnova cb json11)
