#pragma once

#include <stdexcept>
#include <vector>

namespace Lb7::Core {

using IntMatrix = std::vector<std::vector<int>>;
using RealMatrix = std::vector<std::vector<double>>;

/// <summary>
/// Validates that an integer matrix is non-empty and rectangular.
/// </summary>
/// <param name="matrix">Matrix to validate.</param>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or jagged.</exception>
inline void validateRectangular(const IntMatrix& matrix) {
    if (matrix.empty() || matrix.front().empty()) {
        throw std::invalid_argument("Matrix must be nonempty.");
    }
    for (const auto& row : matrix) {
        if (row.size() != matrix.front().size()) {
            throw std::invalid_argument("Matrix must be rectangular.");
        }
    }
}

/// <summary>
/// Validates that a floating-point matrix is non-empty and square (N x N).
/// </summary>
/// <param name="matrix">Matrix to validate.</param>
/// <exception cref="std::invalid_argument">Thrown if matrix is empty or non-square.</exception>
inline void validateSquare(const RealMatrix& matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("Matrix must be nonempty.");
    }
    for (const auto& row : matrix) {
        if (row.size() != matrix.size()) {
            throw std::invalid_argument("Matrix must be square.");
        }
    }
}

} // namespace Lb7::Core
