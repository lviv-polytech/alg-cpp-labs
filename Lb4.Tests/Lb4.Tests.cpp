#include "../Lb4/Tasks.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {
void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << message << '\n';
        std::exit(1);
    }
}
void near(double actual, double expected, double tolerance = 1e-8) {
    expect(std::fabs(actual - expected) < tolerance, "Numeric result differs from expected value.");
}
void testCycles() {
    const auto values = Lb4::cycleSums(3);
    for (double value : values) near(value, 16.205130, 1e-5);
    bool rejected = false;
    try { (void)Lb4::cycleSums(0); } catch (const std::invalid_argument&) { rejected = true; }
    expect(rejected, "N=0 must be rejected.");
}
void testPiecewiseAndGraph() {
    near(Lb4::formula(0), -1.0);
    near(Lb4::formula(1), 4.0);
    near(Lb4::formula(4), 51.390290, 1e-5);
    near(Lb4::formula(7), 79.0, 1e-5);
    near(Lb4::graphFunction(2, -4), 1);
    near(Lb4::graphFunction(2, -3), 0);
    near(Lb4::graphFunction(2, 2), -2);
    near(Lb4::graphFunction(2, 6), 2);
    expect(!Lb4::parametric(2, 0, 4, 4), "Division by zero must return no value.");
    near(*Lb4::parametric(2, 0, 4, 0), 0.5);
    expect(!Lb4::parametric(2, 3, 2, -10), "a=c in the fallback branch is undefined.");
    near(*Lb4::parametric(2, 3, 4, -10), -5.0);
    near(Lb4::graphFunction(2, -1), -2);
    const auto rows = Lb4::tabulateFormula(-2, 9, 0.5);
    expect(rows.size() == 23 && std::fabs(rows.back().first - 9.0) < 1e-12,
           "Tabulation must include each in-range grid point.");
}
void testNestedAndTaylor() {
    const auto sums = Lb4::nestedSums();
    for (double value : sums) near(value, sums[0]);
    const auto result = Lb4::taylorLog(2, 1e-4);
    expect(result && result->terms == 10, "Taylor series should use 10 terms at x=2.");
    near(result->sum, 0.693065, 1e-6);
    expect(!Lb4::taylorLog(0.5, 1e-4), "x=0.5 is outside the convergence domain.");
    const auto atOne = Lb4::taylorLog(1.0, 1e-4);
    expect(atOne && atOne->terms == 1, "x=1 uses one zero-valued term.");
    near(atOne->sum, 0.0);
}
}

int main() {
    testCycles();
    testPiecewiseAndGraph();
    testNestedAndTaylor();
    std::cout << "Lb4 tests passed.\n";
}
