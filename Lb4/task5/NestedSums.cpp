#include "NestedSums.h"

#include <cmath>

namespace Lb4::Task5 {

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

} // namespace Lb4::Task5
