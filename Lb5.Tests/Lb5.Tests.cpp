#include "../Lb5/Tasks.h"

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {
void require(bool condition) {
    if (!condition) {
        std::cerr << "Lb5 test failed.\n";
        std::exit(1);
    }
}
void near(double actual, double expected, double tolerance = 1e-6) {
    if (std::fabs(actual - expected) >= tolerance) {
        std::cerr << std::setprecision(15) << "Expected " << expected << ", got " << actual << '\n';
        std::exit(1);
    }
}
}

int main() {
    near(Lb5::expression(1, 1), 1.25);
    near(Lb5::expression(0, 0), 1.0);
    near(Lb5::helper(0).value(), 1.0);
    near(Lb5::helper(0.5).value(), 1.2605918365, 1e-8);
    near(Lb5::taylorSum(2, 1e-4).sum, 0.693065, 1e-6);
    require(Lb5::taylorSum(2, 1e-4).terms == 10);
    const auto sums = Lb5::recursiveSums(3);
    for (double sum : sums) near(sum, 16.205130, 1e-5);
    const auto oneTerm = Lb5::recursiveSums(1);
    for (double sum : oneTerm) near(sum, 0.546302, 1e-6);
    const auto gp = Lb5::geometric(2, 3, 5);
    near(gp.term, 162);
    near(gp.sum, 242);
    require(gp.termDepth == 5 && gp.sumDepth == 5);
    const auto unitRatio = Lb5::geometric(2, 1, 4);
    near(unitRatio.sum, 8);
    require(unitRatio.termDepth == 4 && unitRatio.sumDepth == 4);
    require(!Lb5::helper(std::acos(-1.0)));
    require(!Lb5::nestedExpression(std::acos(-1.0) - Lb5::helper(1.0).value()));
    std::cout << "Lb5 tests passed.\n";
}
