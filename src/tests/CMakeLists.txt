add_executable(tests main.cpp integration_test.cpp)
target_link_libraries(tests StoreLib Catch2::Catch2)
