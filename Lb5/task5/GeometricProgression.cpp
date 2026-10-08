#include "GeometricProgression.h"

#include <stdexcept>

namespace Lb5::Task5 {
namespace {

double geometricTerm(const double first, const double ratio, const int n, int& depth) {
    ++depth;
    if (n == 1) return first;
    return geometricTerm(first, ratio, n - 1, depth) * ratio;
}

double geometricSum(const double first, const double ratio, const int n, int& depth) {
    ++depth;
    if (n == 1) return first;
    int termDepth = 0;
    const double currentTerm = geometricTerm(first, ratio, n, termDepth);
    return geometricSum(first, ratio, n - 1, depth) + currentTerm;
}

} // namespace

GeometricResult geometric(const double first, const double ratio, const int n) {
    if (n < 1 || n > 1000) throw std::invalid_argument("n must be in [1, 1000].");
    int termDepth = 0;
    const double nthTerm = geometricTerm(first, ratio, n, termDepth);
    int sumDepth = 0;
    const double sum = geometricSum(first, ratio, n, sumDepth);
    return {nthTerm, sum, termDepth, sumDepth};
}

} // namespace Lb5::Task5
