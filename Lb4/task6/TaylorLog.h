#pragma once

#include <optional>
#include <utility>
#include <vector>

namespace Lb4::Task6 {

    /// <summary>
    /// Result of the ln(x) Taylor series approximation, holding the accumulated sum
    /// and the total count of included terms.
    /// </summary>
    struct TaylorResult {
        double sum;
        int terms;
    };

    /// <summary>
    /// Computes ln(x) approximation via Taylor series expansion for x &gt; 0.5:
    /// ln(x) = sum_{n=1}^{infinity} (1/n) * ((x - 1) / x)^n
    ///
    /// Recurrence relation:
    /// a_1 = (x - 1) / x
    /// a_{n+1} = a_n * ((x - 1) / x) * (n / (n + 1))
    ///
    /// Summation proceeds until |a_n| &lt; epsilon.
    /// </summary>
    /// <param name="x">Argument x (must be &gt; 0.5 for convergence).</param>
    /// <param name="epsilon">Target absolute error threshold (epsilon &gt; 0).</param>
    /// <returns>TaylorResult containing sum and term count, or std::nullopt if x &lt;= 0.5.</returns>
    /// <exception cref="std::invalid_argument">Thrown if x or epsilon are not finite or epsilon &lt;= 0.</exception>
    /// <exception cref="std::runtime_error">Thrown if iteration count exceeds safety limit.</exception>
    std::optional<TaylorResult> taylorLog(double x, double epsilon);

    /// <summary>
    /// Tabulates the Taylor series evaluation for ln(x) over [start, end] with step.
    /// </summary>
    /// <param name="start">Start bound.</param>
    /// <param name="end">End bound.</param>
    /// <param name="step">Grid step.</param>
    /// <param name="epsilon">Convergence tolerance.</param>
    /// <returns>Vector of pairs (x, optional TaylorResult).</returns>
    std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
        double start, double end, double step, double epsilon);

} // namespace Lb4::Task6
