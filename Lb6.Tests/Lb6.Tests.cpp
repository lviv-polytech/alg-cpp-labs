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
    const std::vector<int> expected{
        7,12,25,31,44, 9,18,50,61,5, 30,73,4,66,27, 35,48,13,59,70, 8,42,16,37,55};
    for (bool recursive : {false, true}) {
        auto selected = expected;
        const auto result = Lb6::processSelection(selected, recursive);
        require(result.count == 21 && result.sum == 786);
        require(selected[0] == 7 && selected[5] == 9 && selected[15] == 35 && selected[20] == 8);
        require(selected[1] == 0 && selected[10] == 0);
        require(Lb6::maxEvenIndex({3, -8, 14, 7, 14, 2, 9}, recursive) == 2);
        require(Lb6::maxEvenIndex({1, 3, 5}, recursive) == -1);
        require(Lb6::maxEvenIndex({-4, -2, -10}, recursive) == 1);
        require(Lb6::maxEvenIndex({0}, recursive) == 0);
        require(Lb6::maxEvenIndex({4, 6, 6}, recursive) == 1);
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
