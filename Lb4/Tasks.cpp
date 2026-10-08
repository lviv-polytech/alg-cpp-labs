#include "Tasks.h"

#include "task1/CycleSums.h"
#include "task2/PiecewiseFormula.h"
#include "task3/ParametricTabulation.h"
#include "task4/GraphTabulation.h"
#include "task5/NestedSums.h"
#include "task6/TaylorLog.h"

namespace Lb4 {

double term(const int i) {
    return Task1::term(i);
}

std::array<double, 4> cycleSums(const int n) {
    return Task1::cycleSums(n);
}

double formula(const double x) {
    return Task2::formula(x);
}

std::vector<std::pair<double, double>> tabulateFormula(
    const double start, const double end, const double step) {
    return Task2::tabulateFormula(start, end, step);
}

std::optional<double> parametric(const double a, const double b, const double c, const double x) {
    return Task3::parametric(a, b, c, x);
}

std::vector<std::pair<double, std::optional<double>>> tabulateParametric(
    const double a, const double b, const double c, const double start, const double end,
    const double step) {
    return Task3::tabulateParametric(a, b, c, start, end, step);
}

double graphFunction(const double radius, const double x) {
    return Task4::graphFunction(radius, x);
}

std::vector<std::pair<double, double>> tabulateGraph(
    const double radius, const double start, const double end, const double step) {
    return Task4::tabulateGraph(radius, start, end, step);
}

std::array<double, 4> nestedSums() {
    return Task5::nestedSums();
}

std::optional<TaylorResult> taylorLog(const double x, const double epsilon) {
    const auto result = Task6::taylorLog(x, epsilon);
    if (!result) return std::nullopt;
    return TaylorResult{result->sum, result->terms};
}

std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    const double start, const double end, const double step, const double epsilon) {
    const auto raw = Task6::tabulateTaylor(start, end, step, epsilon);
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

} // namespace Lb4
