#include "ParametricTabulation.h"
#include "../Core/Tabulation.h"

namespace Lb4::Task3 {

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
    return Core::tabulate(start, end, step, [=](const double x) { return parametric(a, b, c, x); });
}

} // namespace Lb4::Task3
