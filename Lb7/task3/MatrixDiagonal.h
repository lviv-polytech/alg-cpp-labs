#pragma once

#include "../Core/MatrixTypes.h"

namespace Lb7::Task3 {

using Core::RealMatrix;

/// <summary>
/// Reorders matrix elements such that the n largest values of the square matrix
/// are placed along the main diagonal in descending (nonincreasing) order:
/// matrix[0][0] &gt;= matrix[1][1] &gt;= ... &gt;= matrix[n-1][n-1].
/// Supports both iterative and recursive implementations.
/// </summary>
/// <param name="matrix">Square real matrix (n x n).</param>
/// <param name="recursive">If true, recursive rearrangement is executed.</param>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or non-square.</exception>
void diagonalLargest(RealMatrix& matrix, bool recursive);

/// <summary>
/// Finds the index of the first row whose elements are all non-positive (element &lt;= 0.0).
/// Returns -1 if every row contains at least one positive value.
/// Supports both iterative and recursive implementations.
/// </summary>
/// <param name="matrix">Square real matrix (n x n).</param>
/// <param name="recursive">If true, recursive search is executed.</param>
/// <returns>Zero-based index of first non-positive row, or -1.</returns>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or non-square.</exception>
int firstRowWithoutPositive(const RealMatrix& matrix, bool recursive);

} // namespace Lb7::Task3
