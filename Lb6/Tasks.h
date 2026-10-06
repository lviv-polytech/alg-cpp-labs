#pragma once

#include <cstddef>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Lb6 {

constexpr std::size_t SELECTION_SIZE = 25;
struct SelectionResult {
    int count;
    int sum;
};
bool isSelected(int index, int value);
int countSelected(const std::vector<int>& values, bool recursive);
int sumSelected(const std::vector<int>& values, bool recursive);
void zeroSelected(std::vector<int>& values, bool recursive);
SelectionResult processSelection(std::vector<int>& values, bool recursive);
int maxEvenIndex(const std::vector<int>& values, bool recursive);

namespace Iterative {
void input(std::istream& in, std::ostream& out, int* values, std::size_t size);
void input(std::istream& in, std::ostream& out, std::string* values, std::size_t size);
}
namespace Recursive {
void input(std::istream& in, std::ostream& out, int* values, std::size_t size);
void input(std::istream& in, std::ostream& out, std::string* values, std::size_t size);
}

template <typename T>
void inputTemplate(std::istream& in, std::ostream& out, T* values, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        out << "a[" << i << "] = ";
        if (!(in >> values[i])) throw std::runtime_error("Failed to read array element.");
    }
}

template <typename T>
void inputTemplateRecursive(std::istream& in, std::ostream& out, T* values,
                            std::size_t size, std::size_t index = 0) {
    if (index >= size) return;
    out << "a[" << index << "] = ";
    if (!(in >> values[index])) throw std::runtime_error("Failed to read array element.");
    inputTemplateRecursive(in, out, values, size, index + 1);
}

namespace Dynamic {
int countPositive(const std::vector<double>& values, bool recursive);
int lastZeroIndex(const std::vector<double>& values, bool recursive);
double sumAfter(const std::vector<double>& values, int index, bool recursive);
void stablePartition(std::vector<double>& values, bool recursive);
}

std::vector<int> createArray(unsigned seed);
void printArray(std::ostream& out, const std::vector<int>& values);
void printArray(std::ostream& out, const std::vector<double>& values);

}  // namespace Lb6
