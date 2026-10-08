#pragma once

#include <cstddef>
#include <vector>

namespace Lb6::Task1 {

    constexpr std::size_t SELECTION_SIZE = 25;

    /// <summary>
    /// Holds the results of array selection processing: the number of matching elements
    /// and their cumulative sum.
    /// </summary>
    struct SelectionResult {
        int count;
        int sum;
    };

    /// <summary>
    /// Checks whether an array element satisfies the variant selection criterion:
    /// (value % 6 == 0) OR (index % 5 != 0).
    /// </summary>
    /// <param name="index">Zero-based element index.</param>
    /// <param name="value">Element value.</param>
    /// <returns>True if the condition is satisfied, false otherwise.</returns>
    bool isSelected(int index, int value);

    /// <summary>
    /// Counts elements in the array satisfying the selection criterion.
    /// Supports both iterative and recursive traversal.
    /// </summary>
    /// <param name="values">Vector of 25 integer values.</param>
    /// <param name="recursive">If true, uses recursive implementation; else iterative.</param>
    /// <returns>Count of selected elements.</returns>
    /// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
    int countSelected(const std::vector<int>& values, bool recursive);

    /// <summary>
    /// Computes the sum of elements satisfying the selection criterion.
    /// Supports both iterative and recursive traversal.
    /// </summary>
    /// <param name="values">Vector of 25 integer values.</param>
    /// <param name="recursive">If true, uses recursive implementation; else iterative.</param>
    /// <returns>Sum of matching elements.</returns>
    /// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
    int sumSelected(const std::vector<int>& values, bool recursive);

    /// <summary>
    /// Replaces all elements satisfying the selection criterion with zero in-place.
    /// Supports both iterative and recursive traversal.
    /// </summary>
    /// <param name="values">Vector of 25 integer values.</param>
    /// <param name="recursive">If true, uses recursive implementation; else iterative.</param>
    /// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
    void zeroSelected(std::vector<int>& values, bool recursive);

    /// <summary>
    /// Processes the array: counts and sums selected elements, then zeros them out.
    /// </summary>
    /// <param name="values">Vector of 25 integer values.</param>
    /// <param name="recursive">If true, uses recursive implementation; else iterative.</param>
    /// <returns>SelectionResult containing the count and sum before zeroing.</returns>
    /// <exception cref="std::invalid_argument">Thrown if values.size() != 25.</exception>
    SelectionResult processSelection(std::vector<int>& values, bool recursive);

} // namespace Lb6::Task1
