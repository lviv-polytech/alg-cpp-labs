#pragma once

#include <optional>
#include <utility>
#include <vector>

namespace Lb4::Task3 {

    /// <summary>
    /// Evaluates the branching function with parameters a, b, c and argument x:
    /// - If x + 10 &lt; 0 and b != 0: returns a*x^2 - c*x + b
    /// - If x + 10 &gt; 0 and b == 0: returns (x - a) / (x - c); returns nullopt if x == c (division by zero)
    /// - Fallback: returns -x / (a - c); returns nullopt if a == c (division by zero)
    /// </summary>
    /// <param name="a">Parameter a.</param>
    /// <param name="b">Parameter b.</param>
    /// <param name="c">Parameter c.</param>
    /// <param name="x">Argument x.</param>
    /// <returns>Computed value, or std::nullopt if undefined.</returns>
    std::optional<double> parametric(double a, double b, double c, double x);

    /// <summary>
    /// Tabulates the parametric function over interval [start, end] with step.
    /// </summary>
    /// <param name="a">Parameter a.</param>
    /// <param name="b">Parameter b.</param>
    /// <param name="c">Parameter c.</param>
    /// <param name="start">Start bound.</param>
    /// <param name="end">End bound.</param>
    /// <param name="step">Grid step.</param>
    /// <returns>Vector of pairs (x, optional result).</returns>
    std::vector<std::pair<double, std::optional<double>>> tabulateParametric(
        double a, double b, double c, double start, double end, double step);

} // namespace Lb4::Task3
