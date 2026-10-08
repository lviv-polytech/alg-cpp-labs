#include "RationalExpression.h"

namespace Lb5::Task1 {

double h(const double x, const double y, const double z) {
    return (x + y + z) / (x * x + y * y + z * z);
}

double expression(const double a, const double b) {
    const double squaredSum = a * a + b * b;
    return (h(a, b, 1.0) + h(1.0, a, b)) / (1.0 + h(squaredSum, 1.0, 0.0));
}

} // namespace Lb5::Task1
