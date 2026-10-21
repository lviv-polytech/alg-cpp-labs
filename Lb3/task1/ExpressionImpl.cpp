#include <cmath>
#include <iostream>

namespace {

    // Перша гілка: 4x^7 - x^5 + x^3 - 2
    double first(const double x) {
        return 4.0 * std::pow(x, 7) - std::pow(x, 5) + std::pow(x, 3) - 2.0;
    }

    // Друга гілка: arctg((|x| + 1) / 2) + 8.3x
    double second(const double x) {
        return std::atan((std::abs(x) + 1.0) / 2.0) + (8.3 * x);
    }

    // Третя гілка: ln|2x + e^(4x + 1)|
    double third(const double x) {
        return std::log(std::abs(2.0 * x + std::exp(4.0 * x + 1.0)));
    }

    // Спільна частина: x^2 + 1
    double baseTerm(const double x) {
        return std::pow(x, 2) + 1.0;
    }

    // Скорочена форма розгалуження
    double calcShort(const double x) {
        double branch = 0.0;
        if (x < 4.0) {
            branch = first(x);
        }
        if (x >= 4.0 && x < 7.0) {
            branch = second(x);
        }
        if (x >= 7.0) {
            branch = third(x);
        }
        return baseTerm(x) + branch;
    }

    // Повна форма розгалуження
    double calcLong(const double x) {
        double branch = 0.0;
        if (x < 4.0) {
            branch = first(x);
        } else {
            if (x < 7.0) {
                branch = second(x);
            } else {
                branch = third(x);
            }
        }
        return baseTerm(x) + branch;
    }
}

namespace Task1::Expression {

    double calc(const double x) {
        const double rsShort = calcShort(x);
        const double rsLong = calcLong(x);
        std::cout << "\nResult short form: " << rsShort << std::endl;
        std::cout << "Result long form: " << rsLong << std::endl;

        if (std::abs(rsShort - rsLong) > 1e-9) {
            std::cout << "\nResult isn't correct" << std::endl;
        }
        return rsShort;
    }
}
