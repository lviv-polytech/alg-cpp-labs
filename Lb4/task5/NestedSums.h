#pragma once

#include <array>

namespace Lb4::Task5 {

    /// <summary>
    /// Evaluates the nested sum:
    /// S = sum_{k=1}^{20} sqrt(sin^2(k) + |sum_{i=1}^{k} cos(i + k)|)
    /// using four loop combinations:
    /// 1. while - while
    /// 2. do-while - do-while
    /// 3. ascending for - for
    /// 4. descending for - for
    /// </summary>
    /// <returns>Array of 4 calculated sums from each nested loop method.</returns>
    std::array<double, 4> nestedSums();

} // namespace Lb4::Task5
