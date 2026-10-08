#pragma once

#include <cstddef>
#include <iosfwd>
#include <vector>

namespace Lb7 {

using IntMatrix = std::vector<std::vector<int>>;
using RealMatrix = std::vector<std::vector<double>>;

/// <summary>
/// Predicate checking if a value satisfies the selection criterion:
/// value is not divisible by 6 (value % 6 != 0).
/// </summary>
/// <param name="value">Cell value.</param>
/// <returns>True if value % 6 != 0, false otherwise.</returns>
bool selected(int value);

/// <summary>
/// Counts the number of cells in the rectangular matrix with value not divisible by 6.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <returns>Count of matching elements.</returns>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or jagged.</exception>
int countSelected(const IntMatrix& matrix, bool recursive);

/// <summary>
/// Computes the sum of all cells in the rectangular matrix with value not divisible by 6.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <returns>Sum of matching elements.</returns>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or jagged.</exception>
int sumSelected(const IntMatrix& matrix, bool recursive);

/// <summary>
/// Sets all cells whose values are not divisible by 6 to zero in-place.
/// </summary>
/// <param name="matrix">Rectangular integer matrix.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or jagged.</exception>
void zeroSelected(IntMatrix& matrix, bool recursive);

/// <summary>
/// Compares two matrix rows lexicographically by keys at column indices 0, 1, and 3.
/// </summary>
/// <param name="left">First row.</param>
/// <param name="right">Second row.</param>
/// <returns>True if left &lt; right by the specified columns.</returns>
/// <exception cref="std::invalid_argument">Thrown if either row has fewer than 4 elements.</exception>
bool rowLess(const std::vector<int>& left, const std::vector<int>& right);

/// <summary>
/// Stable-sorts rows of the matrix using insertion sort based on column keys {0, 1, 3}.
/// </summary>
/// <param name="matrix">Rectangular integer matrix with &gt;= 4 columns.</param>
/// <param name="recursive">True for recursive execution, false for iterative.</param>
/// <exception cref="std::invalid_argument">Thrown if matrix is jagged or columns &lt; 4.</exception>
void sortRows(IntMatrix& matrix, bool recursive);

/// <summary>
/// Formats and outputs an integer matrix to the stream.
/// </summary>
void printMatrix(std::ostream& out, const IntMatrix& matrix);

/// <summary>
/// Generates a rectangular integer matrix with values uniformly distributed in [11, 64].
/// </summary>
IntMatrix createIntMatrix(std::size_t rows, std::size_t columns, unsigned seed);

/// <summary>
/// Finds the column index of the minimum element in a specified row.
/// </summary>
int findMinInRow(const IntMatrix& matrix, std::size_t row);

/// <summary>
/// Finds the column index of the maximum element in a specified row.
/// </summary>
int findMaxInRow(const IntMatrix& matrix, std::size_t row);

/// <summary>
/// Swaps two matrix elements at coordinates (rowA, colA) and (rowB, colB).
/// </summary>
void swapElements(IntMatrix& matrix, std::size_t rowA, std::size_t colA,
                  std::size_t rowB, std::size_t colB);

/// <summary>
/// Processes adjacent pairs of rows (0 and 1, 2 and 3, etc.):
/// finds minimum in row 2k and maximum in row 2k+1 and swaps them.
/// </summary>
void processMatrixPairs(IntMatrix& matrix);

/// <summary>
/// Rearranges the square matrix so the n largest values are placed on the main diagonal
/// in descending order (matrix[0][0] &gt;= matrix[1][1] &gt;= ... &gt;= matrix[n-1][n-1]).
/// </summary>
void diagonalLargest(RealMatrix& matrix, bool recursive);

/// <summary>
/// Finds the index of the first row with no positive elements (all elements &lt;= 0.0), or -1.
/// </summary>
int firstRowWithoutPositive(const RealMatrix& matrix, bool recursive);

/// <summary>
/// Generates a square real matrix with values uniformly distributed in [-10.0, 10.0].
/// </summary>
RealMatrix createRealMatrix(std::size_t size, unsigned seed);

/// <summary>
/// Formats and outputs a real matrix to the stream.
/// </summary>
void printMatrix(std::ostream& out, const RealMatrix& matrix);

}  // namespace Lb7
