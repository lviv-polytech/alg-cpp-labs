cmake_minimum_required(VERSION 3.20)
project(alg_cpp_labs CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(Lb1
        Lb1/Lb1.cpp
        Lb1/calculate_factorial.cpp
)

add_executable(Lb1_tests
        Lb1.Tests/Lb1.Tests.cpp
        Lb1.Tests/factorial_and_print_test.cpp
        Lb1/calculate_factorial.cpp
)

add_executable(Lb2
        Lb2/Lb2.cpp
        Lb2/SevenTeen.cpp
)

add_executable(Lb2_tests
        Lb2.Tests/Lb2.Tests.cpp
)
