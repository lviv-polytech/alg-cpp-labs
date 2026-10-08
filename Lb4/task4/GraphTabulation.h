#pragma once

#include <utility>
#include <vector>

namespace Lb4::Task4 {

    /// <summary>
    /// Computes the piecewise function representing the geometric chart:
    /// - If x &lt; -1 - R: returns 1.0
    /// - If -1 - R &lt;= x &lt;= -1: returns -sqrt(max(0, R^2 - (x+1)^2)) (circular arc)
    /// - If -1 &lt; x &lt;= 2: returns -R (horizontal line)
    /// - If x &gt; 2: returns R*(x - 4) / 2 (slanted line passing through (4, 0))
    /// </summary>
    /// <param name="radius">Radius parameter R, must be positive and finite.</param>
    /// <param name="x">The argument x.</param>
    /// <returns>Evaluated chart ordinate y.</returns>
    /// <exception cref="std::invalid_argument">Thrown if radius is non-positive or non-finite.</exception>
    double graphFunction(double radius, double x);

    /// <summary>
    /// Tabulates the chart function over the interval [start, end] with step.
    /// </summary>
    /// <param name="radius">Radius parameter R.</param>
    /// <param name="start">Start bound.</param>
    /// <param name="end">End bound.</param>
    /// <param name="step">Grid step.</param>
    /// <returns>Vector of (x, y) pairs.</returns>
    std::vector<std::pair<double, double>> tabulateGraph(
        double radius, double start, double end, double step);

} // namespace Lb4::Task4
