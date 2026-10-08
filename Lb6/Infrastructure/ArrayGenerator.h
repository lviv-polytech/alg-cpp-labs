#pragma once

#include <vector>

namespace Lb6::Infrastructure {

    /// <summary>
    /// Generates a random array of 25 elements uniformly distributed in [4, 73].
    /// </summary>
    /// <param name="seed">Random generator seed.</param>
    /// <returns>A vector of 25 pseudorandom integers.</returns>
    std::vector<int> createArray(unsigned seed);

} // namespace Lb6::Infrastructure
