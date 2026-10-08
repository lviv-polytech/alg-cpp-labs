#pragma once

#include <array>

namespace Lb5::Task4 {

    /// <summary>
    /// Computes individual summand: sin(i) / (1 + cos(i)).
    /// </summary>
    /// <param name="i">Term index.</param>
    /// <returns>Computed summand value.</returns>
    double term(int i);

    /// <summary>
    /// Evaluates the finite series sum of logTerm(i) for i = 1 .. n
    /// using five computational techniques:
    /// 1. Iterative loop
    /// 2. Simple recursion ascending (from 1 to n)
    /// 3. Simple recursion descending (from n to 1)
    /// 4. Tail/accumulator recursion ascending
    /// 5. Tail/accumulator recursion descending
    /// </summary>
    /// <param name="n">Number of terms, must be in [1, 5000].</param>
    /// <returns>Array of 5 computed sum results.</returns>
    /// <exception cref="std::invalid_argument">Thrown if n &lt; 1 or n &gt; 5000.</exception>
    std::array<double, 5> recursiveSums(int n);

} // namespace Lb5::Task4
