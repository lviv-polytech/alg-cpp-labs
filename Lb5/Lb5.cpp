#include "Tasks.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
void printTwoColumnHeader(const char* valueLabel) {
    std::cout << "+----------+----------------+\n"
              << "| " << std::setw(8) << "x" << " | " << std::setw(14) << valueLabel << " |\n"
              << "+----------+----------------+\n";
}
}

int main() {
    std::cout << "Lab 5: 1 expression, 2 Taylor table, 3 helper table, 4 recursive sums, 5 geometric series\n";
    std::cout << "-> Select task: ";
    int task;
    if (!(std::cin >> task)) return 1;
    std::cout << std::fixed << std::setprecision(8);
    try {
        // Task 1: evaluate the expression for given parameters.
        if (task == 1) {
            double a, b;
            std::cout << "-> a b: ";
            std::cin >> a >> b;
            std::cout << "R = " << Lb5::expression(a, b) << '\n';
        // Task 2: table of Taylor approximations for ln(x).
        } else if (task == 2) {
            double start, end, step, epsilon;
            std::cout << "-> start end step epsilon: ";
            std::cin >> start >> end >> step >> epsilon;
            std::cout << "+----------+----------------+----------------+------------+\n"
                      << "| " << std::setw(8) << "x" << " | " << std::setw(14) << "ln(x)"
                      << " | " << std::setw(14) << "Taylor sum" << " | " << std::setw(10) << "terms" << " |\n"
                      << "+----------+----------------+----------------+------------+\n";
            for (const auto& [x, result] : Lb5::tabulateTaylor(start, end, step, epsilon)) {
                std::cout << "| " << std::setw(8) << x << " | ";
                if (x > 0.0) std::cout << std::log(x);
                else std::cout << "undefined";
                std::cout << " | ";
                if (result)
                    std::cout << std::setw(14) << result->sum << " | " << std::setw(10) << result->terms << " |\n";
                else std::cout << std::setw(14) << "outside domain" << " | " << std::setw(10) << "-" << " |\n";
            }
            std::cout << "+----------+----------------+----------------+------------+\n";
        // Task 3: helper function table over the range.
        } else if (task == 3) {
            double start, end;
            int n;
            std::cout << "-> start end n: ";
            std::cin >> start >> end >> n;
            if (n < 1 || start > end) throw std::invalid_argument("Require n >= 1 and start <= end.");
            const double step = (end - start) / n;
            printTwoColumnHeader("E(g)");
            for (int j = 0; j <= n; ++j) {
                const double g = start + j * step;
                const auto value = Lb5::nestedExpression(g);
                std::cout << "| " << std::setw(8) << g << " | ";
                if (value) std::cout << std::setw(14) << *value;
                else std::cout << std::setw(14) << "undefined";
                std::cout << " |\n";
            }
            std::cout << "+----------+----------------+\n";
        // Task 4: recursive and iterative sum variants.
        } else if (task == 4) {
            int n;
            std::cout << "-> n: ";
            std::cin >> n;
            const auto values = Lb5::recursiveSums(n);
            const char* labels[] = {"iter", "rec up ++", "rec up --", "rec down ++", "rec down --"};
            for (int i = 0; i < 5; ++i) std::cout << labels[i] << ": " << values[i] << '\n';
        // Task 5: geometric sequence term and sum.
        } else if (task == 5) {
            double first, ratio;
            int n;
            std::cout << "-> first ratio n: ";
            std::cin >> first >> ratio >> n;
            const auto result = Lb5::geometric(first, ratio, n);
            std::cout << "b_n = " << result.term << "\nS_n = " << result.sum
                      << "\nterm depth = " << result.termDepth << "\nsum depth = " << result.sumDepth << '\n';
        } else {
            std::cerr << "Unknown task.\n";
            return 1;
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
