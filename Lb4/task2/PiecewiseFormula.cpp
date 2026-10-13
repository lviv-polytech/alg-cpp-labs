#include "PiecewiseFormula.h"
#include "../Core/Tabulation.h"

#include <cmath>

namespace Lb4::Task2 {

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
    return Core::tabulate(start, end, step, formula);
}

} // namespace Lb4::Task2
