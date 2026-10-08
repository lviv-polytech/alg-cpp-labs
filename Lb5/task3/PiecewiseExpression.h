#pragma once

#include <optional>

namespace Lb5::Task3 {

    /// <summary>
    /// Computes the piecewise function helper(x):
    /// - For |x| &gt;= 1: helper(x) = (sin(x) + 1) / (1 + cos(x))
    ///   Returns std::nullopt at cosine singularity points (1 + cos(x) == 0).
    /// - For |x| &lt; 1: polynomial series expansion (5 terms):
    ///   1 + sum_{i=1}^{5} a_i, where a_i = a_{i-1} * x / ((2*i - 1)*(2*i)).
    /// </summary>
    /// <param name="x">Argument x.</param>
    /// <returns>Computed value, or std::nullopt if at a singularity.</returns>
    /// <exception cref="std::invalid_argument">Thrown if x is not finite.</exception>
    std::optional<double> helper(double x);

    /// <summary>
    /// Evaluates the nested expression:
    /// E(g) = helper(g^2 + 1) + helper(g + helper(1)) + 1.
    /// Returns std::nullopt if any subexpression encounters a singularity.
    /// </summary>
    /// <param name="g">Parameter g.</param>
    /// <returns>Evaluated value, or std::nullopt if undefined.</returns>
    std::optional<double> nestedExpression(double g);

} // namespace Lb5::Task3
