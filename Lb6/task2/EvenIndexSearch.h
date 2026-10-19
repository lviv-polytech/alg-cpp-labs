#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

namespace Lb6::Task2 {

constexpr int DEFAULT_MIN_VAL = -50;
constexpr int DEFAULT_MAX_VAL = 50;

/**
 * @brief Checks if a given integer is even.
 *
 * Condition: value % 2 == 0.
 * Works correctly for positive integers, negative integers, and zero (0 is even).
 *
 * @param value Integer value to check.
 * @return true if value is divisible by 2 without remainder, false otherwise.
 */
bool isEven(int value);

// ============================================================================
// Iterative Implementations (Method 1)
// ============================================================================

/**
 * @brief Populates the array iteratively with uniform pseudo-random integers in [minVal, maxVal].
 *
 * @param a Reference to the vector to populate in-place.
 * @param minVal Minimum random value (inclusive, default: -50).
 * @param maxVal Maximum random value (inclusive, default: 50).
 */
void initArrayIterative(std::vector<int>& a, int minVal = DEFAULT_MIN_VAL, int maxVal = DEFAULT_MAX_VAL);

/**
 * @brief Prints the array elements formatted into a single line with width = 5.
 *
 * @param out Output stream to write to.
 * @param a Vector of integers to print.
 */
void printArrayIterative(std::ostream& out, const std::vector<int>& a);

/**
 * @brief Finds the zero-based index of the maximum even element iteratively.
 *
 * Mathematical model:
 *   k_{-1} = -1
 *   k_i = i, if (a[i] % 2 == 0) and (k_{i-1} == -1 or a[i] > a[k_{i-1}])
 *   k_i = k_{i-1}, otherwise
 *
 * If multiple even elements equal the maximum, the first occurrence (smallest index) is returned.
 * Returns -1 if no even elements exist.
 *
 * Pure function: does NOT perform console I/O.
 *
 * @param a Vector of integers.
 * @return Index of the first maximum even element, or -1 if none found.
 */
int findMaxEvenIndexIterative(const std::vector<int>& a);

// ============================================================================
// Recursive Implementations (Method 2)
// ============================================================================

/**
 * @brief Populates the array recursively with uniform pseudo-random integers in [minVal, maxVal].
 *
 * @param a Reference to the vector to populate in-place.
 * @param minVal Minimum random value (inclusive, default: -50).
 * @param maxVal Maximum random value (inclusive, default: 50).
 * @param i Current element index (initial: 0).
 */
void initArrayRecursive(std::vector<int>& a, int minVal = DEFAULT_MIN_VAL, int maxVal = DEFAULT_MAX_VAL, std::size_t i = 0);

/**
 * @brief Prints the array elements recursively in a single formatted row with width = 5.
 *
 * @param out Output stream.
 * @param a Vector of integers to print.
 * @param i Current element index (initial: 0).
 */
void printArrayRecursive(std::ostream& out, const std::vector<int>& a, std::size_t i = 0);

/**
 * @brief Finds the zero-based index of the maximum even element recursively.
 *
 * Tail-recursive recurrence:
 *   F(a, n, i, best) = best, if i >= n
 *   F(a, n, i, best) = F(a, n, i + 1, i), if (a[i] % 2 == 0) and (best == -1 or a[i] > a[best])
 *   F(a, n, i, best) = F(a, n, i + 1, best), otherwise
 *
 * Pure function: does NOT perform console I/O.
 *
 * @param a Vector of integers.
 * @param i Current traversal index (initial: 0).
 * @param bestIndex Current index of best candidate (initial: -1).
 * @return Index of the first maximum even element, or -1 if none found.
 */
int findMaxEvenIndexRecursive(const std::vector<int>& a, std::size_t i = 0, int bestIndex = -1);

// ============================================================================
// Unified API
// ============================================================================

/**
 * @brief Dispatches maximum even index search to iterative or recursive solver.
 *
 * @param values Vector of integers.
 * @param recursive true to use recursive search, false for iterative.
 * @return Index of the first maximum even element, or -1 if none found.
 */
int maxEvenIndex(const std::vector<int>& values, bool recursive);

} // namespace Lb6::Task2
