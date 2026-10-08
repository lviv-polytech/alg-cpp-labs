#include "MatrixGenerator.h"

#include <random>
#include <stdexcept>

namespace Lb7::Infrastructure {

IntMatrix createIntMatrix(const std::size_t rows, const std::size_t columns, const unsigned seed) {
    if (rows == 0 || columns == 0) throw std::invalid_argument("Matrix dimensions must be positive.");
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> distribution(11, 64);
    IntMatrix matrix(rows, std::vector<int>(columns));
    for (auto& row : matrix) for (int& value : row) value = distribution(engine);
    return matrix;
}

RealMatrix createRealMatrix(const std::size_t size, const unsigned seed) {
    if (size == 0) throw std::invalid_argument("Matrix size must be positive.");
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> distribution(-1000, 1000);
    RealMatrix matrix(size, std::vector<double>(size));
    for (auto& row : matrix) for (double& value : row) value = distribution(engine) / 100.0;
    return matrix;
}

} // namespace Lb7::Infrastructure
