#pragma once

namespace Lb5::Task1 {

    /// <summary>
    /// Computes the rational helper function:
    /// h(x, y, z) = (x + y + z) / (x^2 + y^2 + z^2).
    /// </summary>
    /// <param name="x">First argument.</param>
    /// <param name="y">Second argument.</param>
    /// <param name="z">Third argument.</param>
    /// <returns>Computed value of h(x, y, z).</returns>
    double h(double x, double y, double z);

    /// <summary>
    /// Evaluates the compound expression with parameters a and b using helper function h:
    /// R = [h(a, b, 1) + h(1, a, b)] / [1 + h(a^2 + b^2, 1, 0)].
    /// </summary>
    /// <param name="a">Parameter a.</param>
    /// <param name="b">Parameter b.</param>
    /// <returns>Computed value R.</returns>
    double expression(double a, double b);

} // namespace Lb5::Task1
