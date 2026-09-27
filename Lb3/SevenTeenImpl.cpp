#include "SevenTeen.h"
#include <cmath>
#include "task1/Expression.h"

namespace SevenTeen {

    double taskFirst(const double x) {
        return pow(x, 2) + 1 + Task1::Expression::calc(x);
    }
} // namespace