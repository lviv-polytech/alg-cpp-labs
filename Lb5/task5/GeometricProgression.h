#pragma once

namespace Lb5::Task5 {

    /// <summary>
    /// Result structure for geometric progression calculations.
    /// Contains the n-th term, sum of first n terms, and recursion stack depths.
    /// </summary>
    struct GeometricResult {
        double term;
        double sum;
        int termDepth;
        int sumDepth;
    };

    /// <summary>
    /// Computes the n-th term and sum of first n terms of a geometric sequence:
    /// b_n = b_1 * q^{n-1}
    /// S_n = sum_{i=1}^{n} b_i
    /// recursively, while tracking the maximum call depth reached.
    /// </summary>
    /// <param name="first">First term b_1.</param>
    /// <param name="ratio">Common ratio q.</param>
    /// <param name="n">Number of terms (must be in [1, 1000]).</param>
    /// <returns>GeometricResult containing term, sum, and recursion depths.</returns>
    /// <exception cref="std::invalid_argument">Thrown if n &lt; 1 or n &gt; 1000.</exception>
    GeometricResult geometric(double first, double ratio, int n);

} // namespace Lb5::Task5
