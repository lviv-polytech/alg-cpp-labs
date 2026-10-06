#pragma once

#include <iosfwd>
#include <vector>

namespace Lb7 {

using IntMatrix = std::vector<std::vector<int>>;
using RealMatrix = std::vector<std::vector<double>>;

bool selected(int value);
int countSelected(const IntMatrix& matrix, bool recursive);
int sumSelected(const IntMatrix& matrix, bool recursive);
void zeroSelected(IntMatrix& matrix, bool recursive);
bool rowLess(const std::vector<int>& left, const std::vector<int>& right);
/** Stable-sorts rows lexicographically by zero-based key columns 0, 1, and 3. */
void sortRows(IntMatrix& matrix, bool recursive);
void printMatrix(std::ostream& out, const IntMatrix& matrix);

IntMatrix createIntMatrix(std::size_t rows, std::size_t columns, unsigned seed);
int findMinInRow(const IntMatrix& matrix, std::size_t row);
int findMaxInRow(const IntMatrix& matrix, std::size_t row);
void swapElements(IntMatrix& matrix, std::size_t rowA, std::size_t colA,
                  std::size_t rowB, std::size_t colB);
void processMatrixPairs(IntMatrix& matrix);

/** Places the n largest matrix values on the main diagonal in nonincreasing order. */
void diagonalLargest(RealMatrix& matrix, bool recursive);
/** Returns the zero-based first row whose elements are all <=0, or -1 if none exists. */
int firstRowWithoutPositive(const RealMatrix& matrix, bool recursive);
RealMatrix createRealMatrix(std::size_t size, unsigned seed);
void printMatrix(std::ostream& out, const RealMatrix& matrix);

}  // namespace Lb7
