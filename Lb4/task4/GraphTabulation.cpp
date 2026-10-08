#include "GraphTabulation.h"
#include "../Core/Tabulation.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace Lb4::Task4 {

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
    return Core::tabulate(start, end, step, [=](const double x) { return graphFunction(radius, x); });
}

} // namespace Lb4::Task4
