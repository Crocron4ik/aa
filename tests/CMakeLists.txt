add_executable(Run-tests test_complex.cpp test_expr.cpp)
target_link_libraries(Run-tests PRIVATE complex_expr Catch2::Catch2WithMain)
target_link_libraries(Run-tests PRIVATE complex_expr Catch2::Catch2WithMain)


