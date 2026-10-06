#include "Tasks.h"

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    std::cout << "Lab 5: 1 expression, 2 Taylor table, 3 helper table, 4 recursive sums, 5 geometric series\n";
    int task;
    if (!(std::cin >> task)) return 1;
    std::cout << std::fixed << std::setprecision(8);
    try {
        if (task == 1) {
            double a, b;
            std::cin >> a >> b;
            std::cout << "R = " << Lb5::expression(a, b) << '\n';
        } else if (task == 2) {
            double start, end, step, epsilon;
            std::cin >> start >> end >> step >> epsilon;
            for (const auto& [x, result] : Lb5::tabulateTaylor(start, end, step, epsilon)) {
                std::cout << x << " | ";
                if (x > 0.0) std::cout << std::log(x);
                else std::cout << "undefined";
                std::cout << " | ";
                if (result) std::cout << result->sum << " | " << result->terms;
                else std::cout << "outside convergence domain";
                std::cout << '\n';
            }
        } else if (task == 3) {
            double start, end;
            int n;
            std::cin >> start >> end >> n;
            if (n < 1 || start > end) throw std::invalid_argument("Require n >= 1 and start <= end.");
            const double step = (end - start) / n;
            for (int j = 0; j <= n; ++j) {
                const double g = start + j * step;
                const auto value = Lb5::nestedExpression(g);
                std::cout << g << " | ";
                if (value) std::cout << *value;
                else std::cout << "undefined";
                std::cout << '\n';
            }
        } else if (task == 4) {
            int n;
            std::cin >> n;
            const auto values = Lb5::recursiveSums(n);
            const char* labels[] = {"iter", "rec up ++", "rec up --", "rec down ++", "rec down --"};
            for (int i = 0; i < 5; ++i) std::cout << labels[i] << ": " << values[i] << '\n';
        } else if (task == 5) {
            double first, ratio;
            int n;
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
