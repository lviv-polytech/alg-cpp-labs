#include <cmath>
#include <iostream>
#include <ostream>

namespace {

    double first(const double x) {
        // B = 5x^3 - x^2 - 2
        return 5.0 * std::pow(x, 3) - std::pow(x, 2) - 2.0;
    }

    double second(const double x) {
        // B = arctg((|x| + 1) / 2) + 8.3x
        return std::atan((std::abs(x) + 1.0) / 2.0) + (8.3 * x);
    }

    double third(const double x) {
        // B = ln|2x + e^(4+x)|
        return std::log(std::abs(2.0 * x + std::exp(4.0 + x)));
    }

    double calcShort(const double x) {
        double res = 0.0;
        if (x < 4) {
            res = first(x);
        }
        if (4 <= x && x < 7) {
            res = second(x);
        }
        if (x >= 7) {
            res = third(x);
        }
        return res;
    }

    double calcLong(const double x) {
        if (x < 4) {
            return first(x);
        } else {
            if (x < 7) {
                return second(x);
            } else {
                return third(x);
            }
        }
    }
}

namespace Task1::Expression {

    double calc(const double x) {
        const double rsShort = calcShort(x);
        const double rsLong = calcLong(x);
        std::cout << "\nResult short form: " << rsShort << std::endl;
        std::cout << "Result long form: " << rsLong << std::endl;

        if (std::abs(rsShort - rsLong) > 1e-9) {
            std::cout << "\nResult isn't correct";
        }
        return rsShort;
    }
}
