#include "Tasks.h"

#include <iomanip>
#include <ostream>
#include <random>
#include <stdexcept>
#include <utility>

namespace Lb7 {
namespace {
void validateRectangular(const IntMatrix& matrix) {
    if (matrix.empty() || matrix.front().empty()) throw std::invalid_argument("Matrix must be nonempty.");
    for (const auto& row : matrix)
        if (row.size() != matrix.front().size()) throw std::invalid_argument("Matrix must be rectangular.");
}
void validateSquare(const RealMatrix& matrix) {
    if (matrix.empty()) throw std::invalid_argument("Matrix must be nonempty.");
    for (const auto& row : matrix)
        if (row.size() != matrix.size()) throw std::invalid_argument("Matrix must be square.");
}
std::size_t cellCount(const IntMatrix& matrix) { return matrix.size() * matrix.front().size(); }
int countSelectedAt(const IntMatrix& matrix, const std::size_t index) {
    if (index == cellCount(matrix)) return 0;
    const auto cols = matrix.front().size();
    return (selected(matrix[index / cols][index % cols]) ? 1 : 0) + countSelectedAt(matrix, index + 1);
}
int sumSelectedAt(const IntMatrix& matrix, const std::size_t index) {
    if (index == cellCount(matrix)) return 0;
    const auto cols = matrix.front().size();
    const int value = matrix[index / cols][index % cols];
    return (selected(value) ? value : 0) + sumSelectedAt(matrix, index + 1);
}
void zeroSelectedAt(IntMatrix& matrix, const std::size_t index) {
    if (index == cellCount(matrix)) return;
    const auto cols = matrix.front().size();
    int& value = matrix[index / cols][index % cols];
    if (selected(value)) value = 0;
    zeroSelectedAt(matrix, index + 1);
}
void insertRow(IntMatrix& matrix, const std::size_t index) {
    if (index == 0) return;
    if (rowLess(matrix[index], matrix[index - 1])) {
        std::swap(matrix[index], matrix[index - 1]);
        insertRow(matrix, index - 1);
    }
}
void sortRowsAt(IntMatrix& matrix, const std::size_t index) {
    if (index == matrix.size()) return;
    insertRow(matrix, index);
    sortRowsAt(matrix, index + 1);
}
bool cellBefore(const RealMatrix& matrix, const std::size_t index, const std::size_t current,
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
std::size_t findLargestCellAt(const RealMatrix& matrix, const std::size_t diagonal,
                              const std::size_t index, const std::size_t best) {
    if (index == matrix.size() * matrix.size()) return best;
    const std::size_t nextBest = cellBefore(matrix, index, best, diagonal) ? index : best;
    return findLargestCellAt(matrix, diagonal, index + 1, nextBest);
}
void diagonalAt(RealMatrix& matrix, const std::size_t diagonal) {
    if (diagonal == matrix.size()) return;
    const std::size_t target = diagonal * matrix.size() + diagonal;
    const std::size_t largest = findLargestCellAt(matrix, diagonal, 0, target);
    std::swap(matrix[diagonal][diagonal],
              matrix[largest / matrix.size()][largest % matrix.size()]);
    diagonalAt(matrix, diagonal + 1);
}
bool rowHasPositiveAt(const RealMatrix& matrix, const std::size_t row, const std::size_t col) {
    if (col == matrix.size()) return false;
    if (matrix[row][col] > 0.0) return true;
    return rowHasPositiveAt(matrix, row, col + 1);
}
int firstRowAt(const RealMatrix& matrix, const std::size_t row) {
    if (row == matrix.size()) return -1;
    if (!rowHasPositiveAt(matrix, row, 0)) return static_cast<int>(row);
    return firstRowAt(matrix, row + 1);
}
}  // namespace

bool selected(const int value) { return value % 6 != 0; }

int countSelected(const IntMatrix& matrix, const bool recursive) {
    validateRectangular(matrix);
    if (recursive) return countSelectedAt(matrix, 0);
    int count = 0;
    for (const auto& row : matrix) for (int value : row) count += selected(value);
    return count;
}
int sumSelected(const IntMatrix& matrix, const bool recursive) {
    validateRectangular(matrix);
    if (recursive) return sumSelectedAt(matrix, 0);
    int sum = 0;
    for (const auto& row : matrix) for (int value : row) if (selected(value)) sum += value;
    return sum;
}
void zeroSelected(IntMatrix& matrix, const bool recursive) {
    validateRectangular(matrix);
    if (recursive) {
        zeroSelectedAt(matrix, 0);
        return;
    }
    for (auto& row : matrix) for (int& value : row) if (selected(value)) value = 0;
}
bool rowLess(const std::vector<int>& left, const std::vector<int>& right) {
    if (left.size() < 4 || right.size() < 4) throw std::invalid_argument("Rows require at least four columns.");
    for (const std::size_t col : {0U, 1U, 3U}) {
        if (left[col] != right[col]) return left[col] < right[col];
    }
    return false;
}
void sortRows(IntMatrix& matrix, const bool recursive) {
    validateRectangular(matrix);
    if (matrix.front().size() < 4) throw std::invalid_argument("Rows require at least four columns.");
    if (recursive) {
        sortRowsAt(matrix, 1);
        return;
    }
    for (std::size_t i = 1; i < matrix.size(); ++i) {
        std::size_t position = i;
        while (position > 0 && rowLess(matrix[position], matrix[position - 1])) {
            std::swap(matrix[position], matrix[position - 1]);
            --position;
        }
    }
}
void printMatrix(std::ostream& out, const IntMatrix& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) out << std::setw(4) << value;
        out << '\n';
    }
}

