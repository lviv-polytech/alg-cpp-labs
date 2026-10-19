#pragma once

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Lb6::Task3 {

// ============================================================================
// Part A: Ordinary Functions (specialized for int)
// ============================================================================

/**
 * @brief Reads an array of integers iteratively from an input stream.
 *
 * @param a Pointer to array destination.
 * @param n Number of elements to read.
 * @param in Input stream (default: std::cin).
 * @param prompt Optional output stream for interactive prompt messages ("a[i] = ").
 */
void inputArrayIterative(int* a, std::size_t n, std::istream& in = std::cin, std::ostream* prompt = nullptr);

/**
 * @brief Prints array of integers iteratively in a single formatted row.
 *
 * @param a Pointer to array.
 * @param n Number of elements.
 * @param out Output stream (default: std::cout).
 * @param fieldWidth Column formatting width (default: 8).
 */
void printArrayIterative(const int* a, std::size_t n, std::ostream& out = std::cout, int fieldWidth = 8);

/**
 * @brief Reads an array of integers recursively from an input stream.
 *
 * @param a Pointer to array destination.
 * @param n Number of elements to read.
 * @param i Current element index (initial: 0).
 * @param in Input stream (default: std::cin).
 * @param prompt Optional output stream for interactive prompt messages.
 */
void inputArrayRecursive(int* a, std::size_t n, std::size_t i = 0, std::istream& in = std::cin, std::ostream* prompt = nullptr);

/**
 * @brief Prints array of integers recursively in a single formatted row.
 *
 * @param a Pointer to array.
 * @param n Number of elements.
 * @param i Current element index (initial: 0).
 * @param out Output stream (default: std::cout).
 * @param fieldWidth Column formatting width (default: 8).
 */
void printArrayRecursive(const int* a, std::size_t n, std::size_t i = 0, std::ostream& out = std::cout, int fieldWidth = 8);

// std::vector<int> convenience overloads for Part A
inline void inputArrayIterative(std::vector<int>& a, std::istream& in = std::cin, std::ostream* prompt = nullptr) {
    inputArrayIterative(a.data(), a.size(), in, prompt);
}

inline void printArrayIterative(const std::vector<int>& a, std::ostream& out = std::cout, int fieldWidth = 8) {
    printArrayIterative(a.data(), a.size(), out, fieldWidth);
}

inline void inputArrayRecursive(std::vector<int>& a, std::size_t i = 0, std::istream& in = std::cin, std::ostream* prompt = nullptr) {
    inputArrayRecursive(a.data(), a.size(), i, in, prompt);
}

inline void printArrayRecursive(const std::vector<int>& a, std::size_t i = 0, std::ostream& out = std::cout, int fieldWidth = 8) {
    printArrayRecursive(a.data(), a.size(), i, out, fieldWidth);
}

// ============================================================================
// Part B: Function Templates (generic for any type T with operator>> and operator<<)
// ============================================================================

/**
 * @brief Generic iterative template function for array input.
 *
 * @tparam T Element type.
 * @param a Pointer to array destination.
 * @param n Number of elements to read.
 * @param in Input stream (default: std::cin).
 * @param prompt Optional output stream for prompts.
 */
template <typename T>
void inputArrayIterativeTemplate(T* a, std::size_t n, std::istream& in = std::cin, std::ostream* prompt = nullptr) {
    if (!a && n > 0) throw std::invalid_argument("Array pointer cannot be null for n > 0.");
    for (std::size_t i = 0; i < n; ++i) {
        if (prompt) *prompt << "a[" << i << "] = ";
        if (!(in >> a[i])) throw std::runtime_error("Failed to read array element.");
    }
}

/**
 * @brief Generic iterative template function for formatted array output.
 *
 * @tparam T Element type.
 * @param a Pointer to array.
 * @param n Number of elements.
 * @param out Output stream (default: std::cout).
 * @param fieldWidth Column formatting width (default: 8).
 */
template <typename T>
void printArrayIterativeTemplate(const T* a, std::size_t n, std::ostream& out = std::cout, int fieldWidth = 8) {
    if (!a && n > 0) return;
    for (std::size_t i = 0; i < n; ++i) {
        out << std::setw(fieldWidth) << a[i];
    }
    out << '\n';
}

/**
 * @brief Generic recursive template function for array input.
 *
 * @tparam T Element type.
 * @param a Pointer to array destination.
 * @param n Number of elements to read.
 * @param i Current element index (initial: 0).
 * @param in Input stream (default: std::cin).
 * @param prompt Optional output stream for prompts.
 */
template <typename T>
void inputArrayRecursiveTemplate(T* a, std::size_t n, std::size_t i = 0, std::istream& in = std::cin, std::ostream* prompt = nullptr) {
    if (i >= n) return;
    if (!a) throw std::invalid_argument("Array pointer cannot be null.");
    if (prompt) *prompt << "a[" << i << "] = ";
    if (!(in >> a[i])) throw std::runtime_error("Failed to read array element.");
    inputArrayRecursiveTemplate(a, n, i + 1, in, prompt);
}

/**
 * @brief Generic recursive template function for formatted array output.
 *
 * @tparam T Element type.
 * @param a Pointer to array.
 * @param n Number of elements.
 * @param i Current element index (initial: 0).
 * @param out Output stream (default: std::cout).
 * @param fieldWidth Column formatting width (default: 8).
 */
template <typename T>
void printArrayRecursiveTemplate(const T* a, std::size_t n, std::size_t i = 0, std::ostream& out = std::cout, int fieldWidth = 8) {
    if (i >= n) {
        out << '\n';
        return;
    }
    out << std::setw(fieldWidth) << a[i];
    printArrayRecursiveTemplate(a, n, i + 1, out, fieldWidth);
}

// std::vector<T> convenience overloads for Part B
template <typename T>
void inputArrayIterativeTemplate(std::vector<T>& a, std::istream& in = std::cin, std::ostream* prompt = nullptr) {
    inputArrayIterativeTemplate(a.data(), a.size(), in, prompt);
}

template <typename T>
void printArrayIterativeTemplate(const std::vector<T>& a, std::ostream& out = std::cout, int fieldWidth = 8) {
    printArrayIterativeTemplate(a.data(), a.size(), out, fieldWidth);
}

template <typename T>
void inputArrayRecursiveTemplate(std::vector<T>& a, std::size_t i = 0, std::istream& in = std::cin, std::ostream* prompt = nullptr) {
    inputArrayRecursiveTemplate(a.data(), a.size(), i, in, prompt);
}

template <typename T>
void printArrayRecursiveTemplate(const std::vector<T>& a, std::size_t i = 0, std::ostream& out = std::cout, int fieldWidth = 8) {
    printArrayRecursiveTemplate(a.data(), a.size(), i, out, fieldWidth);
}

// ============================================================================
// Backward compatibility layer for existing callers
// ============================================================================

namespace Iterative {
    inline void input(std::istream& in, std::ostream& out, int* values, std::size_t size) {
        inputArrayIterative(values, size, in, &out);
    }
}

namespace Recursive {
    inline void input(std::istream& in, std::ostream& out, int* values, std::size_t size) {
        inputArrayRecursive(values, size, 0, in, &out);
    }
}

template <typename T>
void inputTemplate(std::istream& in, std::ostream& out, T* values, std::size_t size) {
    inputArrayIterativeTemplate(values, size, in, &out);
}

template <typename T>
void inputTemplateRecursive(std::istream& in, std::ostream& out, T* values, std::size_t size, std::size_t index = 0, int level = 0) {
    (void)level;
    inputArrayRecursiveTemplate(values, size, index, in, &out);
}

} // namespace Lb6::Task3
