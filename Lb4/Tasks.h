#pragma once

#include <array>
#include <optional>
#include <utility>
#include <vector>

namespace Lb4 {

/// <summary>
/// Computes an individual series term:
/// a_i = sin(i) / (1 + cos(i)) where i is an integer angle in radians.
/// </summary>
/// <param name="i">The 1-based integer index.</param>
/// <returns>Computed summand value.</returns>
double term(int i);

/// <summary>
/// Evaluates the finite series sum S_n = sum_{i=1}^{n} [sin(i) / (1 + cos(i))]
/// using four different loop approaches:
/// while, do-while, ascending for, and descending for.
/// </summary>
/// <param name="n">Number of terms, must be &gt;= 1.</param>
/// <returns>Array of 4 evaluated sums.</returns>
/// <exception cref="std::invalid_argument">Thrown if n &lt; 1.</exception>
std::array<double, 4> cycleSums(int n);

/// <summary>
/// Evaluates the piecewise function f(x) = x^2 + 1 + B(x):
/// - For x &lt; 4:  B(x) = 4*x^7 - x^5 + x^3 - 2
/// - For 4 &lt;= x &lt; 7: B(x) = arctan((|x| + 1) / 2) + 8.3*x
/// - For x &gt;= 7: B(x) = ln(|2*x + exp(4*x + 1)|)
/// </summary>
/// <param name="x">The input argument x.</param>
/// <returns>Evaluated function value f(x).</returns>
double formula(double x);

/// <summary>
/// Tabulates the piecewise function f(x) over [start, end] with step.
/// </summary>
/// <param name="start">Lower bound.</param>
/// <param name="end">Upper bound.</param>
/// <param name="step">Discretization step.</param>
/// <returns>Vector of (x, f(x)) coordinates.</returns>
std::vector<std::pair<double, double>> tabulateFormula(double start, double end, double step);

/// <summary>
/// Evaluates the parametric branching function with parameters a, b, c:
/// - If x + 10 &lt; 0 and b != 0: returns a*x^2 - c*x + b
/// - If x + 10 &gt; 0 and b == 0: returns (x - a) / (x - c); returns nullopt if x == c
/// - Fallback: returns -x / (a - c); returns nullopt if a == c
/// </summary>
/// <param name="a">Parameter a.</param>
/// <param name="b">Parameter b.</param>
/// <param name="c">Parameter c.</param>
/// <param name="x">Argument x.</param>
/// <returns>Evaluated value or std::nullopt if division by zero occurs.</returns>
std::optional<double> parametric(double a, double b, double c, double x);

/// <summary>
/// Tabulates the parametric function over [start, end] with step.
/// </summary>
std::vector<std::pair<double, std::optional<double>>> tabulateParametric(
    double a, double b, double c, double start, double end, double step);

/// <summary>
/// Evaluates the piecewise geometric chart function:
/// - If x &lt; -1 - R: returns 1.0
/// - If -1 - R &lt;= x &lt;= -1: returns -sqrt(max(0, R^2 - (x+1)^2))
/// - If -1 &lt; x &lt;= 2: returns -R
/// - If x &gt; 2: returns R*(x - 4) / 2
/// </summary>
/// <param name="radius">Geometric radius parameter R &gt; 0.</param>
/// <param name="x">Coordinate x.</param>
/// <returns>Evaluated chart ordinate y.</returns>
/// <exception cref="std::invalid_argument">Thrown if radius &lt;= 0 or not finite.</exception>
double graphFunction(double radius, double x);

/// <summary>
/// Tabulates the geometric chart function over [start, end] with step.
/// </summary>
std::vector<std::pair<double, double>> tabulateGraph(
    double radius, double start, double end, double step);

/// <summary>
/// Evaluates the double nested sum:
/// S = sum_{k=1}^{20} sqrt(sin^2(k) + |sum_{i=1}^{k} cos(i + k)|)
/// using 4 nested loop variations.
/// </summary>
/// <returns>Array of 4 evaluated sum values.</returns>
std::array<double, 4> nestedSums();

/// <summary>
/// Result of the ln(x) Taylor approximation containing the computed sum and number of terms.
/// </summary>
struct TaylorResult {
    double sum;
    int terms;
};

/// <summary>
/// Evaluates ln(x) via Taylor series for x &gt; 0.5:
/// ln(x) = sum_{n=1}^{infinity} (1/n) * ((x - 1) / x)^n
/// using dynamic recurrence until term magnitude falls below epsilon.
/// </summary>
/// <param name="x">Argument x (must be &gt; 0.5 for series convergence).</param>
/// <param name="epsilon">Error threshold epsilon &gt; 0.</param>
/// <returns>TaylorResult or std::nullopt if x &lt;= 0.5.</returns>
std::optional<TaylorResult> taylorLog(double x, double epsilon);

/// <summary>
/// Tabulates the Taylor approximation of ln(x) over [start, end] with step.
/// </summary>
std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    double start, double end, double step, double epsilon);

} // namespace Lb4
