#include "Tasks.h"

#include "task1/MatrixFilterAndSort.h"
#include "task2/MatrixRowPairs.h"
#include "task3/MatrixDiagonal.h"
#include "Infrastructure/MatrixGenerator.h"
#include "UI/MatrixPrinter.h"

namespace Lb7 {

bool selected(const int value) {
    return Task1::selected(value);
}

int countSelected(const IntMatrix& matrix, const bool recursive) {
    return Task1::countSelected(matrix, recursive);
}

int sumSelected(const IntMatrix& matrix, const bool recursive) {
    return Task1::sumSelected(matrix, recursive);
}

void zeroSelected(IntMatrix& matrix, const bool recursive) {
    Task1::zeroSelected(matrix, recursive);
}

bool rowLess(const std::vector<int>& left, const std::vector<int>& right) {
    return Task1::rowLess(left, right);
}

void sortRows(IntMatrix& matrix, const bool recursive) {
    Task1::sortRows(matrix, recursive);
}

void printMatrix(std::ostream& out, const IntMatrix& matrix) {
    UI::printMatrix(out, matrix);
}

IntMatrix createIntMatrix(const std::size_t rows, const std::size_t columns, const unsigned seed) {
    return Infrastructure::createIntMatrix(rows, columns, seed);
}

int findMinInRow(const IntMatrix& matrix, const std::size_t row) {
    return Task2::findMinInRow(matrix, row);
}

int findMaxInRow(const IntMatrix& matrix, const std::size_t row) {
    return Task2::findMaxInRow(matrix, row);
}

void swapElements(IntMatrix& matrix, const std::size_t rowA, const std::size_t colA,
                  const std::size_t rowB, const std::size_t colB) {
    Task2::swapElements(matrix, rowA, colA, rowB, colB);
}

void processMatrixPairs(IntMatrix& matrix) {
    Task2::processMatrixPairs(matrix);
}

void diagonalLargest(RealMatrix& matrix, const bool recursive) {
    Task3::diagonalLargest(matrix, recursive);
}

int firstRowWithoutPositive(const RealMatrix& matrix, const bool recursive) {
    return Task3::firstRowWithoutPositive(matrix, recursive);
}

RealMatrix createRealMatrix(const std::size_t size, const unsigned seed) {
    return Infrastructure::createRealMatrix(size, seed);
}

void printMatrix(std::ostream& out, const RealMatrix& matrix) {
    UI::printMatrix(out, matrix);
}

} // namespace Lb7
