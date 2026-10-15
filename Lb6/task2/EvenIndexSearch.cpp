#include "EvenIndexSearch.h"

#include <iomanip>
#include <iostream>
#include <random>

namespace Lb6::Task2 {

bool isEven(const int value) {
    return value % 2 == 0;
}

// ============================================================================
// Iterative Implementations (Method 1)
// ============================================================================

void initArrayIterative(std::vector<int>& a, const int minVal, const int maxVal) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(minVal, maxVal);
    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = distribution(engine);
    }
}

void printArrayIterative(std::ostream& out, const std::vector<int>& a) {
    for (std::size_t i = 0; i < a.size(); ++i) {
        out << std::setw(5) << a[i];
    }
    out << '\n';
}

int findMaxEvenIndexIterative(const std::vector<int>& a) {
    int bestIndex = -1;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (isEven(a[i])) {
            if (bestIndex == -1 || a[i] > a[bestIndex]) {
                bestIndex = static_cast<int>(i);
            }
        }
    }
    return bestIndex;
}

// ============================================================================
// Recursive Implementations (Method 2)
// ============================================================================

void initArrayRecursive(std::vector<int>& a, const int minVal, const int maxVal, const std::size_t i) {
    if (i >= a.size()) {
        return;
    }
    static thread_local std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution(minVal, maxVal);
    a[i] = distribution(engine);
    initArrayRecursive(a, minVal, maxVal, i + 1);
}

void printArrayRecursive(std::ostream& out, const std::vector<int>& a, const std::size_t i) {
    if (i >= a.size()) {
        out << '\n';
        return;
    }
    out << std::setw(5) << a[i];
    printArrayRecursive(out, a, i + 1);
}

int findMaxEvenIndexRecursive(const std::vector<int>& a, const std::size_t i, const int bestIndex) {
    if (i >= a.size()) {
        return bestIndex;
    }
    int nextBest = bestIndex;
    if (isEven(a[i])) {
        if (bestIndex == -1 || a[i] > a[bestIndex]) {
            nextBest = static_cast<int>(i);
        }
    }
    return findMaxEvenIndexRecursive(a, i + 1, nextBest);
}

// ============================================================================
// Unified API
// ============================================================================

int maxEvenIndex(const std::vector<int>& values, const bool recursive) {
    return recursive ? findMaxEvenIndexRecursive(values, 0, -1)
                     : findMaxEvenIndexIterative(values);
}

} // namespace Lb6::Task2
