#include "CycleSums.h"

#include <cmath>
#include <stdexcept>

namespace Lb4::Task1 {

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

} // namespace Lb4::Task1
