#pragma once

#include <array>
#include <optional>
#include <utility>
#include <vector>

namespace Lb5 {

/// <summary>
/// Introductory calculation for Task 5.0:
/// calculate(x, y) = (x^2 + y) / 2.0.
/// </summary>
/// <param name="x">First argument.</param>
/// <param name="y">Second argument.</param>
/// <returns>Computed value.</returns>
double calculate(double x, double y);

/// <summary>
/// Rational function h(x, y, z) = (x + y + z) / (x^2 + y^2 + z^2).
/// </summary>
/// <param name="x">First argument.</param>
/// <param name="y">Second argument.</param>
/// <param name="z">Third argument.</param>
/// <returns>Computed value.</returns>
double h(double x, double y, double z);

/// <summary>
/// Evaluates the expression R = [h(a, b, 1) + h(1, a, b)] / [1 + h(a^2 + b^2, 1, 0)].
/// </summary>
/// <param name="a">Parameter a.</param>
/// <param name="b">Parameter b.</param>
/// <returns>Computed expression result.</returns>
double expression(double a, double b);

/// <summary>
/// Result of Taylor series approximation containing the sum and term count.
/// </summary>
struct TaylorResult {
    double sum;
    int terms;
};

/// <summary>
/// Evaluates the recurrence term a_n = a_{n-1} * ((x - 1) / x) * (n / (n + 1)) for n >= 1.
/// </summary>
/// <param name="x">Argument x != 0.</param>
/// <param name="n">Term index n &gt;= 1.</param>
/// <param name="previous">Value of term a_{n-1}.</param>
/// <returns>Next term value a_n.</returns>
double nextTaylorTerm(double x, int n, double previous);

/// <summary>
/// Adds Taylor series terms for ln(x) until the absolute value of the term falls below epsilon,
/// writing the term count to the output reference parameter `terms`.
/// </summary>
/// <param name="x">Argument x &gt; 0.5.</param>
/// <param name="epsilon">Absolute error tolerance &gt; 0.</param>
/// <param name="terms">Output reference parameter for the number of terms.</param>
/// <returns>Accumulated Taylor series sum.</returns>
double taylorSum(double x, double epsilon, int& terms);

/// <summary>
/// Adds Taylor series terms for ln(x) until the absolute value of the term falls below epsilon.
/// </summary>
/// <param name="x">Argument x &gt; 0.5.</param>
/// <param name="epsilon">Absolute error tolerance &gt; 0.</param>
/// <returns>TaylorResult with sum and term count.</returns>
TaylorResult taylorSum(double x, double epsilon);

/// <summary>
/// Tabulates the Taylor approximation of ln(x) over [start, end] with step.
/// </summary>
std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    double start, double end, double step, double epsilon);

/// <summary>
/// Piecewise function helper(x):
/// For |x| &gt;= 1: (sin(x) + 1) / (1 + cos(x))
/// For |x| &lt; 1: 5-term polynomial series expansion.
/// </summary>
/// <param name="x">Argument x.</param>
/// <returns>Computed value, or std::nullopt at singularity.</returns>
std::optional<double> helper(double x);

/// <summary>
/// Evaluates nested expression E(g) = helper(g^2 + 1) + helper(g + helper(1)) + 1.
/// Returns std::nullopt if any subexpression encounters a singularity.
/// </summary>
/// <param name="g">Parameter g.</param>
/// <returns>Computed value or std::nullopt.</returns>
std::optional<double> nestedExpression(double g);

/// <summary>
/// Computes logTerm(i) = sin(i) / (1 + cos(i)).
/// </summary>
/// <param name="i">Term index.</param>
/// <returns>Summand value.</returns>
double term(int i);

/// <summary>
/// Computes the sum of logTerm(i) for i = 1 .. n using 5 recursive and iterative methods:
/// iterative, simple recursive ascending, simple recursive descending,
/// accumulator recursive ascending, and accumulator recursive descending.
/// </summary>
/// <param name="n">Number of terms [1, 5000].</param>
/// <returns>Array of 5 computed sums.</returns>
std::array<double, 5> recursiveSums(int n);

/// <summary>
/// Result structure for geometric sequence containing the n-th term,
/// sum of n terms, and recursion stack depths.
/// </summary>
struct GeometricResult {
    double term;
    double sum;
    int termDepth;
    int sumDepth;
};

/// <summary>
/// Recursively computes the n-th term and sum of first n terms of a geometric progression:
/// b_n = b_1 * q^{n-1}, S_n = sum_{i=1}^{n} b_i.
/// </summary>
/// <param name="first">First term b_1.</param>
/// <param name="ratio">Common ratio q.</param>
/// <param name="n">Number of terms [1, 1000].</param>
/// <returns>GeometricResult.</returns>
GeometricResult geometric(double first, double ratio, int n);

} // namespace Lb5
