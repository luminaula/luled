project(color_test)

add_executable(transfer_test transfer_test.cpp)

target_link_libraries(transfer_test color)

add_test(NAME transfer_test COMMAND transfer_test)