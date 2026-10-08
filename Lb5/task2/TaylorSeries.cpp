#include "TaylorSeries.h"
#include "../Core/Tabulation.h"

#include <cmath>
#include <stdexcept>

namespace Lb5::Task2 {

constexpr int MAX_TAYLOR_TERMS = 1'000'000;

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
    Core::validateRange(start, end, step);
    std::vector<std::pair<double, std::optional<TaylorResult>>> rows;
    for (std::size_t i = 0;; ++i) {
        const double x = start + static_cast<double>(i) * step;
        if (x > end + 1e-9) break;
        if (x <= 0.5) rows.emplace_back(x, std::nullopt);
        else rows.emplace_back(x, taylorSum(x, epsilon));
    }
    return rows;
}

} // namespace Lb5::Task2
