#pragma once

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

namespace Lb6::Task4 {

constexpr double EPSILON = 1e-9;

/**
 * @brief Checks if a floating-point number is considered zero within tolerance eps.
 */
inline bool isZero(double x, double eps = EPSILON) {
    return std::abs(x) < eps;
}

/**
 * @brief Checks if the integer part (truncation towards zero) of x is at most 1.
 * Mathematical equivalent: trunc(x) <= 1 <=> x < 2.0.
 */
inline bool hasIntPartAtMostOne(double x) {
    return std::trunc(x) <= 1.0;
}

// ============================================================================
// Iterative Implementations (Method 1)
// ============================================================================

/**
 * @brief Initializes a dynamic array iteratively with uniform random reals in [minVal, maxVal].
 */
void initArrayIterative(std::vector<double>& a, double minVal = -5.0, double maxVal = 5.0);

/**
 * @brief Prints array elements formatted into a single row with fixed width and precision.
 */
void printArrayIterative(std::ostream& out, const std::vector<double>& a, int fieldWidth = 8, int precision = 2);

/**
 * @brief Task 1.1: Counts positive elements (a[i] > 0.0) iteratively.
 */
int countPositiveIterative(const std::vector<double>& a);

/**
 * @brief Task 1.2 (Step A): Finds index of the last zero element iteratively (from right to left).
 * @return Index in [0, n - 1] or -1 if no zero element exists.
 */
int findLastZeroIndexIterative(const std::vector<double>& a, double eps = EPSILON);

/**
 * @brief Task 1.2 (Step B): Computes sum of elements after the specified index position iteratively.
 */
double sumAfterIndexIterative(const std::vector<double>& a, int startIndex);

/**
 * @brief Task 1.2: Computes sum of elements after the last zero element iteratively.
 * Returns 0.0 if no zeros exist or if the last zero is the last element.
 */
double sumAfterLastZeroIterative(const std::vector<double>& a, double eps = EPSILON);

/**
 * @brief Task 2: In-place stable partition: elements with trunc(x) <= 1 precede all others.
 */
void partitionByIntPartIterative(std::vector<double>& a);

// ============================================================================
// Recursive Implementations (Method 2)
// ============================================================================

/**
 * @brief Initializes a dynamic array recursively with uniform random reals in [minVal, maxVal].
 */
void initArrayRecursive(std::vector<double>& a, double minVal = -5.0, double maxVal = 5.0, std::size_t i = 0);

/**
 * @brief Prints array elements formatted recursively into a single row.
 */
void printArrayRecursive(std::ostream& out, const std::vector<double>& a, std::size_t i = 0, int fieldWidth = 8, int precision = 2);

/**
 * @brief Task 1.1: Counts positive elements (a[i] > 0.0) recursively.
 */
int countPositiveRecursive(const std::vector<double>& a, std::size_t i = 0);

/**
 * @brief Task 1.2 (Step A): Recursively searches for last zero element from right to left (i = n - 1 downto 0).
 */
int findLastZeroIndexRecursive(const std::vector<double>& a, int i, double eps = EPSILON);

/**
 * @brief Task 1.2 (Step B): Recursively sums suffix of array starting from index i.
 */
double sumFromIndexRecursive(const std::vector<double>& a, std::size_t i);

/**
 * @brief Task 1.2: Computes sum of elements after the last zero element recursively.
 */
double sumAfterLastZeroRecursive(const std::vector<double>& a, double eps = EPSILON);

/**
 * @brief Helper for Task 2: Recursively shifts sub-array a[writePos .. k - 1] one position right.
 */
void shiftRightRecursive(std::vector<double>& a, std::size_t writePos, std::size_t k);

/**
 * @brief Task 2: In-place recursive stable partition.
 */
void partitionByIntPartRecursive(std::vector<double>& a, std::size_t i = 0, std::size_t writePos = 0);

// ============================================================================
// Unified Dispatcher Functions (for backward compatibility)
// ============================================================================

int countPositive(const std::vector<double>& values, bool recursive);
int lastZeroIndex(const std::vector<double>& values, bool recursive);
double sumAfter(const std::vector<double>& values, int index, bool recursive);
void stablePartition(std::vector<double>& values, bool recursive);

} // namespace Lb6::Task4
