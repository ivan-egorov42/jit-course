include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(compiler_gtests
   builder-test.cpp
   rpo-test.cpp
   domtree-test.cpp
)

target_link_libraries(compiler_gtests
    PUBLIC jit_compiler
    PUBLIC GTest::gtest_main
)

gtest_discover_tests(compiler_gtests)