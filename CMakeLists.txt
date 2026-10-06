cmake_minimum_required(VERSION 3.20)
project(alg_cpp_labs CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

enable_testing()

add_executable(Lb1
        Lb1/Lb1.cpp
        Lb1/calculate_factorial.cpp
)

add_executable(Lb1_tests
        Lb1.Tests/Lb1.Tests.cpp
        Lb1.Tests/factorial_and_print_test.cpp
        Lb1/calculate_factorial.cpp
)

add_test(NAME Lb1_Test COMMAND Lb1_tests)

add_executable(Lb2
        Lb2/Lb2.cpp
        Lb2/SevenTeen.cpp
)

add_executable(Lb2_tests
        Lb2.Tests/Lb2.Tests.cpp
        Lb2/SevenTeen.cpp
)

add_test(NAME Lb2_Test COMMAND Lb2_tests)

add_executable(Lb3
        Lb3/Lb3.cpp
        Lb3/SevenTeenImpl.cpp
        Lb3/task1/ExpressionImpl.cpp
        Lb3/task2/ExpressionImpl.cpp
        Lb3/task3/ExpressionImpl.cpp
)

add_executable(Lb4
        Lb4/Lb4.cpp
        Lb4/Tasks.cpp
)

add_executable(Lb4_tests
        Lb4.Tests/Lb4.Tests.cpp
        Lb4/Tasks.cpp
)
add_test(NAME Lb4_Test COMMAND Lb4_tests)

add_executable(Lb5
        Lb5/Lb5.cpp
        Lb5/Tasks.cpp
)

add_executable(Lb5_tests
        Lb5.Tests/Lb5.Tests.cpp
        Lb5/Tasks.cpp
)
add_test(NAME Lb5_Test COMMAND Lb5_tests)

add_executable(Lb6
        Lb6/Lb6.cpp
        Lb6/Tasks.cpp
)

add_executable(Lb6_tests
        Lb6.Tests/Lb6.Tests.cpp
        Lb6/Tasks.cpp
)
add_test(NAME Lb6_Test COMMAND Lb6_tests)