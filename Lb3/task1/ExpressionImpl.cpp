#include <cmath>
#include <iostream>
#include <ostream>

namespace {

    double first(const double x) {
        return 4 + pow(x, 7) - pow(x, 5) + pow(x, 3) - 2;
    }

    double second(const double x) {
        return std::atan((std::abs(x) + 1) / 2) + (8.3 * x);
    }

    double third(const double x) {
        return std::log(std::abs(2 * x + std::exp(4 * x + 1)));
    }

    double calcShort(const double x) {
        if (x < 4) {
            return first(x);
        }
        if (4 <= x && x < 7) {
            return second(x);
        }
        return third(x);
    }

    double calcLong(const double x) {
        if (x < 4) {
            return first(x);
        } else if (4 <= x && x < 7) {
            return second(x);
        } else {
            return third(x);
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
