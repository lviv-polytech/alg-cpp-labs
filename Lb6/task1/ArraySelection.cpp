#include "ArraySelection.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>

namespace Lb6::Task1 {

bool isSelected(const int index, const int value) {
    return (value % 6 == 0) || (index % 5 != 0);
}

// ============================================================================
// Iterative Implementations (Method 1)
// ============================================================================

void generateArray(std::vector<int>& values, const int low, const int high) {
    if (values.size() != SELECTION_SIZE) {
        values.resize(SELECTION_SIZE);
    }
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(low, high);
    for (std::size_t i = 0; i < values.size(); ++i) {
        values[i] = distribution(engine);
    }
}

void printArray(std::ostream& out, const std::vector<int>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        out << std::setw(4) << values[i];
    }
    out << '\n';
}

int countElements(const std::vector<int>& values) {
    if (values.size() != SELECTION_SIZE) {
        throw std::invalid_argument("Array must have exactly 25 elements.");
    }
    int count = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (isSelected(static_cast<int>(i), values[i])) {
            ++count;
        }
    }
    return count;
}

int sumElements(const std::vector<int>& values) {
    if (values.size() != SELECTION_SIZE) {
        throw std::invalid_argument("Array must have exactly 25 elements.");
    }
    int totalSum = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (isSelected(static_cast<int>(i), values[i])) {
            totalSum += values[i];
        }
    }
    return totalSum;
}

void zeroElements(std::vector<int>& values) {
    if (values.size() != SELECTION_SIZE) {
        throw std::invalid_argument("Array must have exactly 25 elements.");
    }
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (isSelected(static_cast<int>(i), values[i])) {
            values[i] = 0;
        }
    }
}

// ============================================================================
// Recursive Implementations (Method 2)
// ============================================================================

void generateArrayRec(std::vector<int>& values, const int low, const int high, const std::size_t i) {
    if (i == 0 && values.size() != SELECTION_SIZE) {
        values.resize(SELECTION_SIZE);
    }
    if (i >= values.size()) {
        return;
    }
    static thread_local std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution(low, high);
    values[i] = distribution(engine);
    generateArrayRec(values, low, high, i + 1);
}

void printArrayRec(std::ostream& out, const std::vector<int>& values, const std::size_t i) {
    if (i >= values.size()) {
        out << '\n';
        return;
    }
    out << std::setw(4) << values[i];
    printArrayRec(out, values, i + 1);
}

int countElementsRec(const std::vector<int>& values, const std::size_t i) {
    if (values.size() != SELECTION_SIZE) {
        throw std::invalid_argument("Array must have exactly 25 elements.");
    }
    if (i >= values.size()) {
        return 0;
    }
    const int match = isSelected(static_cast<int>(i), values[i]) ? 1 : 0;
    return match + countElementsRec(values, i + 1);
}

int sumElementsRec(const std::vector<int>& values, const std::size_t i) {
    if (values.size() != SELECTION_SIZE) {
        throw std::invalid_argument("Array must have exactly 25 elements.");
    }
    if (i >= values.size()) {
        return 0;
    }
    const int contribution = isSelected(static_cast<int>(i), values[i]) ? values[i] : 0;
    return contribution + sumElementsRec(values, i + 1);
}

void zeroElementsRec(std::vector<int>& values, const std::size_t i) {
    if (values.size() != SELECTION_SIZE) {
        throw std::invalid_argument("Array must have exactly 25 elements.");
    }
    if (i >= values.size()) {
        return;
    }
    if (isSelected(static_cast<int>(i), values[i])) {
        values[i] = 0;
    }
    zeroElementsRec(values, i + 1);
}

// ============================================================================
// Orchestration & Unified API
// ============================================================================

int countSelected(const std::vector<int>& values, const bool recursive) {
    return recursive ? countElementsRec(values, 0) : countElements(values);
}

int sumSelected(const std::vector<int>& values, const bool recursive) {
    return recursive ? sumElementsRec(values, 0) : sumElements(values);
}

void zeroSelected(std::vector<int>& values, const bool recursive) {
    if (recursive) {
        zeroElementsRec(values, 0);
    } else {
        zeroElements(values);
    }
}

SelectionResult processSelection(std::vector<int>& values, const bool recursive) {
    if (values.size() != SELECTION_SIZE) {
        throw std::invalid_argument("Array must have exactly 25 elements.");
    }
    // Critical sequence: count and sum must be calculated BEFORE zeroing
    const int count = countSelected(values, recursive);
    const int sum = sumSelected(values, recursive);
    zeroSelected(values, recursive);
    return SelectionResult{count, sum};
}

} // namespace Lb6::Task1
