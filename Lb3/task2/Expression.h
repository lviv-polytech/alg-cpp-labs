#pragma once

namespace Task2::Expression {
    struct Params {
        const double a, b, c, x;

        Params(double a, double b, double c, double x)
            : a(a), b(b), c(c), x(x) {}
    };

    double calc(const Params& params);
}
