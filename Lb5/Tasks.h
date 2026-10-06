#pragma once

#include <array>
#include <optional>
#include <utility>
#include <vector>

namespace Lb5 {

/** The assignment helper h(x,y,z)=(x+y+z)/(x^2+y^2+z^2). */
double h(double x, double y, double z);
/** Evaluates the specified expression from two input parameters using h. */
double expression(double a, double b);
struct TaylorResult {
    double sum;
    int terms;
};
double nextTaylorTerm(double x, int n, double previous);
/** Adds Taylor terms for ln(x), including the first term whose magnitude is below epsilon. */
TaylorResult taylorSum(double x, double epsilon);
std::vector<std::pair<double, std::optional<TaylorResult>>> tabulateTaylor(
    double start, double end, double step, double epsilon);
std::optional<double> helper(double x);
/** Evaluates h(g^2+1)+h(g+h(1))+1; nullopt marks a cosine-denominator singularity. */
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
