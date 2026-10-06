#pragma once

#include <array>
#include <optional>
#include <utility>
#include <vector>

namespace Lb5 {

double h(double x, double y, double z);
double expression(double a, double b);
struct TaylorResult {
    double sum;
    int terms;
};
double nextTaylorTerm(double x, int n, double previous);
TaylorResult taylorSum(double x, double epsilon);
std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    double start, double end, double step, double epsilon);
std::optional<double> helper(double x);
std::optional<double> nestedExpression(double g);

double term(int i);
std::array<double, 5> recursiveSums(int n);

struct GeometricResult {
    double term;
    double sum;
    int termDepth;
    int sumDepth;
};
GeometricResult geometric(double first, double ratio, int n);

}  // namespace Lb5
