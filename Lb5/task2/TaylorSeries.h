#pragma once

#include <optional>
#include <utility>
#include <vector>

namespace Lb5::Task2 {

    /**
     * @brief Result structure for Taylor series approximation of ln(x).
     */
    struct TaylorResult {
        double sum;
        int terms;
    };

    /**
     * @brief Calculates the next Taylor series term a_n from the previous term a_{n-1}
     * using the recurrence relation for Variant 17:
     *   a_0 = (x - 1) / x
     *   a_n = a_{n-1} * ((x - 1) / x) * (n / (n + 1)), for n >= 1.
     *
     * @param x The evaluation point (must be finite and x != 0).
     * @param n Current step index (n >= 1, equal to the count of terms already accumulated).
     * @param previous Value of previous term a_{n-1}.
     * @return Computed value of term a_n.
     * @throws std::invalid_argument If n < 1, x == 0, or inputs are non-finite.
     */
    double nextTaylorTerm(double x, int n, double previous);

    /**
     * @brief Evaluates the Taylor series approximation for ln(x) using a do-while loop
     * until the absolute value of the added term is strictly less than epsilon:
     *   ln(x) = sum_{n=0}^{infinity} ((x - 1)^{n+1}) / ((n + 1) * x^{n+1}), for x > 0.5.
     * Writes the number of evaluated terms into the output reference parameter `terms`.
     *
     * @param x Argument x > 0.5.
     * @param epsilon Absolute error tolerance > 0.
     * @param[out] terms Output parameter receiving the number of accumulated terms.
     * @return Accumulated Taylor series sum.
     * @throws std::invalid_argument If arguments are non-finite or epsilon <= 0.
     * @throws std::domain_error If x <= 0.5 (outside convergence domain).
     * @throws std::runtime_error If maximum term limit is exceeded.
     */
    double taylorSum(double x, double epsilon, int& terms);

    /**
     * @brief Evaluates the Taylor series approximation for ln(x) and returns a TaylorResult struct.
     *
     * @param x Argument x > 0.5.
     * @param epsilon Absolute error tolerance > 0.
     * @return TaylorResult containing sum and term count.
     */
    TaylorResult taylorSum(double x, double epsilon);

    /**
     * @brief Tabulates the Taylor series for ln(x) over [start, end] with step dx.
     * Points with x <= 0.5 return std::nullopt.
     *
     * @param start Interval start x_start.
     * @param end Interval end x_end.
     * @param step Grid step dx > 0.
     * @param epsilon Accuracy threshold eps > 0.
     * @return Vector of (x, optional TaylorResult) pairs.
     */
    std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
        double start, double end, double step, double epsilon);

} // namespace Lb5::Task2
