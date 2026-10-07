#pragma once

namespace SevenTeen {

    /// <summary>
    /// Computes the piecewise function with one variable for Task 1 (Variant 17).
    /// </summary>
    /// <param name="x">The input argument x.</param>
    /// <returns>Computed value of x^2 + 1 + f(x).</returns>
    double taskFirst(double x);

    /// <summary>
    /// Computes the branching expression with parameters for Task 2 (Variant 17).
    /// </summary>
    /// <param name="a">Parameter a.</param>
    /// <param name="b">Parameter b.</param>
    /// <param name="c">Parameter c.</param>
    /// <param name="x">Argument x.</param>
    /// <returns>The evaluated expression value.</returns>
    double taskSecond(double a, double b, double c, double x);

    /// <summary>
    /// Computes the chart/graph function value for Task 3 (Variant 17).
    /// </summary>
    /// <param name="x">Argument x.</param>
    /// <param name="R">Radius parameter R.</param>
    /// <returns>Value of y corresponding to the given x and R on the piecewise chart.</returns>
    double taskThird(double x, double R);

    /// <summary>
    /// Determines whether the point (x, y) falls inside or on the boundary of the shaded region for Task 4.
    /// </summary>
    /// <param name="x">The x-coordinate of the point.</param>
    /// <param name="y">The y-coordinate of the point.</param>
    /// <param name="R">The radius parameter R defining the circular boundaries.</param>
    /// <returns>True if the point lies inside or on the border of the target region; false otherwise.</returns>
    bool taskFourth(double x, double y, double R);

} // namespace SevenTeen
