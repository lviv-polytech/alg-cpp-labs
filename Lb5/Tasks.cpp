#include "Tasks.h"

#include "task1/RationalExpression.h"
#include "task2/TaylorSeries.h"
#include "task3/PiecewiseExpression.h"
#include "task4/RecursiveSeries.h"
#include "task5/GeometricProgression.h"

namespace Lb5 {

double h(const double x, const double y, const double z) {
    return Task1::h(x, y, z);
}

double expression(const double a, const double b) {
    return Task1::expression(a, b);
}

double nextTaylorTerm(const double x, const int n, const double previous) {
    return Task2::nextTaylorTerm(x, n, previous);
}

TaylorResult taylorSum(const double x, const double epsilon) {
    const auto result = Task2::taylorSum(x, epsilon);
    return TaylorResult{result.sum, result.terms};
}

std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    const double start, const double end, const double step, const double epsilon) {
    const auto raw = Task2::tabulateTaylor(start, end, step, epsilon);
    std::vector<std::pair<double, std::optional<TaylorResult>>> rows;
    rows.reserve(raw.size());
    for (const auto& [x, opt] : raw) {
        if (opt) {
            rows.emplace_back(x, TaylorResult{opt->sum, opt->terms});
        } else {
            rows.emplace_back(x, std::nullopt);
        }
    }
    return rows;
}

std::optional<double> helper(const double x) {
    return Task3::helper(x);
}

std::optional<double> nestedExpression(const double g) {
    return Task3::nestedExpression(g);
}

double term(const int i) {
    return Task4::term(i);
}

std::array<double, 5> recursiveSums(const int n) {
    return Task4::recursiveSums(n);
}

GeometricResult geometric(const double first, const double ratio, const int n) {
    const auto res = Task5::geometric(first, ratio, n);
    return GeometricResult{res.term, res.sum, res.termDepth, res.sumDepth};
}

} // namespace Lb5
