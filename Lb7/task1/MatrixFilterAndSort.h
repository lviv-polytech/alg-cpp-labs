#pragma once

#include "../Core/MatrixTypes.h"
#include <vector>

namespace Lb7::Task1 {

using Core::IntMatrix;

/// <summary>
/// Predicate checking if a matrix element satisfies the selection criterion:
/// value is not divisible by 6 (value % 6 != 0).
/// </summary>
/// <param name="value">Matrix cell value.</param>
/// <returns>True if value % 6 != 0, false otherwise.</returns>
bool selected(int value);

/// <summary>
/// Counts the number of elements in the rectangular matrix not divisible by 6.
/// Supports iterative and recursive traversals.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="recursive">If true, recursive counting is executed.</param>
/// <returns>Count of selected elements.</returns>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or non-rectangular.</exception>
int countSelected(const IntMatrix& matrix, bool recursive);

/// <summary>
/// Computes the sum of elements not divisible by 6 in the rectangular matrix.
/// Supports iterative and recursive traversals.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="recursive">If true, recursive summation is executed.</param>
/// <returns>Sum of selected elements.</returns>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or non-rectangular.</exception>
int sumSelected(const IntMatrix& matrix, bool recursive);

/// <summary>
/// Replaces all elements not divisible by 6 with 0 in-place.
/// Supports iterative and recursive traversals.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="recursive">If true, recursive replacement is executed.</param>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or non-rectangular.</exception>
void zeroSelected(IntMatrix& matrix, bool recursive);

/// <summary>
/// Compares two matrix rows lexicographically by keys at zero-based column indices: 0, 1, and 3.
/// </summary>
/// <param name="left">First row.</param>
/// <param name="right">Second row.</param>
/// <returns>True if left &lt; right under the compound key, false otherwise.</returns>
/// <exception cref="std::invalid_argument">Thrown if either row has fewer than 4 elements.</exception>
bool rowLess(const std::vector<int>& left, const std::vector<int>& right);

/// <summary>
/// Stable-sorts the rows of the matrix using insertion sort based on rowLess ordering.
/// Supports iterative and recursive sort algorithms.
/// </summary>
/// <param name="matrix">Rectangular integer matrix with at least 4 columns.</param>
/// <param name="recursive">If true, recursive insertion sort is executed.</param>
/// <exception cref="std::invalid_argument">Thrown if matrix is invalid or columns &lt; 4.</exception>
void sortRows(IntMatrix& matrix, bool recursive);

} // namespace Lb7::Task1
