#include "../Lb5/Tasks.h"
#include "../Lb5/UI/TablePrinter.h"

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
void require(bool condition, const char* msg = "Lb5 test failed.") {
    if (!condition) {
        std::cerr << msg << '\n';
        std::exit(1);
    }
}

void near(double actual, double expected, double tolerance = 1e-6) {
    if (std::fabs(actual - expected) >= tolerance) {
        std::cerr << std::setprecision(15) << "Expected " << expected << ", got " << actual << '\n';
        std::exit(1);
    }
}

template <typename Exception, typename Callable>
void requireThrows(Callable&& fn, const char* msg) {
    bool caught = false;
    try {
        fn();
    } catch (const Exception&) {
        caught = true;
    }
    require(caught, msg);
}
} // namespace

int main() {
    // ------------------------------------------------------------------------
    // Task 5.1: Rational Expression (Variant 17)
    // ------------------------------------------------------------------------
    near(Lb5::expression(1.0, 1.0), 1.25);
    near(Lb5::expression(0.0, 0.0), 1.0);
    near(Lb5::expression(2.0, -1.0), 0.5416666667, 1e-8);

    // ------------------------------------------------------------------------
    // Task 5.2: Taylor Series for ln(x) (Variant 17) - Verification Matrix
    // ------------------------------------------------------------------------
    // TC-01: Reference point x = 2.0, eps = 1e-4 -> sum ~= 0.69306484, terms = 10
    {
        int termsOut = 0;
        const double sumOut = Lb5::taylorSum(2.0, 1e-4, termsOut);
        near(sumOut, 0.69306485615, 1e-9);
        require(termsOut == 10, "TC-01: Expected 10 terms at x=2, eps=1e-4");

        const auto res = Lb5::taylorSum(2.0, 1e-4);
        near(res.sum, sumOut, 1e-12);
        require(res.terms == 10);
        near(res.sum, std::log(2.0), 1e-4);
    }

    // TC-02: Center of expansion x = 1.0, eps = 1e-4 -> a_0 = 0, sum = 0.0, terms = 1
    {
        const auto res = Lb5::taylorSum(1.0, 1e-4);
        near(res.sum, 0.0, 1e-12);
        require(res.terms == 1, "TC-02: Expected 1 term at x=1.0");
    }

    // TC-03: Alternating region x = 0.6, eps = 1e-4 -> sum ~= -0.51078897, terms = 16
    {
        const auto res = Lb5::taylorSum(0.6, 1e-4);
        near(res.sum, -0.51078897, 1e-6);
        require(res.terms == 16, "TC-03: Expected 16 terms at x=0.6, eps=1e-4");
        near(res.sum, std::log(0.6), 1e-4);
    }

    // TC-04: Point x = 0.8, eps = 1e-4 -> sum ~= -0.22313639, terms = 6
    {
        const auto res = Lb5::taylorSum(0.8, 1e-4);
        near(res.sum, -0.22313639, 1e-6);
        require(res.terms == 6, "TC-04: Expected 6 terms at x=0.8, eps=1e-4");
        near(res.sum, std::log(0.8), 1e-4);
    }

    // TC-05: Recurrence relation helper nextTaylorTerm(x, n, previous)
    {
        // At x = 2.0: a_0 = 0.5, a_1 = 0.125, a_2 = 1/24
        const double a0 = 0.5;
        const double a1 = Lb5::nextTaylorTerm(2.0, 1, a0);
        near(a1, 0.125, 1e-12);
        const double a2 = Lb5::nextTaylorTerm(2.0, 2, a1);
        near(a2, 1.0 / 24.0, 1e-12);
    }

    // TC-06: Mixed-domain tabulation [0.4, 1.0] step 0.2, eps = 1e-4
    {
        const auto rows = Lb5::tabulateTaylor(0.4, 1.0, 0.2, 1e-4);
        require(rows.size() == 4, "TC-06: Expected 4 rows for [0.4, 1.0] step 0.2");
        require(!rows[0].second.has_value(), "TC-06: x=0.4 must be outside domain");
        require(rows[1].second.has_value() && rows[1].second->terms == 16);
        require(rows[2].second.has_value() && rows[2].second->terms == 6);
        require(rows[3].second.has_value() && rows[3].second->terms == 1);
    }

    // TC-07 & TC-08: Boundary & invalid parameter exceptions
    requireThrows<std::domain_error>([] { Lb5::taylorSum(0.5, 1e-4); }, "x=0.5 must throw domain_error");
    requireThrows<std::domain_error>([] { Lb5::taylorSum(-1.0, 1e-4); }, "x=-1.0 must throw domain_error");
    requireThrows<std::invalid_argument>([] { Lb5::taylorSum(2.0, 0.0); }, "eps=0 must throw invalid_argument");
    requireThrows<std::invalid_argument>([] { Lb5::taylorSum(2.0, -1e-4); }, "eps<0 must throw invalid_argument");
    requireThrows<std::invalid_argument>([] { Lb5::nextTaylorTerm(2.0, 0, 0.5); }, "n=0 must throw invalid_argument");
    requireThrows<std::invalid_argument>([] { Lb5::nextTaylorTerm(0.0, 1, 0.5); }, "x=0 must throw invalid_argument");
    requireThrows<std::invalid_argument>([] { Lb5::tabulateTaylor(0.2, 0.4, 0.1, -1e-4); }, "tabulateTaylor eps<=0 must throw");
    requireThrows<std::invalid_argument>([] { Lb5::tabulateTaylor(2.0, 1.0, 0.2, 1e-4); }, "start>end must throw");
    requireThrows<std::invalid_argument>([] { Lb5::tabulateTaylor(1.0, 2.0, 0.0, 1e-4); }, "step<=0 must throw");

    // Table formatting non-breaking test
    {
        std::ostringstream out;
        Lb5::UI::printTaylorHeader(out);
        for (const auto& [x, result] : Lb5::tabulateTaylor(0.4, 1.0, 0.2, 1e-4)) {
            Lb5::UI::printTaylorRow(out, x, result);
        }
        Lb5::UI::printTaylorFooter(out);
        std::istringstream lines(out.str());
        std::string line;
        std::size_t expectedLen = 0;
        while (std::getline(lines, line)) {
            require(!line.empty(), "Table line must not be empty");
            if (expectedLen == 0) expectedLen = line.size();
            require(line.size() == expectedLen, "Every line in Taylor table must have identical width");
        }
    }

    // ------------------------------------------------------------------------
    // Task 5.3: Piecewise Helper Function & Nested Expression (Variant 17)
    // ------------------------------------------------------------------------
    near(Lb5::helper(0.0).value(), 1.0);
    near(Lb5::helper(0.5).value(), 1.2605918365, 1e-8);
    require(!Lb5::helper(std::acos(-1.0)));
    require(!Lb5::nestedExpression(std::acos(-1.0) - Lb5::helper(1.0).value()));

    // ------------------------------------------------------------------------
    // Task 5.4: Recursive Sums (Variant 17)
    // ------------------------------------------------------------------------
    const auto sums = Lb5::recursiveSums(3);
    for (double sum : sums) near(sum, 16.205130, 1e-5);
    const auto oneTerm = Lb5::recursiveSums(1);
    for (double sum : oneTerm) near(sum, 0.546302, 1e-6);

    // ------------------------------------------------------------------------
    // Task 5.5: Geometric Progression Recursion (Variant 17)
    // ------------------------------------------------------------------------
    const auto gp = Lb5::geometric(2.0, 3.0, 5);
    near(gp.term, 162.0);
    near(gp.sum, 242.0);
    require(gp.termDepth == 5 && gp.sumDepth == 5);
    const auto unitRatio = Lb5::geometric(2.0, 1.0, 4);
    near(unitRatio.sum, 8.0);
    require(unitRatio.termDepth == 4 && unitRatio.sumDepth == 4);

    std::cout << "Lb5 tests passed.\n";
}
