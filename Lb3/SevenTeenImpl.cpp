#include "SevenTeen.h"
#include <cmath>
#include "task1/Expression.h"
#include "task2/Expression.h"
#include "task3/Expression.h"
#include "task4/Expression.h"

namespace SevenTeen {

    double taskFirst(const double x) {
        return pow(x, 2) + 1 + Task1::Expression::calc(x);
    }

    double taskSecond(const double a, const double b, const double c, const double x) {
        return Task2::Expression::calc({a, b, c, x});
    }

    double taskThird(const double x, const double R) {
        return Task3::Expression::calc({x, R});
    }

    bool taskFourth(const double x, const double y, const double R) {
        return Task4::Expression::isInside(x, y, R);
    }
} // namespace SevenTeen
