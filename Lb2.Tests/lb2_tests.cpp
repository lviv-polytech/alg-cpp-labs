#include "lb2_tests.h"

#include "../Lb2/Params.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace {

constexpr double TOLERANCE = 1e-9;

bool approxEqual(double a, double b, double tolerance = TOLERANCE) {
    return std::fabs(a - b) <= tolerance;
}

void testEqualForLargePositiveValues() {
    Params params;
    params.m = 25.0;
    calc(params);

    if (!approxEqual(params.z1, params.z2)) {
        std::cerr << "Expected equal values for m=25, got z1=" << params.z1
                  << " and z2=" << params.z2 << "\n";
        std::exit(1);
    }
}

void testNotEqualForSmallPositiveValues() {
    Params params;
    params.m = 0.25;
    calc(params);

    if (approxEqual(params.z1, params.z2)) {
        std::cerr << "Expected different values for m=0.25, but z1 and z2 were equal.\n";
        std::exit(1);
    }
}

void testBoundaryValue() {
    Params params;
    params.m = 2.0 / 3.0;
    calc(params);

    if (!approxEqual(params.z1, params.z2)) {
        std::cerr << "Expected equality at the boundary m=2/3, got z1=" << params.z1
                  << " and z2=" << params.z2 << "\n";
        std::exit(1);
    }
}

}  // namespace

namespace lb2_tests {

void runAll() {
    testEqualForLargePositiveValues();
    testNotEqualForSmallPositiveValues();
    testBoundaryValue();
}

}  // namespace lb2_tests
