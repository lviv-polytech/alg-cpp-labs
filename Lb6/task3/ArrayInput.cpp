#include "ArrayInput.h"

namespace Lb6::Task3 {
namespace {

void inputIntRecursive(std::istream& in, std::ostream& out, int* values,
                       const std::size_t size, const std::size_t index) {
    if (index >= size) return;
    out << "a[" << index << "] = ";
    if (!(in >> values[index])) throw std::runtime_error("Failed to read array element.");
    inputIntRecursive(in, out, values, size, index + 1);
}

} // namespace

namespace Iterative {
void input(std::istream& in, std::ostream& out, int* values, const std::size_t size) {
    inputTemplate(in, out, values, size);
}
} // namespace Iterative

namespace Recursive {
void input(std::istream& in, std::ostream& out, int* values, const std::size_t size) {
    inputIntRecursive(in, out, values, size, 0);
}
} // namespace Recursive

} // namespace Lb6::Task3
