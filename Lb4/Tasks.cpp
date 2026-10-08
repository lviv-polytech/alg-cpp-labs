#include "Tasks.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace Lb4 {
namespace {
constexpr double RANGE_TOLERANCE = 1e-9;
constexpr int MAX_TAYLOR_TERMS = 1'000'000;

void validateRange(double start, double end, double step) {
    if (!std::isfinite(start) || !std::isfinite(end) || !std::isfinite(step) ||
        step <= 0.0 || start > end) {
        throw std::invalid_argument("Range requires finite values, start <= end, and step > 0.");
    }
}

template <typename F>
auto tabulate(double start, double end, double step, F function) {
    validateRange(start, end, step);
    using Result = decltype(function(start));
    std::vector<std::pair<double, Result>> rows;
    const auto count = static_cast<std::size_t>(std::floor((end - start) / step + RANGE_TOLERANCE)) + 1;
    rows.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        const double x = start + static_cast<double>(i) * step;
        if (x > end + RANGE_TOLERANCE) {
            break;
        }
        rows.emplace_back(x, function(x));
    }
    return rows;
}
}  // namespace

double term(const int i) {
    return std::sin(static_cast<double>(i)) / (1.0 + std::cos(static_cast<double>(i)));
}

std::array<double, 4> cycleSums(const int n) {
    if (n < 1) {
        throw std::invalid_argument("N must be at least 1.");
    }
    std::array<double, 4> sums{};
    int i = 1;
    while (i <= n) sums[0] += term(i++);
    i = 1;
    do {
        sums[1] += term(i++);
    } while (i <= n);
    for (i = 1; i <= n; ++i) sums[2] += term(i);
    for (i = n; i >= 1; --i) sums[3] += term(i);
    return sums;
}

double formula(const double x) {
    if (x < 4.0) {
        const double x2 = x * x;
        const double x3 = x2 * x;
        const double x5 = x3 * x2;
        const double x7 = x5 * x2;
        return x2 + 1.0 + 4.0 * x7 - x5 + x3 - 2.0;
    }
    if (x < 7.0) {
        return x * x + 1.0 + std::atan((std::fabs(x) + 1.0) / 2.0) + 8.3 * x;
    }
    return x * x + 1.0 + std::log(std::fabs(2.0 * x + std::exp(4.0 * x + 1.0)));
}

std::vector<std::pair<double, double>> tabulateFormula(
    const double start, const double end, const double step) {
    return tabulate(start, end, step, formula);
}

std::optional<double> parametric(const double a, const double b, const double c, const double x) {
    if (x + 10.0 < 0.0 && b != 0.0) return a * x * x - c * x + b;
    if (x + 10.0 > 0.0 && b == 0.0) {
        if (x == c) return std::nullopt;
        return (x - a) / (x - c);
    }
    if (a == c) return std::nullopt;
    return -x / (a - c);
}

std::vector<std::pair<double, std::optional<double>>> tabulateParametric(
    const double a, const double b, const double c, const double start, const double end,
    const double step) {
    return tabulate(start, end, step, [=](const double x) { return parametric(a, b, c, x); });
}

double graphFunction(const double radius, const double x) {
    if (!std::isfinite(radius) || radius <= 0.0) {
        throw std::invalid_argument("R must be finite and positive.");
    }
    if (x < -1.0 - radius) return 1.0;
    if (x <= -1.0) {
        return -std::sqrt(std::max(0.0, radius * radius - (x + 1.0) * (x + 1.0)));
    }
    if (x <= 2.0) return -radius;
    return radius * (x - 4.0) / 2.0;
}

std::vector<std::pair<double, double>> tabulateGraph(
    const double radius, const double start, const double end, const double step) {
    return tabulate(start, end, step, [=](const double x) { return graphFunction(radius, x); });
}

std::array<double, 4> nestedSums() {
    std::array<double, 4> sums{};
    int k = 1;
    while (k <= 20) {
        double inner = 0.0;
        int i = 1;
        while (i <= k) inner += std::cos(i + k), ++i;
        sums[0] += std::sqrt(std::sin(k) * std::sin(k) + std::fabs(inner));
        ++k;
    }
    k = 1;
    do {
        double inner = 0.0;
        int i = 1;
        do {
            inner += std::cos(i + k);
            ++i;
        } while (i <= k);
        sums[1] += std::sqrt(std::sin(k) * std::sin(k) + std::fabs(inner));
        ++k;
    } while (k <= 20);
    for (k = 1; k <= 20; ++k) {
        double inner = 0.0;
        for (int i = 1; i <= k; ++i) inner += std::cos(i + k);
        sums[2] += std::sqrt(std::sin(k) * std::sin(k) + std::fabs(inner));
    }
    for (k = 20; k >= 1; --k) {
        double inner = 0.0;
        for (int i = k; i >= 1; --i) inner += std::cos(i + k);
        sums[3] += std::sqrt(std::sin(k) * std::sin(k) + std::fabs(inner));
    }
    return sums;
}

std::optional<TaylorResult> taylorLog(const double x, const double epsilon) {
    if (!std::isfinite(x) || !std::isfinite(epsilon) || epsilon <= 0.0) {
        throw std::invalid_argument("x and epsilon must be finite and epsilon must be positive.");
    }
    if (x <= 0.5) return std::nullopt;
    const double q = (x - 1.0) / x;
    double addend = q;
    double sum = 0.0;
    int terms = 0;
    do {
        sum += addend;
        ++terms;
        if (std::fabs(addend) < epsilon) break;
        if (terms >= MAX_TAYLOR_TERMS) {
            throw std::runtime_error("Taylor series exceeded the iteration limit.");
        }
        addend *= q * static_cast<double>(terms) / static_cast<double>(terms + 1);
    } while (true);
    return TaylorResult{sum, terms};
}

std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    const double start, const double end, const double step, const double epsilon) {
    return tabulate(start, end, step, [=](const double x) { return taylorLog(x, epsilon); });
}

}  // namespace Lb4