IntMatrix createIntMatrix(const std::size_t rows, const std::size_t columns, const unsigned seed) {
    if (rows == 0 || columns == 0) throw std::invalid_argument("Matrix dimensions must be positive.");
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> distribution(11, 64);
    IntMatrix matrix(rows, std::vector<int>(columns));
    for (auto& row : matrix) for (int& value : row) value = distribution(engine);
    return matrix;
}
int findMinInRow(const IntMatrix& matrix, const std::size_t row) {
    validateRectangular(matrix);
    if (row >= matrix.size()) throw std::out_of_range("Row index is out of range.");
    int index = 0;
    for (std::size_t col = 1; col < matrix[row].size(); ++col)
        if (matrix[row][col] < matrix[row][index]) index = static_cast<int>(col);
    return index;
}
int findMaxInRow(const IntMatrix& matrix, const std::size_t row) {
    validateRectangular(matrix);
    if (row >= matrix.size()) throw std::out_of_range("Row index is out of range.");
    int index = 0;
    for (std::size_t col = 1; col < matrix[row].size(); ++col)
        if (matrix[row][col] > matrix[row][index]) index = static_cast<int>(col);
    return index;
}
void swapElements(IntMatrix& matrix, const std::size_t rowA, const std::size_t colA,
                  const std::size_t rowB, const std::size_t colB) {
    validateRectangular(matrix);
    if (rowA >= matrix.size() || rowB >= matrix.size() ||
        colA >= matrix.front().size() || colB >= matrix.front().size())
        throw std::out_of_range("Matrix coordinate is out of range.");
    std::swap(matrix[rowA][colA], matrix[rowB][colB]);
}
void processMatrixPairs(IntMatrix& matrix) {
    validateRectangular(matrix);
    for (std::size_t odd = 0; odd + 1 < matrix.size(); odd += 2) {
        const int minCol = findMinInRow(matrix, odd);
        const int maxCol = findMaxInRow(matrix, odd + 1);
        swapElements(matrix, odd, minCol, odd + 1, maxCol);
    }
}

void diagonalLargest(RealMatrix& matrix, const bool recursive) {
    validateSquare(matrix);
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
int firstRowWithoutPositive(const RealMatrix& matrix, const bool recursive) {
    validateSquare(matrix);
    if (recursive) return firstRowAt(matrix, 0);
    for (std::size_t row = 0; row < matrix.size(); ++row) {
        bool hasPositive = false;
        for (double value : matrix[row]) hasPositive = hasPositive || value > 0.0;
        if (!hasPositive) return static_cast<int>(row);
    }
    return -1;
}
RealMatrix createRealMatrix(const std::size_t size, const unsigned seed) {
    if (size == 0) throw std::invalid_argument("Matrix size must be positive.");
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> distribution(-1000, 1000);
    RealMatrix matrix(size, std::vector<double>(size));
    for (auto& row : matrix) for (double& value : row) value = distribution(engine) / 100.0;
    return matrix;
}
void printMatrix(std::ostream& out, const RealMatrix& matrix) {
    out << std::fixed << std::setprecision(2);
    for (const auto& row : matrix) {
        for (double value : row) out << std::setw(8) << value;
        out << '\n';
    }
}
}  // namespace Lb7
