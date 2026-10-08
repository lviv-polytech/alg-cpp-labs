#include "EvenIndexSearch.h"

#include <cstddef>

namespace Lb6::Task2 {
namespace {

int evenIndexRecursive(const std::vector<int>& values, const std::size_t index, int best) {
    if (index == values.size()) return best;
    if (values[index] % 2 == 0 && (best == -1 || values[index] > values[best]))
        best = static_cast<int>(index);
    return evenIndexRecursive(values, index + 1, best);
}

} // namespace

int maxEvenIndex(const std::vector<int>& values, const bool recursive) {
    if (recursive) return evenIndexRecursive(values, 0, -1);
    int best = -1;
    for (std::size_t i = 0; i < values.size(); ++i)
        if (values[i] % 2 == 0 && (best == -1 || values[i] > values[best]))
            best = static_cast<int>(i);
    return best;
}

} // namespace Lb6::Task2
