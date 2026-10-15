#pragma once

#include <cstddef>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "task1/ArraySelection.h"

namespace Lb6 {

constexpr std::size_t SELECTION_SIZE = 25;

/// <summary>
/// Structure storing results of array selection processing: matching element count and sum.
/// </summary>
struct SelectionResult {
    int count;
    int sum;
};

/// <summary>
/// Predicate checking if element satisfies variant criterion:
/// (value % 6 == 0) || (index % 5 != 0).
/// </summary>
/// <param name="index">Zero-based element index.</param>
/// <param name="value">Element value.</param>
/// <returns>True if selected, false otherwise.</returns>
bool isSelected(int index, int value);

/// <summary>
/// Counts elements matching the selection criterion in an array of 25 elements.
/// </summary>
/// <param name="values">Vector of 25 integers.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <returns>Count of matching elements.</returns>
/// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
int countSelected(const std::vector<int>& values, bool recursive);

/// <summary>
/// Computes sum of elements matching the selection criterion in an array of 25 elements.
/// </summary>
/// <param name="values">Vector of 25 integers.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <returns>Sum of matching elements.</returns>
/// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
int sumSelected(const std::vector<int>& values, bool recursive);

/// <summary>
/// Sets elements matching the selection criterion to zero in-place.
/// </summary>
/// <param name="values">Vector of 25 integers.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
void zeroSelected(std::vector<int>& values, bool recursive);

/// <summary>
/// Counts and sums selected elements, then zeros them out in the array.
/// </summary>
/// <param name="values">Vector of 25 integers.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <returns>SelectionResult with count and sum.</returns>
/// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
SelectionResult processSelection(std::vector<int>& values, bool recursive);

/// <summary>
/// Finds the index of the largest even element in the vector, or -1 if none found.
/// </summary>
/// <param name="values">Vector of integers.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <returns>Index of largest even value or -1.</returns>
int maxEvenIndex(const std::vector<int>& values, bool recursive);

namespace Iterative {
    /// <summary>
    /// Reads an array of integers iteratively from input stream.
    /// </summary>
    void input(std::istream& in, std::ostream& out, int* values, std::size_t size);
}

namespace Recursive {
    /// <summary>
    /// Reads an array of integers recursively from input stream.
    /// </summary>
    void input(std::istream& in, std::ostream& out, int* values, std::size_t size);
}

/// <summary>
/// Generic template function for reading array elements iteratively.
/// </summary>
template <typename T>
void inputTemplate(std::istream& in, std::ostream& out, T* values, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        out << "a[" << i << "] = ";
        if (!(in >> values[i])) throw std::runtime_error("Failed to read array element.");
    }
}

/// <summary>
/// Generic template function for reading array elements recursively.
/// </summary>
template <typename T>
void inputTemplateRecursive(std::istream& in, std::ostream& out, T* values,
                            std::size_t size, std::size_t index = 0) {
    if (index >= size) return;
    out << "a[" << index << "] = ";
    if (!(in >> values[index])) throw std::runtime_error("Failed to read array element.");
    inputTemplateRecursive(in, out, values, size, index + 1);
}

namespace Dynamic {
    /// <summary>
    /// Counts positive elements (x &gt; 0.0) in the dynamic array.
    /// </summary>
    int countPositive(const std::vector<double>& values, bool recursive);

    /// <summary>
    /// Finds index of the last zero-valued element, or -1 if none found.
    /// </summary>
    int lastZeroIndex(const std::vector<double>& values, bool recursive);

    /// <summary>
    /// Computes sum of elements after the specified index position.
    /// </summary>
    double sumAfter(const std::vector<double>& values, int index, bool recursive);

    /// <summary>
    /// Stable partitions dynamic array so that elements &lt; 2.0 precede elements &gt;= 2.0.
    /// </summary>
    void stablePartition(std::vector<double>& values, bool recursive);
}

/// <summary>
/// Generates a random array of 25 elements with uniform distribution in [4, 73].
/// </summary>
std::vector<int> createArray(unsigned seed);

/// <summary>
/// Formats and outputs an integer vector.
/// </summary>
void printArray(std::ostream& out, const std::vector<int>& values);

/// <summary>
/// Formats and outputs a floating point vector.
/// </summary>
void printArray(std::ostream& out, const std::vector<double>& values);

}  // namespace Lb6
