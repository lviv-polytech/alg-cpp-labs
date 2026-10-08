#include "MatrixFilterAndSort.h"
#include "../../Common/RecursionTracker.h"

#include <iostream>
#include <stdexcept>
#include <utility>

namespace Lb7::Task1 {
namespace {

std::size_t cellCount(const Core::IntMatrix& matrix) {
    return matrix.size() * matrix.front().size();
}

int countSelectedAt(const Core::IntMatrix& matrix, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "countSelectedAt", level, level + 1);
    if (index == cellCount(matrix)) return 0;
    const auto cols = matrix.front().size();
    return (selected(matrix[index / cols][index % cols]) ? 1 : 0) + countSelectedAt(matrix, index + 1, level + 1);
}

int sumSelectedAt(const Core::IntMatrix& matrix, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "sumSelectedAt", level, level + 1);
    if (index == cellCount(matrix)) return 0;
    const auto cols = matrix.front().size();
    const int value = matrix[index / cols][index % cols];
    return (selected(value) ? value : 0) + sumSelectedAt(matrix, index + 1, level + 1);
}

void zeroSelectedAt(Core::IntMatrix& matrix, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "zeroSelectedAt", level, level + 1);
    if (index == cellCount(matrix)) return;
    const auto cols = matrix.front().size();
    int& value = matrix[index / cols][index % cols];
    if (selected(value)) value = 0;
    zeroSelectedAt(matrix, index + 1, level + 1);
}

void insertRow(Core::IntMatrix& matrix, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "insertRow", level, level + 1);
    if (index == 0) return;
    if (rowLess(matrix[index], matrix[index - 1])) {
        std::swap(matrix[index], matrix[index - 1]);
        insertRow(matrix, index - 1, level + 1);
    }
}

void sortRowsAt(Core::IntMatrix& matrix, const std::size_t index, const int level = 0) {
    Common::Recursion::printStep(std::cout, "sortRowsAt", level, level + 1);
    if (index == matrix.size()) return;
    insertRow(matrix, index, 0);
    sortRowsAt(matrix, index + 1, level + 1);
}

} // namespace

bool selected(const int value) {
    return value % 6 != 0;
}

int countSelected(const Core::IntMatrix& matrix, const bool recursive) {
    Core::validateRectangular(matrix);
    if (recursive) return countSelectedAt(matrix, 0);
    int count = 0;
    for (const auto& row : matrix) for (int value : row) count += selected(value);
    return count;
}

int sumSelected(const Core::IntMatrix& matrix, const bool recursive) {
    Core::validateRectangular(matrix);
    if (recursive) return sumSelectedAt(matrix, 0);
    int sum = 0;
    for (const auto& row : matrix) for (int value : row) if (selected(value)) sum += value;
    return sum;
}

void zeroSelected(Core::IntMatrix& matrix, const bool recursive) {
    Core::validateRectangular(matrix);
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

void sortRows(Core::IntMatrix& matrix, const bool recursive) {
    Core::validateRectangular(matrix);
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

} // namespace Lb7::Task1
