#pragma once

#include <array>
#include <optional>
#include <utility>
#include <vector>

namespace Lb4 {

double term(int i);
std::array<double, 4> cycleSums(int n);
double formula(double x);
std::vector<std::pair<double, double>> tabulateFormula(double start, double end, double step);
std::optional<double> parametric(double a, double b, double c, double x);
std::vector<std::pair<double, std::optional<double>>> tabulateParametric(
    double a, double b, double c, double start, double end, double step);
double graphFunction(double radius, double x);
std::vector<std::pair<double, double>> tabulateGraph(
    double radius, double start, double end, double step);
std::array<double, 4> nestedSums();
struct TaylorResult {
    double sum;
    int terms;
};
std::optional<TaylorResult> taylorLog(double x, double epsilon);
std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    double start, double end, double step, double epsilon);

}  // namespace Lb4
