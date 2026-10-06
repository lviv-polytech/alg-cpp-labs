#include "Tasks.h"

#include <cmath>
#include <stdexcept>

namespace Lb5 {
namespace {
constexpr double SINGULARITY_TOLERANCE = 1e-12;
constexpr int MAX_TAYLOR_TERMS = 1'000'000;

double logTerm(const int i) {
    return std::sin(static_cast<double>(i)) / (1.0 + std::cos(static_cast<double>(i)));
}

double sumUp(const int upper, const int i) {
    return i > upper ? 0.0 : logTerm(i) + sumUp(upper, i + 1);
}
double sumDown(const int lower, const int i) {
    return i < lower ? 0.0 : logTerm(i) + sumDown(lower, i - 1);
}
double sumUpAccumulator(const int upper, const int i, const double acc) {
    return i > upper ? acc : sumUpAccumulator(upper, i + 1, acc + logTerm(i));
}
double sumDownAccumulator(const int lower, const int i, const double acc) {
    return i < lower ? acc : sumDownAccumulator(lower, i - 1, acc + logTerm(i));
}

double geometricTerm(const double first, const double ratio, const int n, int& depth) {
    ++depth;
    if (n == 1) return first;
    return geometricTerm(first, ratio, n - 1, depth) * ratio;
}
double geometricSum(const double first, const double ratio, const int n, int& depth) {
    ++depth;
    if (n == 1) return first;
    int termDepth = 0;
    const double currentTerm = geometricTerm(first, ratio, n, termDepth);
    return geometricSum(first, ratio, n - 1, depth) + currentTerm;
}

void validateRange(const double start, const double end, const double step) {
    if (!std::isfinite(start) || !std::isfinite(end) || !std::isfinite(step) ||
        start > end || step <= 0.0) {
        throw std::invalid_argument("Require finite bounds, start <= end, and step > 0.");
    }
}
}  // namespace

double h(const double x, const double y, const double z) {
    return (x + y + z) / (x * x + y * y + z * z);
}

double expression(const double a, const double b) {
    const double squaredSum = a * a + b * b;
    return (h(a, b, 1.0) + h(1.0, a, b)) / (1.0 + h(squaredSum, 1.0, 0.0));
}

double nextTaylorTerm(const double x, const int n, const double previous) {
    if (n < 1 || x == 0.0) throw std::invalid_argument("Taylor recurrence requires n >= 1 and x != 0.");
    const double q = (x - 1.0) / x;
    return previous * q * static_cast<double>(n) / static_cast<double>(n + 1);
}

TaylorResult taylorSum(const double x, const double epsilon) {
    if (!std::isfinite(x) || !std::isfinite(epsilon) || epsilon <= 0.0)
        throw std::invalid_argument("x and epsilon must be finite and epsilon must be positive.");
    if (x <= 0.5) throw std::domain_error("x is outside the Taylor-series convergence domain.");
    double addend = (x - 1.0) / x;
    double sum = 0.0;
    int terms = 0;
    do {
        sum += addend;
        ++terms;
        if (std::fabs(addend) < epsilon) break;
        if (terms == MAX_TAYLOR_TERMS) throw std::runtime_error("Taylor series iteration limit reached.");
        addend = nextTaylorTerm(x, terms, addend);
    } while (true);
    return {sum, terms};
}

std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    const double start, const double end, const double step, const double epsilon) {
    validateRange(start, end, step);
    std::vector<std::pair<double, std::optional<TaylorResult>>> rows;
    for (std::size_t i = 0;; ++i) {
        const double x = start + static_cast<double>(i) * step;
        if (x > end + 1e-9) break;
        if (x <= 0.5) rows.emplace_back(x, std::nullopt);
        else rows.emplace_back(x, taylorSum(x, epsilon));
    }
    return rows;
}

std::optional<double> helper(const double x) {
    if (!std::isfinite(x)) throw std::invalid_argument("x must be finite.");
    if (std::fabs(x) >= 1.0) {
        const double denominator = 1.0 + std::cos(x);
        if (std::fabs(denominator) < SINGULARITY_TOLERANCE) return std::nullopt;
        return (std::sin(x) + 1.0) / denominator;
    }
    double sum = 1.0;
    double addend = 1.0;
    for (int i = 1; i <= 5; ++i) {
        addend *= x / static_cast<double>((2 * i - 1) * (2 * i));
        sum += addend;
    }
    return sum;
}

std::optional<double> nestedExpression(const double g) {
    const double hOne = *helper(1.0);
    const auto first = helper(g * g + 1.0);
    const auto second = helper(g + hOne);
    if (!first || !second) return std::nullopt;
    return *first + *second + 1.0;
}

double term(const int i) { return logTerm(i); }

std::array<double, 5> recursiveSums(const int n) {
    if (n < 1 || n > 5000) throw std::invalid_argument("N must be in [1, 5000].");
    double iterative = 0.0;
    for (int i = 1; i <= n; ++i) iterative += logTerm(i);
    return {iterative, sumUp(n, 1), sumDown(1, n), sumUpAccumulator(n, 1, 0.0),
            sumDownAccumulator(1, n, 0.0)};
}

GeometricResult geometric(const double first, const double ratio, const int n) {
    if (n < 1 || n > 1000) throw std::invalid_argument("n must be in [1, 1000].");
    int termDepth = 0;
    const double nthTerm = geometricTerm(first, ratio, n, termDepth);
    int sumDepth = 0;
    const double sum = geometricSum(first, ratio, n, sumDepth);
    return {nthTerm, sum, termDepth, sumDepth};
}

}  // namespace Lb5
