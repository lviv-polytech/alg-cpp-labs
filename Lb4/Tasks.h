#pragma once

#include <array>
#include <optional>
#include <utility>
#include <vector>

namespace Lb4 {

/** Computes one summand sin(i)/(1+cos(i)); i is an integer radian angle. */
double term(int i);
/** Evaluates the sum from i=1 through N using while, do-while, for++, and for--. */
std::array<double, 4> cycleSums(int n);
/** Evaluates x^2+1+B(x), using thresholds 4 and 7 for the three assignment branches. */
double formula(double x);
std::vector<std::pair<double, double>> tabulateFormula(double start, double end, double step);
std::optional<double> parametric(double a, double b, double c, double x);
std::vector<std::pair<double, std::optional<double>>> tabulateParametric(
    double a, double b, double c, double start, double end, double step);
double graphFunction(double radius, double x);
std::vector<std::pair<double, double>> tabulateGraph(
    double radius, double start, double end, double step);
std::array<double, 4> nestedSums();
/** Result of the ln(x) Taylor approximation and the number of included terms. */
struct TaylorResult {
    double sum;
    int terms;
};
std::optional<TaylorResult> taylorLog(double x, double epsilon);
std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    double start, double end, double step, double epsilon);

}  // namespace Lb4
