cmake_minimum_required(VERSION 3.20)
project(alg_cpp_labs CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

enable_testing()

add_library(Common STATIC
        Common/IO.cpp
)
target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

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
        Lb3/task4/ExpressionImpl.cpp
)

add_executable(Lb3_tests
        Lb3.Tests/Lb3.Tests.cpp
        Lb3/SevenTeenImpl.cpp
        Lb3/task1/ExpressionImpl.cpp
        Lb3/task2/ExpressionImpl.cpp
        Lb3/task3/ExpressionImpl.cpp
        Lb3/task4/ExpressionImpl.cpp
)

add_test(NAME Lb3_Test COMMAND Lb3_tests)


add_executable(Lb4
        Lb4/Lb4.cpp
        Lb4/Tasks.cpp
        Lb4/UI/TablePrinter.cpp
        Lb4/task1/CycleSums.cpp
        Lb4/task2/PiecewiseFormula.cpp
        Lb4/task3/ParametricTabulation.cpp
        Lb4/task4/GraphTabulation.cpp
        Lb4/task5/NestedSums.cpp
        Lb4/task6/TaylorLog.cpp
)
target_link_libraries(Lb4 PRIVATE Common)

add_executable(Lb4_tests
        Lb4.Tests/Lb4.Tests.cpp
        Lb4/Tasks.cpp
        Lb4/UI/TablePrinter.cpp
        Lb4/task1/CycleSums.cpp
        Lb4/task2/PiecewiseFormula.cpp
        Lb4/task3/ParametricTabulation.cpp
        Lb4/task4/GraphTabulation.cpp
        Lb4/task5/NestedSums.cpp
        Lb4/task6/TaylorLog.cpp
)
target_link_libraries(Lb4_tests PRIVATE Common)
add_test(NAME Lb4_Test COMMAND Lb4_tests)

add_executable(Lb5
        Lb5/Lb5.cpp
        Lb5/Tasks.cpp
        Lb5/UI/TablePrinter.cpp
        Lb5/task1/RationalExpression.cpp
        Lb5/task2/TaylorSeries.cpp
        Lb5/task3/PiecewiseExpression.cpp
        Lb5/task4/RecursiveSeries.cpp
        Lb5/task5/GeometricProgression.cpp
)
target_link_libraries(Lb5 PRIVATE Common)

add_executable(Lb5_tests
        Lb5.Tests/Lb5.Tests.cpp
        Lb5/Tasks.cpp
        Lb5/UI/TablePrinter.cpp
        Lb5/task1/RationalExpression.cpp
        Lb5/task2/TaylorSeries.cpp
        Lb5/task3/PiecewiseExpression.cpp
        Lb5/task4/RecursiveSeries.cpp
        Lb5/task5/GeometricProgression.cpp
)
target_link_libraries(Lb5_tests PRIVATE Common)
add_test(NAME Lb5_Test COMMAND Lb5_tests)

add_executable(Lb6
        Lb6/Lb6.cpp
        Lb6/Tasks.cpp
        Lb6/UI/ArrayPrinter.cpp
        Lb6/Infrastructure/ArrayGenerator.cpp
        Lb6/task1/ArraySelection.cpp
        Lb6/task2/EvenIndexSearch.cpp
        Lb6/task3/ArrayInput.cpp
        Lb6/task4/DynamicArrayOperations.cpp
)
target_link_libraries(Lb6 PRIVATE Common)

add_executable(Lb6_tests
        Lb6.Tests/Lb6.Tests.cpp
        Lb6/Tasks.cpp
        Lb6/UI/ArrayPrinter.cpp
        Lb6/Infrastructure/ArrayGenerator.cpp
        Lb6/task1/ArraySelection.cpp
        Lb6/task2/EvenIndexSearch.cpp
        Lb6/task3/ArrayInput.cpp
        Lb6/task4/DynamicArrayOperations.cpp
)
target_link_libraries(Lb6_tests PRIVATE Common)
add_test(NAME Lb6_Test COMMAND Lb6_tests)

add_executable(Lb7
        Lb7/Lb7.cpp
        Lb7/Tasks.cpp
)

add_executable(Lb7_tests
        Lb7.Tests/Lb7.Tests.cpp
        Lb7/Tasks.cpp
)
add_test(NAME Lb7_Test COMMAND Lb7_tests)
