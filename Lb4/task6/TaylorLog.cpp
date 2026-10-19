#include "TaylorLog.h"
#include "../Core/Tabulation.h"

#include <cmath>
#include <stdexcept>

namespace Lb4::Task6 {

constexpr int MAX_TAYLOR_TERMS = 1'000'000;

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
    if (!std::isfinite(epsilon) || epsilon <= 0.0) {
        throw std::invalid_argument("epsilon must be finite and positive.");
    }
    return Core::tabulate(start, end, step, [=](const double x) { return taylorLog(x, epsilon); });
}

} // namespace Lb4::Task6
