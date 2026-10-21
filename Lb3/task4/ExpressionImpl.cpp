#include "Expression.h"
#include <stdexcept>

namespace Task4::Expression {

    bool isInside(const Params &params) {
        const auto [x, y, R] = params;

        if (R <= 0.0) {
            throw std::invalid_argument("Radius R must be positive.");
        }

        // II чверть (верхня ліва)
        const bool inUpperLeft = (x >= -R) && (y >= 0.0) &&
                                 ((x + R) * (x + R) + y * y <= R * R);

        // IV чверть (нижня права)
        const bool inLowerRight = (x <= R) && (y <= 0.0) &&
                                  ((x - R) * (x - R) + y * y <= R * R);

        return inUpperLeft || inLowerRight;
    }

    bool isInside(const double x, const double y, const double R) {
        return isInside(Params{x, y, R});
    }

} // namespace Task4::Expression
