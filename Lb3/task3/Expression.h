#pragma once

namespace Task3::Expression {
    struct Params {
        const double x, R;

        Params(double x, double R) : x(x), R(R) {}
    };

    double calc(const Params& params);
}
