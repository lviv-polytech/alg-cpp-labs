#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "../Lb3/SevenTeen.h"
#include "../Lb3/task4/Expression.h"

namespace {

constexpr double TOLERANCE = 1e-9;

bool approxEqual(const double a, const double b, const double eps = TOLERANCE) {
    return std::fabs(a - b) <= eps;
}

// ==================== TASK 4 UNIT TESTS ====================

void testTask4InsideHappyPaths() {
    const double R = 4.0;

    // Origin (common boundary point for both regions)
    assert(Task4::Expression::isInside(0.0, 0.0, R));

    // Quadrant II interior points
    assert(Task4::Expression::isInside(-2.0, 1.0, R));
    assert(Task4::Expression::isInside(-3.0, 0.5, R));
    assert(Task4::Expression::isInside(-1.0, 1.5, R));

    // Quadrant IV interior points
    assert(Task4::Expression::isInside(2.0, -1.0, R));
    assert(Task4::Expression::isInside(3.0, -0.5, R));
    assert(Task4::Expression::isInside(1.0, -1.5, R));

    std::cout << "[PASS] Task 4 - Inside happy paths\n";
}

void testTask4OutsideHappyPaths() {
    const double R = 4.0;

    // Quadrant I (always outside)
    assert(!Task4::Expression::isInside(1.0, 1.0, R));
    assert(!Task4::Expression::isInside(2.0, 3.0, R));

    // Quadrant III (always outside)
    assert(!Task4::Expression::isInside(-1.0, -1.0, R));
    assert(!Task4::Expression::isInside(-2.0, -3.0, R));

    // Quadrant II outside the circular arc
    assert(!Task4::Expression::isInside(-2.0, 4.0, R)); // ( -2 + 4 )^2 + 4^2 = 20 > 16
    assert(!Task4::Expression::isInside(-0.5, 3.5, R));

    // Quadrant IV outside the circular arc
    assert(!Task4::Expression::isInside(2.0, -4.0, R)); // ( 2 - 4 )^2 + (-4)^2 = 20 > 16
    assert(!Task4::Expression::isInside(0.5, -3.5, R));

    // Outside x bounds
    assert(!Task4::Expression::isInside(-4.5, 1.0, R));
    assert(!Task4::Expression::isInside(4.5, -1.0, R));

    // Far away
    assert(!Task4::Expression::isInside(100.0, 100.0, R));
    assert(!Task4::Expression::isInside(-100.0, 100.0, R));

    std::cout << "[PASS] Task 4 - Outside happy paths\n";
}

void testTask4BoundaryPoints() {
    const double R = 5.0;

    // Boundary vertices
    assert(Task4::Expression::isInside(-R, 0.0, R));
    assert(Task4::Expression::isInside(-R, R, R));
    assert(Task4::Expression::isInside(R, 0.0, R));
    assert(Task4::Expression::isInside(R, -R, R));

    // Straight line boundaries
    assert(Task4::Expression::isInside(-R, R / 2.0, R));  // vertical left boundary
    assert(Task4::Expression::isInside(-R / 2.0, 0.0, R)); // horizontal negative X-axis
    assert(Task4::Expression::isInside(R, -R / 2.0, R));  // vertical right boundary
    assert(Task4::Expression::isInside(R / 2.0, 0.0, R));  // horizontal positive X-axis

    // Points on the circular arc in Quadrant II
    const double angle = M_PI / 4.0;
    const double arcX_Q2 = -R + R * std::cos(angle);
    const double arcY_Q2 = R * std::sin(angle);
    assert(Task4::Expression::isInside(arcX_Q2, arcY_Q2, R));

    // Points on the circular arc in Quadrant IV
    const double arcX_Q4 = R - R * std::cos(angle);
    const double arcY_Q4 = -R * std::sin(angle);
    assert(Task4::Expression::isInside(arcX_Q4, arcY_Q4, R));

    // Points just outside the boundary
    assert(!Task4::Expression::isInside(-R - 0.01, 1.0, R));
    assert(!Task4::Expression::isInside(R + 0.01, -1.0, R));
    assert(!Task4::Expression::isInside(arcX_Q2, arcY_Q2 + 0.01, R));
    assert(!Task4::Expression::isInside(arcX_Q4, arcY_Q4 - 0.01, R));

    std::cout << "[PASS] Task 4 - Boundary points\n";
}

void testTask4EdgeCasesAndValidation() {
    // Non-positive R must throw std::invalid_argument
    bool threwZero = false;
    try {
        Task4::Expression::isInside(0.0, 0.0, 0.0);
    } catch (const std::invalid_argument &) {
        threwZero = true;
    }
    assert(threwZero);

    bool threwNegative = false;
    try {
        Task4::Expression::isInside(0.0, 0.0, -5.0);
    } catch (const std::invalid_argument &) {
        threwNegative = true;
    }
    assert(threwNegative);

    // Non-finite R must throw
    const double nanVal = std::numeric_limits<double>::quiet_NaN();
    const double infVal = std::numeric_limits<double>::infinity();

    bool threwNanR = false;
    try {
        Task4::Expression::isInside(0.0, 0.0, nanVal);
    } catch (const std::invalid_argument &) {
        threwNanR = true;
    }
    assert(threwNanR);

    bool threwInfR = false;
    try {
        Task4::Expression::isInside(0.0, 0.0, infVal);
    } catch (const std::invalid_argument &) {
        threwInfR = true;
    }
    assert(threwInfR);

    // Non-finite x or y should safely return false
    assert(!Task4::Expression::isInside(nanVal, 0.0, 5.0));
    assert(!Task4::Expression::isInside(0.0, nanVal, 5.0));
    assert(!Task4::Expression::isInside(infVal, 0.0, 5.0));
    assert(!Task4::Expression::isInside(0.0, -infVal, 5.0));

    std::cout << "[PASS] Task 4 - Edge cases and validation\n";
}

void testSevenTeenFacade() {
    const double R = 3.0;
    assert(SevenTeen::taskFourth(0.0, 0.0, R) == true);
    assert(SevenTeen::taskFourth(-1.0, 1.0, R) == true);
    assert(SevenTeen::taskFourth(1.0, -1.0, R) == true);
    assert(SevenTeen::taskFourth(2.0, 2.0, R) == false);

    // Verify task 1 runs and returns finite value
    const double res1 = SevenTeen::taskFirst(2.0);
    assert(std::isfinite(res1));

    // Verify task 2 runs and returns finite value
    const double res2 = SevenTeen::taskSecond(1.0, 2.0, 3.0, 0.5);
    assert(std::isfinite(res2));

    // Verify task 3 runs and returns finite value
    const double res3 = SevenTeen::taskThird(-1.0, 2.0);
    assert(std::isfinite(res3));

    std::cout << "[PASS] SevenTeen facade integration\n";
}

} // namespace

int main() {
    std::cout << "Running Lb3 Unit Tests...\n";
    testTask4InsideHappyPaths();
    testTask4OutsideHappyPaths();
    testTask4BoundaryPoints();
    testTask4EdgeCasesAndValidation();
    testSevenTeenFacade();
    std::cout << "All Lb3 tests successfully passed!\n";
    return 0;
}
