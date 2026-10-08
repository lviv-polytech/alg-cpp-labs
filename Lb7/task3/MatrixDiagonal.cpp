#include "MatrixDiagonal.h"
#include "../../Common/RecursionTracker.h"

#include <iostream>
#include <utility>

namespace Lb7::Task3 {
namespace {

bool cellBefore(const Core::RealMatrix& matrix, const std::size_t index, const std::size_t current,
                const std::size_t diagonal) {
    const std::size_t n = matrix.size();
    if (index == current) return false;
    const std::size_t row = index / n;
    const std::size_t col = index % n;
    if (row == col && row < diagonal) return false;
    const std::size_t currentRow = current / n;
    const std::size_t currentCol = current % n;
    return matrix[row][col] > matrix[currentRow][currentCol];
}

std::size_t findLargestCellAt(const Core::RealMatrix& matrix, const std::size_t diagonal,
                              const std::size_t index, const std::size_t best, const int level = 0) {
    Common::Recursion::printStep(std::cout, "findLargestCellAt", level, level + 1);
    if (index == matrix.size() * matrix.size()) return best;
    const std::size_t nextBest = cellBefore(matrix, index, best, diagonal) ? index : best;
    return findLargestCellAt(matrix, diagonal, index + 1, nextBest, level + 1);
}

void diagonalAt(Core::RealMatrix& matrix, const std::size_t diagonal, const int level = 0) {
    Common::Recursion::printStep(std::cout, "diagonalAt", level, level + 1);
    if (diagonal == matrix.size()) return;
    const std::size_t target = diagonal * matrix.size() + diagonal;
    const std::size_t largest = findLargestCellAt(matrix, diagonal, 0, target, 0);
    std::swap(matrix[diagonal][diagonal],
              matrix[largest / matrix.size()][largest % matrix.size()]);
    diagonalAt(matrix, diagonal + 1, level + 1);
}

bool rowHasPositiveAt(const Core::RealMatrix& matrix, const std::size_t row, const std::size_t col, const int level = 0) {
    Common::Recursion::printStep(std::cout, "rowHasPositiveAt", level, level + 1);
    if (col == matrix.size()) return false;
    if (matrix[row][col] > 0.0) return true;
    return rowHasPositiveAt(matrix, row, col + 1, level + 1);
}

int firstRowAt(const Core::RealMatrix& matrix, const std::size_t row, const int level = 0) {
    Common::Recursion::printStep(std::cout, "firstRowAt", level, level + 1);
    if (row == matrix.size()) return -1;
    if (!rowHasPositiveAt(matrix, row, 0, 0)) return static_cast<int>(row);
    return firstRowAt(matrix, row + 1, level + 1);
}

} // namespace

void diagonalLargest(Core::RealMatrix& matrix, const bool recursive) {
    Core::validateSquare(matrix);
    if (recursive) {
        diagonalAt(matrix, 0);
        return;
    }
    const std::size_t n = matrix.size();
    for (std::size_t diagonal = 0; diagonal < n; ++diagonal) {
        std::size_t bestRow = diagonal, bestCol = diagonal;
        for (std::size_t row = 0; row < n; ++row) {
            for (std::size_t col = 0; col < n; ++col) {
                if (row == col && row < diagonal) continue;
                if (matrix[row][col] > matrix[bestRow][bestCol]) {
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
        std::swap(matrix[diagonal][diagonal], matrix[bestRow][bestCol]);
    }
}

int firstRowWithoutPositive(const Core::RealMatrix& matrix, const bool recursive) {
    Core::validateSquare(matrix);
    if (recursive) return firstRowAt(matrix, 0);
    for (std::size_t row = 0; row < matrix.size(); ++row) {
        bool hasPositive = false;
        for (double value : matrix[row]) hasPositive = hasPositive || value > 0.0;
        if (!hasPositive) return static_cast<int>(row);
    }
    return -1;
}

} // namespace Lb7::Task3
