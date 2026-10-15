#include "ArrayInput.h"

namespace Lb6::Task3 {

void inputArrayIterative(int* a, std::size_t n, std::istream& in, std::ostream* prompt) {
    if (!a && n > 0) throw std::invalid_argument("Array pointer cannot be null for n > 0.");
    for (std::size_t i = 0; i < n; ++i) {
        if (prompt) *prompt << "a[" << i << "] = ";
        if (!(in >> a[i])) throw std::runtime_error("Failed to read array element.");
    }
}

void printArrayIterative(const int* a, std::size_t n, std::ostream& out, int fieldWidth) {
    if (!a && n > 0) return;
    for (std::size_t i = 0; i < n; ++i) {
        out << std::setw(fieldWidth) << a[i];
    }
    out << '\n';
}

void inputArrayRecursive(int* a, std::size_t n, std::size_t i, std::istream& in, std::ostream* prompt) {
    if (i >= n) return;
    if (!a) throw std::invalid_argument("Array pointer cannot be null.");
    if (prompt) *prompt << "a[" << i << "] = ";
    if (!(in >> a[i])) throw std::runtime_error("Failed to read array element.");
    inputArrayRecursive(a, n, i + 1, in, prompt);
}

void printArrayRecursive(const int* a, std::size_t n, std::size_t i, std::ostream& out, int fieldWidth) {
    if (i >= n) {
        out << '\n';
        return;
    }
    out << std::setw(fieldWidth) << a[i];
    printArrayRecursive(a, n, i + 1, out, fieldWidth);
}

} // namespace Lb6::Task3
