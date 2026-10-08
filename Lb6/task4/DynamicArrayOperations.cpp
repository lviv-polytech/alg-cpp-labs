#include "DynamicArrayOperations.h"
#include "../../Common/RecursionTracker.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace Lb6::Task4 {
namespace {

int countPositiveRecursive(const std::vector<double>& values, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "countPositiveRecursive", level, level + 1);
    return index == values.size() ? 0 : (values[index] > 0.0) +
           countPositiveRecursive(values, index + 1, level + 1);
}

int lastZeroRecursive(const std::vector<double>& values, const std::size_t index, const int last, const int level = 0) {
    Common::Recursion::printStep(std::cout, "lastZeroRecursive", level, level + 1);
    return index == values.size() ? last :
           lastZeroRecursive(values, index + 1, values[index] == 0.0 ? static_cast<int>(index) : last, level + 1);
}

double sumAfterRecursive(const std::vector<double>& values, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "sumAfterRecursive", level, level + 1);
    return index == values.size() ? 0.0 : values[index] + sumAfterRecursive(values, index + 1, level + 1);
}

void partitionRecursive(std::vector<double>& values, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "partitionRecursive", level, level + 1);
    if (index == values.size()) return;
    const double current = values[index];
    partitionRecursive(values, index + 1, level + 1);
    if (current >= 2.0) {
        std::size_t lowCount = 0;
        while (index + 1 + lowCount < values.size() && values[index + 1 + lowCount] < 2.0)
            ++lowCount;
        for (std::size_t j = 0; j < lowCount; ++j)
            values[index + j] = values[index + 1 + j];
        values[index + lowCount] = current;
    }
}

} // namespace

int countPositive(const std::vector<double>& values, const bool recursive) {
    if (recursive) return countPositiveRecursive(values, 0);
    int count = 0;
    for (double value : values) count += value > 0.0;
    return count;
}

int lastZeroIndex(const std::vector<double>& values, const bool recursive) {
    if (recursive) return lastZeroRecursive(values, 0, -1);
    int last = -1;
    for (std::size_t i = 0; i < values.size(); ++i)
        if (values[i] == 0.0) last = static_cast<int>(i);
    return last;
}

double sumAfter(const std::vector<double>& values, const int index, const bool recursive) {
    if (index < -1 || index >= static_cast<int>(values.size()))
        throw std::out_of_range("Index must identify a position or be -1.");
    const std::size_t start = static_cast<std::size_t>(index + 1);
    if (recursive) return sumAfterRecursive(values, start);
    double sum = 0.0;
    for (std::size_t i = start; i < values.size(); ++i) sum += values[i];
    return sum;
}

void stablePartition(std::vector<double>& values, const bool recursive) {
    if (recursive) {
        partitionRecursive(values, 0);
        return;
    }
    std::vector<double> reordered;
    reordered.reserve(values.size());
    for (double value : values) if (value < 2.0) reordered.push_back(value);
    for (double value : values) if (value >= 2.0) reordered.push_back(value);
    values.swap(reordered);
}

} // namespace Lb6::Task4
