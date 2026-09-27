#include <iostream>

#include "Expression.h"

using Params = Task2::Expression::Params;

namespace {
    double first(const Params &params) {
        return -((2 * params.x - params.c) / (params.b * params.x - params.a));
    }

    double second(const Params &params) {
        return (params.x - params.a) / (params.x - params.c);
    }

    double third(const Params &params) {
        return -(params.x / params.c) + (-params.c) / (2 * params.x + 1);
    }

    double calcShort(const Params &params) {
        return params.x < 0 && params.b != 0
                   ? first(params)
                   : params.x > 0 && params.b == 0
                         ? second(params)
                         : third(params);
    }

    double calcLong(const Params &params) {
        if (params.x < 0 && params.b != 0) {
            return first(params);
        } else if (params.x > 0 && params.b == 0) {
            return second(params);
        } else {
            return third(params);
        }
    }
} // namespace

namespace Task2::Expression {
    double calc(const Params& params) {
        const double rsShort = calcShort(params);
        const double rsLong = calcLong(params);

        std::cout << "\nResult short form: " << rsShort << std::endl;
        std::cout << "\nResult long form: " << rsLong << std::endl;

        if (std::abs(rsShort - rsLong) > 1e-9) {
            std::cout << "\nResult isn't correct";
        }
        return rsShort;
    }
}
