#include "GeometricProgression.h"
#include "../../Common/RecursionTracker.h"

#include <iostream>
#include <stdexcept>

namespace Lb5::Task5 {
namespace {

double geometricTerm(const double first, const double ratio, const int n, int& depth, const int level = 0) {
    ++depth;
    Common::Recursion::printStep(std::cout, "geometricTerm", level, depth);
    if (n == 1) return first;
    return geometricTerm(first, ratio, n - 1, depth, level + 1) * ratio;
}

double geometricSum(const double first, const double ratio, const int n, int& depth, const int level = 0) {
    ++depth;
    Common::Recursion::printStep(std::cout, "geometricSum", level, depth);
    if (n == 1) return first;
    int termDepth = 0;
    const double currentTerm = geometricTerm(first, ratio, n, termDepth, 0);
    return geometricSum(first, ratio, n - 1, depth, level + 1) + currentTerm;
}

} // namespace

GeometricResult geometric(const double first, const double ratio, const int n) {
    if (n < 1 || n > 1000) throw std::invalid_argument("n must be in [1, 1000].");
    int termDepth = 0;
    const double nthTerm = geometricTerm(first, ratio, n, termDepth, 0);
    int sumDepth = 0;
    const double sum = geometricSum(first, ratio, n, sumDepth, 0);
    return {nthTerm, sum, termDepth, sumDepth};
}

} // namespace Lb5::Task5
