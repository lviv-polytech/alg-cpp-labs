#pragma once

#include <optional>
#include <utility>
#include <vector>

namespace Lb5::Task2 {

    /// <summary>
    /// Result structure for Taylor series approximation of ln(x).
    /// </summary>
    struct TaylorResult {
        double sum;
        int terms;
    };

    /// <summary>
    /// Calculates the next Taylor term from previous term using recurrence relation:
    /// a_{n+1} = a_n * ((x - 1) / x) * (n / (n + 1)).
    /// </summary>
    /// <param name="x">The evaluation point x != 0.</param>
    /// <param name="n">Current term index n &gt;= 1.</param>
    /// <param name="previous">Value of term a_n.</param>
    /// <returns>Computed value of next term a_{n+1}.</returns>
    /// <exception cref="std::invalid_argument">Thrown if n &lt; 1 or x == 0.</exception>
    double nextTaylorTerm(double x, int n, double previous);

    /// <summary>
    /// Evaluates the Taylor series approximation for ln(x) until term magnitude is below epsilon:
    /// ln(x) = sum_{n=1}^{infinity} (1/n) * ((x - 1) / x)^n.
    /// Convergence region is x &gt; 0.5.
    /// </summary>
    /// <param name="x">Argument x &gt; 0.5.</param>
    /// <param name="epsilon">Absolute error tolerance &gt; 0.</param>
    /// <returns>TaylorResult containing sum and term count.</returns>
    /// <exception cref="std::invalid_argument">Thrown if arguments are non-finite or epsilon &lt;= 0.</exception>
    /// <exception cref="std::domain_error">Thrown if x &lt;= 0.5 (outside convergence domain).</exception>
    /// <exception cref="std::runtime_error">Thrown if maximum term limit is exceeded.</exception>
    TaylorResult taylorSum(double x, double epsilon);

    /// <summary>
    /// Tabulates the Taylor series for ln(x) over [start, end] with step.
    /// Points with x &lt;= 0.5 return std::nullopt.
    /// </summary>
    /// <param name="start">Interval start.</param>
    /// <param name="end">Interval end.</param>
    /// <param name="step">Grid step.</param>
    /// <param name="epsilon">Accuracy threshold.</param>
    /// <returns>Vector of (x, optional TaylorResult) pairs.</returns>
    std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
        double start, double end, double step, double epsilon);

} // namespace Lb5::Task2
