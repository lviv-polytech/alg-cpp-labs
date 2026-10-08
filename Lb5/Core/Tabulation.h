#pragma once

#include <cmath>
#include <stdexcept>

namespace Lb5::Core {

/// <summary>
/// Validates start, end, and step for interval tabulation.
/// Requires finite bounds, start &lt;= end, and step &gt; 0.
/// </summary>
/// <param name="start">Interval start.</param>
/// <param name="end">Interval end.</param>
/// <param name="step">Discretization step.</param>
/// <exception cref="std::invalid_argument">Thrown if values are invalid.</exception>
inline void validateRange(const double start, const double end, const double step) {
    if (!std::isfinite(start) || !std::isfinite(end) || !std::isfinite(step) ||
        start > end || step <= 0.0) {
        throw std::invalid_argument("Require finite bounds, start <= end, and step > 0.");
    }
}

} // namespace Lb5::Core
