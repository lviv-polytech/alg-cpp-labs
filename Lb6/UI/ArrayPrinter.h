#pragma once

#include <ostream>
#include <vector>

namespace Lb6::UI {

    /// <summary>
    /// Formats and prints an integer vector to the output stream.
    /// </summary>
    /// <param name="out">Output stream.</param>
    /// <param name="values">Vector of integers.</param>
    void printArray(std::ostream& out, const std::vector<int>& values);

    /// <summary>
    /// Formats and prints a double vector with fixed 2-decimal precision.
    /// </summary>
    /// <param name="out">Output stream.</param>
    /// <param name="values">Vector of floating point numbers.</param>
    void printArray(std::ostream& out, const std::vector<double>& values);

} // namespace Lb6::UI
