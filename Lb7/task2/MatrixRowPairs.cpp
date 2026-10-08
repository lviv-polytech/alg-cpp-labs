#include "MatrixRowPairs.h"

#include <stdexcept>
#include <utility>

namespace Lb7::Task2 {

int findMinInRow(const Core::IntMatrix& matrix, const std::size_t row) {
    Core::validateRectangular(matrix);
    if (row >= matrix.size()) throw std::out_of_range("Row index is out of range.");
    int index = 0;
    for (std::size_t col = 1; col < matrix[row].size(); ++col)
        if (matrix[row][col] < matrix[row][index]) index = static_cast<int>(col);
    return index;
}

int findMaxInRow(const Core::IntMatrix& matrix, const std::size_t row) {
    Core::validateRectangular(matrix);
    if (row >= matrix.size()) throw std::out_of_range("Row index is out of range.");
    int index = 0;
    for (std::size_t col = 1; col < matrix[row].size(); ++col)
        if (matrix[row][col] > matrix[row][index]) index = static_cast<int>(col);
    return index;
}

void swapElements(Core::IntMatrix& matrix, const std::size_t rowA, const std::size_t colA,
                  const std::size_t rowB, const std::size_t colB) {
    Core::validateRectangular(matrix);
    if (rowA >= matrix.size() || rowB >= matrix.size() ||
        colA >= matrix.front().size() || colB >= matrix.front().size())
        throw std::out_of_range("Matrix coordinate is out of range.");
    std::swap(matrix[rowA][colA], matrix[rowB][colB]);
}

void processMatrixPairs(Core::IntMatrix& matrix) {
    Core::validateRectangular(matrix);
    for (std::size_t odd = 0; odd + 1 < matrix.size(); odd += 2) {
        const int minCol = findMinInRow(matrix, odd);
        const int maxCol = findMaxInRow(matrix, odd + 1);
        swapElements(matrix, odd, minCol, odd + 1, maxCol);
    }
}

} // namespace Lb7::Task2
