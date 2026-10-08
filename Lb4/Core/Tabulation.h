#pragma once

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Lb4::Core {

constexpr double RANGE_TOLERANCE = 1e-9;

/// <summary>
/// Validates bounds and step for tabulation grids.
/// Ensures start &lt;= end, step &gt; 0, and all arguments are finite numbers.
/// </summary>
/// <param name="start">Start bound of interval.</param>
/// <param name="end">End bound of interval.</param>
/// <param name="step">Grid step size.</param>
/// <exception cref="std::invalid_argument">Thrown if values are not finite, start &gt; end, or step &lt;= 0.</exception>
inline void validateRange(const double start, const double end, const double step) {
    if (!std::isfinite(start) || !std::isfinite(end) || !std::isfinite(step) ||
        step <= 0.0 || start > end) {
        throw std::invalid_argument("Range requires finite values, start <= end, and step > 0.");
    }
}

/// <summary>
/// Generic tabulation engine evaluating a callable function over interval [start, end] with fixed step.
/// </summary>
/// <typeparam name="F">Callable type taking double argument.</typeparam>
/// <param name="start">Start coordinate.</param>
/// <param name="end">End coordinate.</param>
/// <param name="step">Discretization step.</param>
/// <param name="function">Function to evaluate at each sample point.</param>
/// <returns>A vector of (x, f(x)) pairs.</returns>
template <typename F>
auto tabulate(const double start, const double end, const double step, F function) {
    validateRange(start, end, step);
    using Result = decltype(function(start));
    std::vector<std::pair<double, Result>> rows;
    const auto count = static_cast<std::size_t>(std::floor((end - start) / step + RANGE_TOLERANCE)) + 1;
    rows.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        const double x = start + static_cast<double>(i) * step;
        if (x > end + RANGE_TOLERANCE) {
            break;
        }
        rows.emplace_back(x, function(x));
    }
    return rows;
}

} // namespace Lb4::Core
