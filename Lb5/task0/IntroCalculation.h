#pragma once

namespace Lb5::Task0 {

/// <summary>
/// Computes the introductory test formula:
/// calculate(x, y) = (x^2 + y) / 2.0.
/// Separates pure mathematical logic from console I/O for standalone unit testing.
/// </summary>
/// <param name="x">First argument.</param>
/// <param name="y">Second argument.</param>
/// <returns>Computed value (x * x + y) / 2.0.</returns>
double calculate(double x, double y);

} // namespace Lb5::Task0
