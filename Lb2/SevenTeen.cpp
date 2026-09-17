#include "Params.h"

#include <cmath>

namespace {
constexpr double EPSILON = 1e-12;
constexpr double TWO = 2.0;
constexpr double THREE = 3.0;
constexpr double TWENTY_FOUR = 24.0;
}  // namespace

// For m > 0, the expression is equivalent to sign(3*m - 2) * sqrt(m).
// At m = 2/3, the direct fraction becomes 0/0; normalize it to sqrt(m) to avoid NaN.
void calc(Params& params) {
    params.z2 = std::sqrt(params.m);

    const double numerator = std::sqrt(std::pow(THREE * params.m + TWO, 2) - TWENTY_FOUR * params.m);
    const double denominator = (THREE * std::sqrt(params.m)) - (TWO / std::sqrt(params.m));

    if (std::abs(denominator) <= EPSILON) {
        params.z1 = params.z2;
        return;
    }

    params.z1 = numerator / denominator;
}