#include "DynamicArrayOperations.h"

#include <random>
#include <stdexcept>

namespace Lb6::Task4 {

// ============================================================================
// Iterative Implementations (Method 1)
// ============================================================================

void initArrayIterative(std::vector<double>& a, double minVal, double maxVal) {
    if (minVal > maxVal) throw std::invalid_argument("minVal cannot exceed maxVal.");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = dist(gen);
    }
}

void printArrayIterative(std::ostream& out, const std::vector<double>& a, int fieldWidth, int precision) {
    auto flags = out.flags();
    out << std::fixed << std::setprecision(precision);
    for (std::size_t i = 0; i < a.size(); ++i) {
        out << std::setw(fieldWidth) << a[i];
    }
    out << '\n';
    out.flags(flags);
}

int countPositiveIterative(const std::vector<double>& a) {
    int count = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] > 0.0) ++count;
    }
    return count;
}

int findLastZeroIndexIterative(const std::vector<double>& a, double eps) {
    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
        if (isZero(a[static_cast<std::size_t>(i)], eps)) {
            return i;
        }
    }
    return -1;
}

double sumAfterIndexIterative(const std::vector<double>& a, int startIndex) {
    if (startIndex < -1 || startIndex >= static_cast<int>(a.size())) {
        throw std::out_of_range("startIndex out of range.");
    }
    double sum = 0.0;
    for (std::size_t i = static_cast<std::size_t>(startIndex + 1); i < a.size(); ++i) {
        sum += a[i];
    }
    return sum;
}

double sumAfterLastZeroIterative(const std::vector<double>& a, double eps) {
    int lastZero = findLastZeroIndexIterative(a, eps);
    if (lastZero == -1 || lastZero >= static_cast<int>(a.size()) - 1) {
        return 0.0;
    }
    return sumAfterIndexIterative(a, lastZero);
}

void partitionByIntPartIterative(std::vector<double>& a) {
    std::size_t writePos = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (hasIntPartAtMostOne(a[i])) {
            double temp = a[i];
            for (std::size_t k = i; k > writePos; --k) {
                a[k] = a[k - 1];
            }
            a[writePos] = temp;
            ++writePos;
        }
    }
}

// ============================================================================
// Recursive Implementations (Method 2)
// ============================================================================

void initArrayRecursive(std::vector<double>& a, double minVal, double maxVal, std::size_t i) {
    if (i >= a.size()) return;
    if (i == 0 && minVal > maxVal) throw std::invalid_argument("minVal cannot exceed maxVal.");
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    a[i] = dist(gen);
    initArrayRecursive(a, minVal, maxVal, i + 1);
}

void printArrayRecursive(std::ostream& out, const std::vector<double>& a, std::size_t i, int fieldWidth, int precision) {
    if (i >= a.size()) {
        out << '\n';
        return;
    }
    auto flags = out.flags();
    out << std::fixed << std::setprecision(precision) << std::setw(fieldWidth) << a[i];
    out.flags(flags);
    printArrayRecursive(out, a, i + 1, fieldWidth, precision);
}

int countPositiveRecursive(const std::vector<double>& a, std::size_t i) {
    if (i >= a.size()) return 0;
    int current = (a[i] > 0.0) ? 1 : 0;
    return current + countPositiveRecursive(a, i + 1);
}

int findLastZeroIndexRecursive(const std::vector<double>& a, int i, double eps) {
    if (i < 0) return -1;
    if (isZero(a[static_cast<std::size_t>(i)], eps)) return i;
    return findLastZeroIndexRecursive(a, i - 1, eps);
}

double sumFromIndexRecursive(const std::vector<double>& a, std::size_t i) {
    if (i >= a.size()) return 0.0;
    return a[i] + sumFromIndexRecursive(a, i + 1);
}

double sumAfterLastZeroRecursive(const std::vector<double>& a, double eps) {
    if (a.empty()) return 0.0;
    int lastZero = findLastZeroIndexRecursive(a, static_cast<int>(a.size()) - 1, eps);
    if (lastZero == -1 || lastZero >= static_cast<int>(a.size()) - 1) {
        return 0.0;
    }
    return sumFromIndexRecursive(a, static_cast<std::size_t>(lastZero + 1));
}

void shiftRightRecursive(std::vector<double>& a, std::size_t writePos, std::size_t k) {
    if (k <= writePos) return;
    a[k] = a[k - 1];
    shiftRightRecursive(a, writePos, k - 1);
}

void partitionByIntPartRecursive(std::vector<double>& a, std::size_t i, std::size_t writePos) {
    if (i >= a.size()) return;

    std::size_t nextWritePos = writePos;
    if (hasIntPartAtMostOne(a[i])) {
        double temp = a[i];
        shiftRightRecursive(a, writePos, i);
        a[writePos] = temp;
        nextWritePos = writePos + 1;
    }

    partitionByIntPartRecursive(a, i + 1, nextWritePos);
}

// ============================================================================
// Unified Dispatcher Functions
// ============================================================================

int countPositive(const std::vector<double>& values, bool recursive) {
    return recursive ? countPositiveRecursive(values, 0) : countPositiveIterative(values);
}

int lastZeroIndex(const std::vector<double>& values, bool recursive) {
    if (values.empty()) return -1;
    return recursive
        ? findLastZeroIndexRecursive(values, static_cast<int>(values.size()) - 1)
        : findLastZeroIndexIterative(values);
}

double sumAfter(const std::vector<double>& values, int index, bool recursive) {
    if (index < -1 || index >= static_cast<int>(values.size())) {
        throw std::out_of_range("Index must identify a position or be -1.");
    }
    const std::size_t start = static_cast<std::size_t>(index + 1);
    if (recursive) return sumFromIndexRecursive(values, start);
    return sumAfterIndexIterative(values, index);
}

void stablePartition(std::vector<double>& values, bool recursive) {
    if (recursive) partitionByIntPartRecursive(values, 0, 0);
    else partitionByIntPartIterative(values);
}

} // namespace Lb6::Task4
