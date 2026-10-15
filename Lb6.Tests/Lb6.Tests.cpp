#include "../Lb6/Tasks.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

namespace {
void require(bool condition) {
    if (!condition) {
        std::cerr << "Lb6 test failed.\n";
        std::exit(1);
    }
}
}

int main() {
    // ------------------------------------------------------------------------
    // Task 6.1 (Variant 17) Reference Test Vector
    // ------------------------------------------------------------------------
    const std::vector<int> r_test{
        12, 10, 15, 20, 30, // Group 1: i=0..4, r[0]=12 is divisible by 6
        25, 10, 15, 20, 30, // Group 2: i=5..9, r[5]=25 is NOT divisible by 6 (preserved)
        42, 10, 15, 20, 30, // Group 3: i=10..14, r[10]=42 is divisible by 6
        19, 10, 15, 20, 30, // Group 4: i=15..19, r[15]=19 is NOT divisible by 6 (preserved)
        73, 10, 15, 20, 30  // Group 5: i=20..24, r[20]=73 is NOT divisible by 6 (preserved)
    };

    // Test 1: Iterative Functions
    {
        require(Lb6::Task1::countElements(r_test) == 22);
        require(Lb6::Task1::sumElements(r_test) == 429);

        auto r_mod = r_test;
        Lb6::Task1::zeroElements(r_mod);
        require(r_mod[5] == 25);
        require(r_mod[15] == 19);
        require(r_mod[20] == 73);
        for (std::size_t i = 0; i < r_mod.size(); ++i) {
            if (i != 5 && i != 15 && i != 20) {
                require(r_mod[i] == 0);
            }
        }
    }

    // Test 2: Recursive Functions
    {
        require(Lb6::Task1::countElementsRec(r_test, 0) == 22);
        require(Lb6::Task1::sumElementsRec(r_test, 0) == 429);

        auto r_mod = r_test;
        Lb6::Task1::zeroElementsRec(r_mod, 0);
        require(r_mod[5] == 25);
        require(r_mod[15] == 19);
        require(r_mod[20] == 73);
        for (std::size_t i = 0; i < r_mod.size(); ++i) {
            if (i != 5 && i != 15 && i != 20) {
                require(r_mod[i] == 0);
            }
        }
    }

    // Test 3: Orchestration / processSelection
    for (bool recursive : {false, true}) {
        auto r_mod = r_test;
        const auto result = Lb6::processSelection(r_mod, recursive);
        require(result.count == 22 && result.sum == 429);
        require(r_mod[5] == 25 && r_mod[15] == 19 && r_mod[20] == 73);
    }

    // Test 4: Exception on invalid size
    {
        bool caught = false;
        try {
            Lb6::Task1::countElements({1, 2, 3});
        } catch (const std::invalid_argument&) {
            caught = true;
        }
        require(caught);
    }

    // ------------------------------------------------------------------------
    // Task 6.2 (Variant 17) Verification Matrix: TC-01 .. TC-09
    // ------------------------------------------------------------------------
    const struct TestCase {
        std::vector<int> input;
        int expectedIndex;
    } testCases[] = {
        {{3, 8, 15, 12, 7, 4}, 3},       // TC-01: Base test, odd max 15 ignored, max even is 12 at index 3
        {{5, -3, 11, 1, 9}, -1},          // TC-02: No even elements -> -1
        {{-10, -4, -7, -2, -8}, 3},       // TC-03: All even elements negative, max is -2 at index 3
        {{-5, 0, -2, -9}, 1},             // TC-04: Zero as even number (0 > -2) at index 1
        {{6, 14, 9, 14, 2}, 1},           // TC-05: Duplicate max even values -> first occurrence at index 1
        {{42}, 0},                        // TC-06: Single even element at index 0
        {{17}, -1},                       // TC-07: Single odd element -> -1
        {{20, 4, 2, -6}, 0},              // TC-08: Maximum at first position (i = 0)
        {{2, 4, 8, 24}, 3},               // TC-09: Maximum at last position (i = n - 1)
        {{}, -1}                          // Empty vector -> -1
    };

    // Test Task 2 Iterative
    for (const auto& tc : testCases) {
        require(Lb6::Task2::findMaxEvenIndexIterative(tc.input) == tc.expectedIndex);
    }

    // Test Task 2 Recursive
    for (const auto& tc : testCases) {
        require(Lb6::Task2::findMaxEvenIndexRecursive(tc.input, 0, -1) == tc.expectedIndex);
    }

    // Test Task 2 Unified Dispatcher
    for (bool recursive : {false, true}) {
        for (const auto& tc : testCases) {
            require(Lb6::maxEvenIndex(tc.input, recursive) == tc.expectedIndex);
        }
    }

    for (bool recursive : {false, true}) {
        std::vector<double> data{1.5, 0, -3.2, 2.0, 0.7, 0, 4.5, -1.0, 2.5};
        require(Lb6::Dynamic::countPositive(data, recursive) == 5);
        const int zero = Lb6::Dynamic::lastZeroIndex(data, recursive);
        require(zero == 5);
        require(std::fabs(Lb6::Dynamic::sumAfter(data, zero, recursive) - 6.0) < 1e-12);
        Lb6::Dynamic::stablePartition(data, recursive);
        require((data == std::vector<double>{1.5, 0, -3.2, 0.7, 0, -1.0, 2.0, 4.5, 2.5}));
        std::vector<double> noZeros{1, -2, 3};
        require(Lb6::Dynamic::lastZeroIndex(noZeros, recursive) == -1);
        std::vector<double> zeroAtEnd{2, 0};
        require(Lb6::Dynamic::lastZeroIndex(zeroAtEnd, recursive) == 1);
        require(Lb6::Dynamic::sumAfter(zeroAtEnd, 1, recursive) == 0);
        std::vector<double> allLow{-2, 0.5, 1.9};
        Lb6::Dynamic::stablePartition(allLow, recursive);
        require((allLow == std::vector<double>{-2, 0.5, 1.9}));
        std::vector<double> allHigh{2, 3, 4};
        Lb6::Dynamic::stablePartition(allHigh, recursive);
        require((allHigh == std::vector<double>{2, 3, 4}));
    }
    // ------------------------------------------------------------------------
    // Task 6.3 Verification Matrix: TC-01 .. TC-07
    // ------------------------------------------------------------------------
    // TC-01: Ordinary int function (n = 5)
    {
        int arrIt[5]{};
        std::istringstream streamIt("10 -25 0 42 -7");
        Lb6::Task3::inputArrayIterative(arrIt, 5, streamIt);
        require(arrIt[0] == 10 && arrIt[1] == -25 && arrIt[2] == 0 && arrIt[3] == 42 && arrIt[4] == -7);

        int arrRec[5]{};
        std::istringstream streamRec("10 -25 0 42 -7");
        Lb6::Task3::inputArrayRecursive(arrRec, 5, 0, streamRec);
        require(arrRec[0] == 10 && arrRec[1] == -25 && arrRec[2] == 0 && arrRec[3] == 42 && arrRec[4] == -7);
    }

    // TC-02: Template function with T = int (n = 5)
    {
        int arrIt[5]{};
        std::istringstream streamIt("10 -25 0 42 -7");
        Lb6::Task3::inputArrayIterativeTemplate(arrIt, 5, streamIt);
        require(arrIt[0] == 10 && arrIt[1] == -25 && arrIt[2] == 0 && arrIt[3] == 42 && arrIt[4] == -7);

        int arrRec[5]{};
        std::istringstream streamRec("10 -25 0 42 -7");
        Lb6::Task3::inputArrayRecursiveTemplate(arrRec, 5, 0, streamRec);
        require(arrRec[0] == 10 && arrRec[1] == -25 && arrRec[2] == 0 && arrRec[3] == 42 && arrRec[4] == -7);
    }

    // TC-03: Template function with T = double (n = 4)
    {
        double arrIt[4]{};
        std::istringstream streamIt("3.14 -0.005 0.0 100.25");
        Lb6::Task3::inputArrayIterativeTemplate(arrIt, 4, streamIt);
        require(std::fabs(arrIt[0] - 3.14) < 1e-9 && std::fabs(arrIt[1] - (-0.005)) < 1e-9 &&
                std::fabs(arrIt[2] - 0.0) < 1e-9 && std::fabs(arrIt[3] - 100.25) < 1e-9);

        double arrRec[4]{};
        std::istringstream streamRec("3.14 -0.005 0.0 100.25");
        Lb6::Task3::inputArrayRecursiveTemplate(arrRec, 4, 0, streamRec);
        require(std::fabs(arrRec[0] - 3.14) < 1e-9 && std::fabs(arrRec[1] - (-0.005)) < 1e-9 &&
                std::fabs(arrRec[2] - 0.0) < 1e-9 && std::fabs(arrRec[3] - 100.25) < 1e-9);
    }

    // TC-04: Template function with T = string (n = 3)
    {
        std::string arrIt[3];
        std::istringstream streamIt("alpha beta gamma");
        Lb6::Task3::inputArrayIterativeTemplate(arrIt, 3, streamIt);
        require(arrIt[0] == "alpha" && arrIt[1] == "beta" && arrIt[2] == "gamma");

        std::string arrRec[3];
        std::istringstream streamRec("alpha beta gamma");
        Lb6::Task3::inputArrayRecursiveTemplate(arrRec, 3, 0, streamRec);
        require(arrRec[0] == "alpha" && arrRec[1] == "beta" && arrRec[2] == "gamma");
    }

    // TC-05: Single element (n = 1)
    {
        int arrIt[1]{};
        std::istringstream streamIt("-999");
        Lb6::Task3::inputArrayIterative(arrIt, 1, streamIt);
        require(arrIt[0] == -999);

        int arrRec[1]{};
        std::istringstream streamRec("-999");
        Lb6::Task3::inputArrayRecursive(arrRec, 1, 0, streamRec);
        require(arrRec[0] == -999);
    }

    // TC-06: Zero elements (n = 0, no reads performed)
    {
        int arrIt[1]{ 777 };
        std::istringstream streamIt("100 200");
        Lb6::Task3::inputArrayIterative(arrIt, 0, streamIt);
        require(arrIt[0] == 777);

        int arrRec[1]{ 777 };
        std::istringstream streamRec("100 200");
        Lb6::Task3::inputArrayRecursive(arrRec, 0, 0, streamRec);
        require(arrRec[0] == 777);
    }

    // TC-07: Diverse delimiters and extra tokens remaining in stream
    {
        int arrIt[3]{};
        std::istringstream streamIt("  5 \n\t 12 \n  -8  99 100");
        Lb6::Task3::inputArrayIterative(arrIt, 3, streamIt);
        require(arrIt[0] == 5 && arrIt[1] == 12 && arrIt[2] == -8);
        int extra = 0;
        streamIt >> extra;
        require(extra == 99);

        int arrRec[3]{};
        std::istringstream streamRec("  5 \n\t 12 \n  -8  99 100");
        Lb6::Task3::inputArrayRecursive(arrRec, 3, 0, streamRec);
        require(arrRec[0] == 5 && arrRec[1] == 12 && arrRec[2] == -8);
        extra = 0;
        streamRec >> extra;
        require(extra == 99);
    }

    // Formatted print tests
    {
        int sample[3] = { 1, 2, 3 };
        std::ostringstream outIt, outRec;
        Lb6::Task3::printArrayIterative(sample, 3, outIt, 4);
        Lb6::Task3::printArrayRecursive(sample, 3, 0, outRec, 4);
        require(outIt.str() == "   1   2   3\n");
        require(outRec.str() == "   1   2   3\n");
    }

    // Backward compatibility checks
    int integers[3]{};
    std::istringstream input("3 5 7");
    std::ostringstream prompts;
    Lb6::Recursive::input(input, prompts, integers, 3);
    require(integers[0] == 3 && integers[2] == 7);
    double values[2]{};
    std::istringstream decimals("1.5 2.25");
    Lb6::inputTemplate(decimals, prompts, values, 2);
    require(values[0] == 1.5 && values[1] == 2.25);
    std::string words[2];
    std::istringstream text("a bb");
    Lb6::inputTemplateRecursive(text, prompts, words, 2);
    require(words[0] == "a" && words[1] == "bb");
    std::cout << "Lb6 tests passed.\n";
}
