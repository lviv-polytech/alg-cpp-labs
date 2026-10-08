#pragma once

#include <cstddef>
#include <vector>

namespace Lb7::Infrastructure {

using IntMatrix = std::vector<std::vector<int>>;
using RealMatrix = std::vector<std::vector<double>>;

/// <summary>
/// Generates an integer matrix filled with pseudorandom numbers from [11, 64].
/// </summary>
/// <param name="rows">Number of rows.</param>
/// <param name="columns">Number of columns.</param>
/// <param name="seed">Random generator seed.</param>
/// <returns>Populated IntMatrix.</returns>
/// <exception cref="std::invalid_argument">Thrown if rows == 0 or columns == 0.</exception>
IntMatrix createIntMatrix(std::size_t rows, std::size_t columns, unsigned seed);

/// <summary>
/// Generates a square real matrix with values from [-10.0, 10.0].
/// </summary>
/// <param name="size">Dimension size of the square matrix.</param>
/// <param name="seed">Random generator seed.</param>
/// <returns>Populated RealMatrix.</returns>
/// <exception cref="std::invalid_argument">Thrown if size == 0.</exception>
RealMatrix createRealMatrix(std::size_t size, unsigned seed);

} // namespace Lb7::Infrastructure
