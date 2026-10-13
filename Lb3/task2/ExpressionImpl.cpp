#include <iostream>

#include "Expression.h"

using Params = Task2::Expression::Params;

namespace {
    double first(const Params &params) {
        // F = ax^2 - cx + b
        return params.a * params.x * params.x - params.c * params.x + params.b;
    }

    double second(const Params &params) {
        // F = x^2 - cx
        return params.x * params.x - params.c * params.x;
    }

    double third(const Params &params) {
        // F = -x / (a - c)
        return -params.x / (params.a - params.c);
    }

    double calcShort(const Params &params) {
        double res = 0.0;
        if (params.x + 10.0 < 0 && params.b != 0) {
            res = first(params);
        }
        if (params.x + 10.0 > 0 && params.b == 0) {
            res = second(params);
        }
        if (!(params.x + 10.0 < 0 && params.b != 0) && !(params.x + 10.0 > 0 && params.b == 0)) {
            res = third(params);
        }
        return res;
    }

    double calcLong(const Params &params) {
        if (params.x + 10.0 < 0 && params.b != 0) {
            return first(params);
        } else {
            if (params.x + 10.0 > 0 && params.b == 0) {
                return second(params);
            } else {
                return third(params);
            }
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
