#include "Expression.h"

#include <cmath>
#include <stdexcept>

namespace Task4::Expression {
namespace {
    constexpr double TOLERANCE = 1e-9;
}

    /// <summary>
    /// Evaluates if the given point (x, y) is within the shaded region defined by radius R.
    ///
    /// The target region is defined as:
    /// - Region A (Quadrant II, top-left):
    ///     -R &lt;= x &lt;= 0
    ///      0 &lt;= y &lt;= R
    ///     (x + R)^2 + y^2 &lt;= R^2
    ///
    /// - Region B (Quadrant IV, bottom-right):
    ///      0 &lt;= x &lt;= R
    ///     -R &lt;= y &lt;= 0
    ///     (x - R)^2 + y^2 &lt;= R^2
    /// </summary>
    bool isInside(const Params &params) {
        if (!std::isfinite(params.R) || params.R <= 0.0) {
            throw std::invalid_argument("Radius R must be a finite positive number.");
        }

        if (!std::isfinite(params.x) || !std::isfinite(params.y)) {
            return false;
        }

        const double rSquared = params.R * params.R;

        // Check Quadrant II (top-left region)
        const bool inUpperLeft = (params.x >= -params.R - TOLERANCE) &&
                                 (params.x <= TOLERANCE) &&
                                 (params.y >= -TOLERANCE) &&
                                 ((params.x + params.R) * (params.x + params.R) + params.y * params.y <= rSquared + TOLERANCE);

        // Check Quadrant IV (bottom-right region)
        const bool inLowerRight = (params.x >= -TOLERANCE) &&
                                  (params.x <= params.R + TOLERANCE) &&
                                  (params.y <= TOLERANCE) &&
                                  ((params.x - params.R) * (params.x - params.R) + params.y * params.y <= rSquared + TOLERANCE);

        return inUpperLeft || inLowerRight;
    }

    bool isInside(const double x, const double y, const double R) {
        return isInside(Params{x, y, R});
    }

} // namespace Task4::Expression
