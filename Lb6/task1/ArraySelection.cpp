#include "ArraySelection.h"

#include <stdexcept>

namespace Lb6::Task1 {
namespace {

int countSelectedRecursive(const std::vector<int>& values, const std::size_t index) {
    return index == values.size() ? 0 :
        (isSelected(static_cast<int>(index), values[index]) ? 1 : 0) +
            countSelectedRecursive(values, index + 1);
}

int sumSelectedRecursive(const std::vector<int>& values, const std::size_t index) {
    return index == values.size() ? 0 :
        (isSelected(static_cast<int>(index), values[index]) ? values[index] : 0) +
            sumSelectedRecursive(values, index + 1);
}

void zeroSelectedRecursive(std::vector<int>& values, const std::size_t index) {
    if (index == values.size()) return;
    if (isSelected(static_cast<int>(index), values[index])) values[index] = 0;
    zeroSelectedRecursive(values, index + 1);
}

} // namespace

bool isSelected(const int index, const int value) {
    return value % 6 == 0 || index % 5 != 0;
}

SelectionResult processSelection(std::vector<int>& values, const bool recursive) {
    if (values.size() != SELECTION_SIZE) throw std::invalid_argument("Selection array must have 25 elements.");
    const SelectionResult result{countSelected(values, recursive), sumSelected(values, recursive)};
    zeroSelected(values, recursive);
    return result;
}

int countSelected(const std::vector<int>& values, const bool recursive) {
    if (values.size() != SELECTION_SIZE) throw std::invalid_argument("Selection array must have 25 elements.");
    if (recursive) return countSelectedRecursive(values, 0);
    int count = 0;
    for (std::size_t i = 0; i < values.size(); ++i)
        count += isSelected(static_cast<int>(i), values[i]);
    return count;
}

int sumSelected(const std::vector<int>& values, const bool recursive) {
    if (values.size() != SELECTION_SIZE) throw std::invalid_argument("Selection array must have 25 elements.");
    if (recursive) return sumSelectedRecursive(values, 0);
    int sum = 0;
    for (std::size_t i = 0; i < values.size(); ++i)
        if (isSelected(static_cast<int>(i), values[i])) sum += values[i];
    return sum;
}

void zeroSelected(std::vector<int>& values, const bool recursive) {
    if (values.size() != SELECTION_SIZE) throw std::invalid_argument("Selection array must have 25 elements.");
    if (recursive) {
        zeroSelectedRecursive(values, 0);
        return;
    }
    for (std::size_t i = 0; i < values.size(); ++i)
        if (isSelected(static_cast<int>(i), values[i])) values[i] = 0;
}

} // namespace Lb6::Task1
