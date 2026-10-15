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
