#include "PiecewiseExpression.h"

#include <cmath>
#include <stdexcept>

namespace Lb5::Task3 {

constexpr double SINGULARITY_TOLERANCE = 1e-12;

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

} // namespace Lb5::Task3
