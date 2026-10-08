#pragma once

#include <array>

namespace Lb4::Task1 {

    /// <summary>
    /// Computes an individual series term:
    /// a_i = sin(i) / (1 + cos(i)) where i is an integer radian angle.
    /// </summary>
    /// <param name="i">The 1-based term index.</param>
    /// <returns>Computed summand value.</returns>
    double term(int i);

    /// <summary>
    /// Evaluates the finite sum S_n = sum_{i=1}^{n} [sin(i) / (1 + cos(i))]
    /// using four distinct loop constructs:
    /// 1. while loop
    /// 2. do-while loop
    /// 3. ascending for loop (i = 1 .. n)
    /// 4. descending for loop (i = n .. 1)
    /// </summary>
    /// <param name="n">Number of terms to sum, must be at least 1.</param>
    /// <returns>Array of 4 evaluated sums corresponding to each loop technique.</returns>
    /// <exception cref="std::invalid_argument">Thrown if n &lt; 1.</exception>
    std::array<double, 4> cycleSums(int n);

} // namespace Lb4::Task1
