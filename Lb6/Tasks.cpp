#include "Tasks.h"

#include <iomanip>
#include <istream>
#include <ostream>
#include <random>
#include <stdexcept>
#include <utility>

namespace Lb6 {
namespace {
void inputIntRecursive(std::istream& in, std::ostream& out, int* values,
                       const std::size_t size, const std::size_t index) {
    if (index >= size) return;
    out << "a[" << index << "] = ";
    if (!(in >> values[index])) throw std::runtime_error("Failed to read array element.");
    inputIntRecursive(in, out, values, size, index + 1);
}
void inputStringRecursive(std::istream& in, std::ostream& out, std::string* values,
                          const std::size_t size, const std::size_t index) {
    if (index >= size) return;
    out << "a[" << index << "] = ";
    if (!(in >> values[index])) throw std::runtime_error("Failed to read array element.");
    inputStringRecursive(in, out, values, size, index + 1);
}
int evenIndexRecursive(const std::vector<int>& values, const std::size_t index, int best) {
    if (index == values.size()) return best;
    if (values[index] % 2 == 0 && (best == -1 || values[index] > values[best]))
        best = static_cast<int>(index);
    return evenIndexRecursive(values, index + 1, best);
}
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
int countPositiveRecursive(const std::vector<double>& values, const std::size_t index) {
    return index == values.size() ? 0 : (values[index] > 0.0) +
           countPositiveRecursive(values, index + 1);
}
int lastZeroRecursive(const std::vector<double>& values, const std::size_t index, const int last) {
    return index == values.size() ? last :
           lastZeroRecursive(values, index + 1, values[index] == 0.0 ? static_cast<int>(index) : last);
}
double sumAfterRecursive(const std::vector<double>& values, const std::size_t index) {
    return index == values.size() ? 0.0 : values[index] + sumAfterRecursive(values, index + 1);
}
void partitionRecursive(std::vector<double>& values, const std::size_t index) {
    if (index == values.size()) return;
    const double current = values[index];
    partitionRecursive(values, index + 1);
    if (current >= 2.0) {
        std::size_t lowCount = 0;
        while (index + 1 + lowCount < values.size() && values[index + 1 + lowCount] < 2.0)
            ++lowCount;
        for (std::size_t j = 0; j < lowCount; ++j)
            values[index + j] = values[index + 1 + j];
        values[index + lowCount] = current;
    }
}
}  // namespace

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

int maxEvenIndex(const std::vector<int>& values, const bool recursive) {
    if (recursive) return evenIndexRecursive(values, 0, -1);
    int best = -1;
    for (std::size_t i = 0; i < values.size(); ++i)
        if (values[i] % 2 == 0 && (best == -1 || values[i] > values[best]))
            best = static_cast<int>(i);
    return best;
}

namespace Iterative {
void input(std::istream& in, std::ostream& out, int* values, const std::size_t size) {
    inputTemplate(in, out, values, size);
}
void input(std::istream& in, std::ostream& out, std::string* values, const std::size_t size) {
    inputTemplate(in, out, values, size);
}
}
namespace Recursive {
void input(std::istream& in, std::ostream& out, int* values, const std::size_t size) {
    inputIntRecursive(in, out, values, size, 0);
}
void input(std::istream& in, std::ostream& out, std::string* values, const std::size_t size) {
    inputStringRecursive(in, out, values, size, 0);
}
}

namespace Dynamic {
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
}

std::vector<int> createArray(const unsigned seed) {
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> distribution(4, 73);
    std::vector<int> values(SELECTION_SIZE);
    for (int& value : values) value = distribution(engine);
    return values;
}
void printArray(std::ostream& out, const std::vector<int>& values) {
    for (int value : values) out << std::setw(4) << value;
    out << '\n';
}
void printArray(std::ostream& out, const std::vector<double>& values) {
    out << std::fixed << std::setprecision(2);
    for (double value : values) out << std::setw(8) << value;
    out << '\n';
}
}  // namespace Lb6
