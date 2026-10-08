#pragma once

#include <vector>

namespace Lb6::Task4 {

    /// <summary>
    /// Counts positive elements (value &gt; 0.0) in the dynamic array.
    /// Supports iterative and recursive modes.
    /// </summary>
    /// <param name="values">Vector of floating point numbers.</param>
    /// <param name="recursive">If true, recursive traversal is used.</param>
    /// <returns>Count of positive values.</returns>
    int countPositive(const std::vector<double>& values, bool recursive);

    /// <summary>
    /// Finds the zero-based index of the last zero-valued element (value == 0.0).
    /// Returns -1 if no zero exists in the array.
    /// </summary>
    /// <param name="values">Vector of floating point numbers.</param>
    /// <param name="recursive">If true, recursive traversal is used.</param>
    /// <returns>Last zero index, or -1.</returns>
    int lastZeroIndex(const std::vector<double>& values, bool recursive);

    /// <summary>
    /// Calculates the sum of elements located after the specified index position.
    /// </summary>
    /// <param name="values">Vector of floating point numbers.</param>
    /// <param name="index">Pivot index (must be in [-1, size - 1]).</param>
    /// <param name="recursive">If true, recursive summation is used.</param>
    /// <returns>Cumulative sum of elements with indices &gt; index.</returns>
    /// <exception cref="std::out_of_range">Thrown if index is out of valid bounds.</exception>
    double sumAfter(const std::vector<double>& values, int index, bool recursive);

    /// <summary>
    /// Performs an in-place stable partition of the vector:
    /// elements strictly less than 2.0 (equivalent to trunc(x) &lt;= 1 for positive values)
    /// precede elements greater than or equal to 2.0, preserving relative order of each group.
    /// </summary>
    /// <param name="values">Vector to partition in place.</param>
    /// <param name="recursive">If true, recursive stable partition is used.</param>
    void stablePartition(std::vector<double>& values, bool recursive);

} // namespace Lb6::Task4
