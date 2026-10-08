#include "Tasks.h"

#include "task1/ArraySelection.h"
#include "task2/EvenIndexSearch.h"
#include "task3/ArrayInput.h"
#include "task4/DynamicArrayOperations.h"
#include "Infrastructure/ArrayGenerator.h"
#include "UI/ArrayPrinter.h"

namespace Lb6 {

bool isSelected(const int index, const int value) {
    return Task1::isSelected(index, value);
}

SelectionResult processSelection(std::vector<int>& values, const bool recursive) {
    const auto res = Task1::processSelection(values, recursive);
    return SelectionResult{res.count, res.sum};
}

int countSelected(const std::vector<int>& values, const bool recursive) {
    return Task1::countSelected(values, recursive);
}

int sumSelected(const std::vector<int>& values, const bool recursive) {
    return Task1::sumSelected(values, recursive);
}

void zeroSelected(std::vector<int>& values, const bool recursive) {
    Task1::zeroSelected(values, recursive);
}

int maxEvenIndex(const std::vector<int>& values, const bool recursive) {
    return Task2::maxEvenIndex(values, recursive);
}

namespace Iterative {
void input(std::istream& in, std::ostream& out, int* values, const std::size_t size) {
    Task3::Iterative::input(in, out, values, size);
}
} // namespace Iterative

namespace Recursive {
void input(std::istream& in, std::ostream& out, int* values, const std::size_t size) {
    Task3::Recursive::input(in, out, values, size);
}
} // namespace Recursive

namespace Dynamic {
int countPositive(const std::vector<double>& values, const bool recursive) {
    return Task4::countPositive(values, recursive);
}

int lastZeroIndex(const std::vector<double>& values, const bool recursive) {
    return Task4::lastZeroIndex(values, recursive);
}

double sumAfter(const std::vector<double>& values, const int index, const bool recursive) {
    return Task4::sumAfter(values, index, recursive);
}

void stablePartition(std::vector<double>& values, const bool recursive) {
    Task4::stablePartition(values, recursive);
}
} // namespace Dynamic

std::vector<int> createArray(const unsigned seed) {
    return Infrastructure::createArray(seed);
}

void printArray(std::ostream& out, const std::vector<int>& values) {
    UI::printArray(out, values);
}

void printArray(std::ostream& out, const std::vector<double>& values) {
    UI::printArray(out, values);
}

} // namespace Lb6
