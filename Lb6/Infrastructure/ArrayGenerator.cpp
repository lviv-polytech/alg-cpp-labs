#include "ArrayGenerator.h"

#include <random>

namespace Lb6::Infrastructure {

std::vector<int> createArray(const unsigned seed) {
    constexpr std::size_t size = 25;
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> distribution(4, 73);
    std::vector<int> values(size);
    for (int& value : values) value = distribution(engine);
    return values;
}

} // namespace Lb6::Infrastructure
