#pragma once

#include <vector>

namespace Lb6::Task2 {

    /// <summary>
    /// Finds the zero-based index of the maximum even element in the vector.
    /// If multiple elements share the maximum even value, returns the index of the first occurrence.
    /// Returns -1 if no even elements exist.
    /// Supports both iterative and recursive implementations.
    /// </summary>
    /// <param name="values">Vector of integer numbers.</param>
    /// <param name="recursive">If true, executes recursive search; else iterative.</param>
    /// <returns>Index of maximum even element, or -1.</returns>
    int maxEvenIndex(const std::vector<int>& values, bool recursive);

} // namespace Lb6::Task2
