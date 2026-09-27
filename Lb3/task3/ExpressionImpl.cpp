#include <cmath>
#include <iostream>

#include "Expression.h"

namespace Task3::Expression {
    double calc(const Params &params) {
        const double thresholdLeft = -1.0 - params.R;

        if (params.x <= thresholdLeft) {
            return 1.0;
        }

        if (params.x <= -1.0) {
            return -std::sqrt(params.R * params.R - (params.x + 1.0) * (params.x + 1.0));
        }

        if (params.x <= 2.0) {
            return -params.R;
        }

        return (params.R * (params.x - 4.0)) / 2.0;
    }
}
