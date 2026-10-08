#pragma once

#include "../Core/MatrixTypes.h"
#include <cstddef>

namespace Lb7::Task2 {

using Core::IntMatrix;

/// <summary>
/// Finds the column index of the minimum element in the specified row of the matrix.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="row">Zero-based row index.</param>
/// <returns>Column index of the minimum value.</returns>
/// <exception cref="std::out_of_range">Thrown if row index is out of bounds.</exception>
int findMinInRow(const IntMatrix& matrix, std::size_t row);

/// <summary>
/// Finds the column index of the maximum element in the specified row of the matrix.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="row">Zero-based row index.</param>
/// <returns>Column index of the maximum value.</returns>
/// <exception cref="std::out_of_range">Thrown if row index is out of bounds.</exception>
int findMaxInRow(const IntMatrix& matrix, std::size_t row);

/// <summary>
/// Swaps two elements in the matrix located at (rowA, colA) and (rowB, colB).
/// </summary>
/// <param name="matrix">Target matrix.</param>
/// <param name="rowA">Row index of first cell.</param>
/// <param name="colA">Column index of first cell.</param>
/// <param name="rowB">Row index of second cell.</param>
/// <param name="colB">Column index of second cell.</param>
/// <exception cref="std::out_of_range">Thrown if any coordinate is out of bounds.</exception>
void swapElements(IntMatrix& matrix, std::size_t rowA, std::size_t colA,
                  std::size_t rowB, std::size_t colB);

/// <summary>
/// Processes adjacent pairs of rows (0 and 1, 2 and 3, etc.):
/// in row 2k finds the minimum element and in row 2k+1 finds the maximum element,
/// then swaps them.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
void processMatrixPairs(IntMatrix& matrix);

} // namespace Lb7::Task2
