#include "RecursiveSeries.h"
#include "../../Common/RecursionTracker.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace Lb5::Task4 {
namespace {

double logTerm(const int i) {
    return std::sin(static_cast<double>(i)) / (1.0 + std::cos(static_cast<double>(i)));
}

double sumUp(const int upper, const int i, const int level = 0) {
    Common::Recursion::printStep(std::cout, "sumUp", level, level + 1);
    return i > upper ? 0.0 : logTerm(i) + sumUp(upper, i + 1, level + 1);
}

double sumDown(const int lower, const int i, const int level = 0) {
    Common::Recursion::printStep(std::cout, "sumDown", level, level + 1);
    return i < lower ? 0.0 : logTerm(i) + sumDown(lower, i - 1, level + 1);
}

double sumUpAccumulator(const int upper, const int i, const double acc, const int level = 0) {
    Common::Recursion::printStep(std::cout, "sumUpAccumulator", level, level + 1);
    return i > upper ? acc : sumUpAccumulator(upper, i + 1, acc + logTerm(i), level + 1);
}

double sumDownAccumulator(const int lower, const int i, const double acc, const int level = 0) {
    Common::Recursion::printStep(std::cout, "sumDownAccumulator", level, level + 1);
    return i < lower ? acc : sumDownAccumulator(lower, i - 1, acc + logTerm(i), level + 1);
}

} // namespace

double term(const int i) {
    return logTerm(i);
}

std::array<double, 5> recursiveSums(const int n) {
    if (n < 1 || n > 5000) throw std::invalid_argument("N must be in [1, 5000].");
    double iterative = 0.0;
    for (int i = 1; i <= n; ++i) iterative += logTerm(i);
    return {iterative, sumUp(n, 1), sumDown(1, n), sumUpAccumulator(n, 1, 0.0),
            sumDownAccumulator(1, n, 0.0)};
}

} // namespace Lb5::Task4
