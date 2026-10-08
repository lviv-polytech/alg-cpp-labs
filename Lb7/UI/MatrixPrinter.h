#pragma once

#include <ostream>
#include <vector>

namespace Lb7::UI {

using IntMatrix = std::vector<std::vector<int>>;
using RealMatrix = std::vector<std::vector<double>>;

/// <summary>
/// Formats and prints an integer matrix to the output stream.
/// </summary>
/// <param name="out">Output stream.</param>
/// <param name="matrix">Integer matrix.</param>
void printMatrix(std::ostream& out, const IntMatrix& matrix);

/// <summary>
/// Formats and prints a real matrix with fixed 2-decimal precision.
/// </summary>
/// <param name="out">Output stream.</param>
/// <param name="matrix">Real matrix.</param>
void printMatrix(std::ostream& out, const RealMatrix& matrix);

} // namespace Lb7::UI
