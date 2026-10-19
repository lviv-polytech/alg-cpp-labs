#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

namespace Lb6::Task1 {

constexpr std::size_t SELECTION_SIZE = 25;
constexpr int DEFAULT_LOW = 4;
constexpr int DEFAULT_HIGH = 73;

/**
 * @brief Represents the calculated metrics of the array processing task.
 */
struct SelectionResult {
    int count;
    int sum;
};

/**
 * @brief Evaluates whether an element satisfies the criterion for Variant 17.
 *
 * Criterion definition:
 * Element matches if its value is divisible by 6 OR its index is not divisible by 5:
 *   P(r_i, i) = (r_i % 6 == 0) || (i % 5 != 0)
 *
 * Notice that on 20 indices where (i % 5 != 0), the criterion is unconditionally true.
 * On the remaining 5 indices (i in {0, 5, 10, 15, 20}), the criterion depends on (r_i % 6 == 0).
 *
 * @param index Zero-based index of the element in the array.
 * @param value Integer value of the element.
 * @return true if the element satisfies the criterion, false otherwise.
 */
bool isSelected(int index, int value);

// ============================================================================
// Iterative Implementations (Method 1)
// ============================================================================

/**
 * @brief Populates the array iteratively with uniform pseudo-random integers in [low, high].
 *
 * Formula: r_i = low + (rand() % (high - low + 1))
 * Domain constraints: low <= high; vector is resized to SELECTION_SIZE if needed.
 *
 * @param values Reference to the target vector to be populated in-place.
 * @param low Lower bound of the generation interval (default: 4).
 * @param high Upper bound of the generation interval (default: 73).
 */
void generateArray(std::vector<int>& values, int low = DEFAULT_LOW, int high = DEFAULT_HIGH);

/**
 * @brief Prints the array elements formatted into a single line with fixed column width.
 *
 * Uses setw(4) formatting for each element to align outputs before and after modification.
 *
 * @param out Output stream to write to.
 * @param values Vector of integers to print.
 */
void printArray(std::ostream& out, const std::vector<int>& values);

/**
 * @brief Computes the count of elements satisfying the selection criterion iteratively.
 *
 * Invariant bound: 20 <= count <= 25.
 *
 * @param values Vector of 25 integers.
 * @return Number of matching elements.
 * @throws std::invalid_argument if values.size() != SELECTION_SIZE.
 */
int countElements(const std::vector<int>& values);

/**
 * @brief Computes the sum of elements satisfying the selection criterion iteratively.
 *
 * Invariant bound: 80 <= sum <= 1825.
 *
 * @param values Vector of 25 integers.
 * @return Cumulative sum of matching elements.
 * @throws std::invalid_argument if values.size() != SELECTION_SIZE.
 */
int sumElements(const std::vector<int>& values);

/**
 * @brief Replaces elements satisfying the selection criterion with zero iteratively.
 *
 * CRITICAL INVARIANT: This function must be executed strictly AFTER countElements
 * and sumElements. If called earlier, zeroing elements causes (0 % 6 == 0) to evaluate
 * true, resulting in total information loss and incorrect sum values (0).
 *
 * @param values Reference to the vector of 25 integers to modify in-place.
 * @throws std::invalid_argument if values.size() != SELECTION_SIZE.
 */
void zeroElements(std::vector<int>& values);

// ============================================================================
// Recursive Implementations (Method 2)
// ============================================================================

/**
 * @brief Populates the array recursively with uniform pseudo-random integers in [low, high].
 *
 * Recurrence relation:
 * Base case: i >= n -> stop.
 * Recursive step: values[i] = rand_in_range(low, high); generateArrayRec(values, low, high, i + 1).
 *
 * @param values Reference to the vector to populate.
 * @param low Lower bound of interval (default: 4).
 * @param high Upper bound of interval (default: 73).
 * @param i Current index being populated (initial: 0).
 */
void generateArrayRec(std::vector<int>& values, int low = DEFAULT_LOW, int high = DEFAULT_HIGH, std::size_t i = 0);

/**
 * @brief Prints the array elements recursively in a single formatted row.
 *
 * Base case: i >= n -> print newline and return.
 * Recursive step: print setw(4) << values[i]; printArrayRec(out, values, i + 1).
 *
 * @param out Output stream.
 * @param values Vector to print.
 * @param i Current element index (initial: 0).
 */
void printArrayRec(std::ostream& out, const std::vector<int>& values, std::size_t i = 0);

/**
 * @brief Computes the count of matching elements recursively.
 *
 * Recurrence:
 *   K(i) = 0, if i >= n
 *   K(i) = chi(r_i, i) + K(i + 1), if i < n
 * Initial call: K(0).
 *
 * @param values Vector of 25 integers.
 * @param i Current index in the traversal (initial: 0).
 * @return Total count of matching elements.
 * @throws std::invalid_argument if values.size() != SELECTION_SIZE.
 */
int countElementsRec(const std::vector<int>& values, std::size_t i = 0);

/**
 * @brief Computes the sum of matching elements recursively.
 *
 * Recurrence:
 *   S(i) = 0, if i >= n
 *   S(i) = (chi(r_i, i) ? r_i : 0) + S(i + 1), if i < n
 * Initial call: S(0).
 *
 * @param values Vector of 25 integers.
 * @param i Current index in the traversal (initial: 0).
 * @return Total sum of matching elements.
 * @throws std::invalid_argument if values.size() != SELECTION_SIZE.
 */
int sumElementsRec(const std::vector<int>& values, std::size_t i = 0);

/**
 * @brief Replaces matching elements with zero recursively.
 *
 * Recurrence:
 *   Zero(i) = stop, if i >= n
 *   Zero(i) = { if (isSelected(i, r_i)) r_i = 0; Zero(i + 1); }, if i < n
 * Initial call: Zero(0).
 *
 * @param values Reference to the vector of 25 integers to modify.
 * @param i Current index (initial: 0).
 * @throws std::invalid_argument if values.size() != SELECTION_SIZE.
 */
void zeroElementsRec(std::vector<int>& values, std::size_t i = 0);

// ============================================================================
// Orchestration & Unified API
// ============================================================================

/**
 * @brief Dispatches element counting to iterative or recursive solver.
 *
 * @param values Vector of 25 integers.
 * @param recursive true to use recursive calculation, false for iterative.
 * @return Count of matching elements.
 */
int countSelected(const std::vector<int>& values, bool recursive);

/**
 * @brief Dispatches element summation to iterative or recursive solver.
 *
 * @param values Vector of 25 integers.
 * @param recursive true to use recursive calculation, false for iterative.
 * @return Sum of matching elements.
 */
int sumSelected(const std::vector<int>& values, bool recursive);

/**
 * @brief Dispatches in-place element zeroing to iterative or recursive solver.
 *
 * @param values Reference to vector of 25 integers.
 * @param recursive true to use recursive zeroing, false for iterative.
 */
void zeroSelected(std::vector<int>& values, bool recursive);

/**
 * @brief Orchestrates full Task 1 pipeline: count, sum, then zero out selected elements.
 *
 * Guarantees correct order of operations: count and sum are calculated before elements are zeroed.
 *
 * @param values Reference to vector of 25 integers.
 * @param recursive true to execute all steps recursively, false iteratively.
 * @return SelectionResult containing the calculated count and sum.
 */
SelectionResult processSelection(std::vector<int>& values, bool recursive);

} // namespace Lb6::Task1
