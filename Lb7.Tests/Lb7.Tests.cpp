#include "../Lb7/Tasks.h"

#include <cstdlib>
#include <iostream>

namespace {
void requireImpl(const bool condition, const int line) {
    if (!condition) {
        std::cerr << "Lb7 test failed at line " << line << ".\n";
        std::exit(1);
    }
}
#define require(condition) requireImpl((condition), __LINE__)
}

int main() {
    const Lb7::IntMatrix rowFixture{
        {30, 20, 11, 50, 13},
        {15, 40, 22, 35, 17},
        {15, 40, 29, 20, 19},
        {15, 25, 61, 60, 12}};
    const Lb7::IntMatrix sorted{
        {15, 25, 61, 60, 12},
        {15, 40, 29, 20, 19},
        {15, 40, 22, 35, 17},
        {30, 20, 11, 50, 13}};
    Lb7::IntMatrix equalKeys{{1, 2, 9, 4, 10}, {1, 2, 3, 4, 11}};
    for (bool recursive : {false, true}) {
        auto matrix = rowFixture;
        Lb7::sortRows(matrix, recursive);
        require(matrix == sorted);
        Lb7::sortRows(equalKeys, recursive);
        require(equalKeys == Lb7::IntMatrix({{1, 2, 9, 4, 10}, {1, 2, 3, 4, 11}}));
        require(Lb7::countSelected({{6, 12}, {18, 24}}, recursive) == 0);
        auto divisibleBySix = Lb7::IntMatrix{{6, 12}, {18, 24}};
        Lb7::zeroSelected(divisibleBySix, recursive);
        require(divisibleBySix == Lb7::IntMatrix({{6, 12}, {18, 24}}));
        require(Lb7::countSelected(rowFixture, recursive) == 17);
        require(Lb7::sumSelected(rowFixture, recursive) == 447);
        Lb7::RealMatrix values{{4, 9, 1}, {7, 2, 8}, {5, 3, 6}};
        Lb7::diagonalLargest(values, recursive);
        require(values[0][0] == 9 && values[1][1] == 8 && values[2][2] == 7);
        require(Lb7::firstRowWithoutPositive({{1.5, -2, 3}, {-1, 0, -4.5}, {2, 2, 2}}, recursive) == 1);
        require(Lb7::firstRowWithoutPositive({{1, 2}, {0, 3}}, recursive) == -1);
        require(Lb7::firstRowWithoutPositive({{-1}}, recursive) == 0);
    }
    Lb7::IntMatrix pairs{{5, 8, 2}, {9, 1, 7}, {4, 6, 3}, {0, 12, -2}};
    require(Lb7::findMinInRow({{2, 2, 1, 1}}, 0) == 2);
    require(Lb7::findMaxInRow({{3, 9, 9}}, 0) == 1);
    Lb7::processMatrixPairs(pairs);
    require(pairs == Lb7::IntMatrix({{5, 8, 9}, {2, 1, 7}, {4, 6, 12}, {0, 3, -2}}));
    Lb7::IntMatrix oddRows{{7, 1}, {4, 2}, {8, 0}};
    Lb7::processMatrixPairs(oddRows);
    require(oddRows[2] == std::vector<int>({8, 0}));
    std::cout << "Lb7 tests passed.\n";
}
