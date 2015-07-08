add_executable(json json.cpp)
target_link_libraries(json json11)

add_executable(config config.cpp)
target_link_libraries(config smartnova json11)
