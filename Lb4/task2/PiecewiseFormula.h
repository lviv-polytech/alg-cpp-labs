#pragma once

#include <utility>
#include <vector>

namespace Lb4::Task2 {

    /// <summary>
    /// Evaluates the piecewise function f(x) = x^2 + 1 + B(x):
    /// - If x &lt; 4:  B(x) = 4*x^7 - x^5 + x^3 - 2
    /// - If 4 &lt;= x &lt; 7: B(x) = arctan((|x| + 1) / 2) + 8.3*x
    /// - If x &gt;= 7: B(x) = ln(|2*x + exp(4*x + 1)|)
    /// </summary>
    /// <param name="x">The input argument x.</param>
    /// <returns>Computed value f(x).</returns>
    double formula(double x);

    /// <summary>
    /// Tabulates the piecewise function f(x) over the interval [start, end] with given step.
    /// </summary>
    /// <param name="start">Start bound.</param>
    /// <param name="end">End bound.</param>
    /// <param name="step">Grid step.</param>
    /// <returns>Vector of (x, f(x)) grid point pairs.</returns>
    std::vector<std::pair<double, double>> tabulateFormula(double start, double end, double step);

} // namespace Lb4::Task2
