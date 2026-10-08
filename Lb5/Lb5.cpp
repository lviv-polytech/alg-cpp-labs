#include "Tasks.h"
#include "UI/TablePrinter.h"
#include "../Common/IO.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {

void runExpressionTask() {
    std::cout << "\n=== Task 1: Rational Expression ===\n";
    double a = 0.0, b = 0.0;
    std::cout << "-> a: ";
    if (!Common::IO::read(std::cin, a)) return;
    std::cout << "-> b: ";
    if (!Common::IO::read(std::cin, b)) return;
    std::cout << "R = " << Lb5::expression(a, b) << '\n';
}

void runTaylorTableTask() {
    std::cout << "\n=== Task 2: Taylor Series Table for ln(x) ===\n";
    double start = 0.0, end = 0.0, step = 0.0, epsilon = 0.0;
    std::cout << "-> start (x > 0.5): ";
    if (!Common::IO::read(std::cin, start)) return;
    std::cout << "-> end: ";
    if (!Common::IO::read(std::cin, end)) return;
    std::cout << "-> step: ";
    if (!Common::IO::read(std::cin, step)) return;
    std::cout << "-> epsilon: ";
    if (!Common::IO::read(std::cin, epsilon)) return;

    Lb5::UI::printTaylorHeader(std::cout);
    for (const auto& [x, result] : Lb5::tabulateTaylor(start, end, step, epsilon)) {
        std::cout << "| " << std::setw(8) << x << " | ";
        if (x > 0.0) std::cout << std::log(x);
        else std::cout << "undefined";
        std::cout << " | ";
        if (result) {
            std::cout << std::setw(14) << result->sum << " | " << std::setw(10) << result->terms << " |\n";
        } else {
            std::cout << std::setw(14) << "outside domain" << " | " << std::setw(10) << "-" << " |\n";
        }
    }
    Lb5::UI::printTaylorFooter(std::cout);
}

void runHelperTableTask() {
    std::cout << "\n=== Task 3: Piecewise Helper Table E(g) ===\n";
    double start = 0.0, end = 0.0;
    int n = 0;
    std::cout << "-> start: ";
    if (!Common::IO::read(std::cin, start)) return;
    std::cout << "-> end: ";
    if (!Common::IO::read(std::cin, end)) return;
    std::cout << "-> n (partitions >= 1): ";
    if (!Common::IO::read(std::cin, n)) return;

    if (n < 1 || start > end) throw std::invalid_argument("Require n >= 1 and start <= end.");
    const double step = (end - start) / n;
    Lb5::UI::printTwoColumnHeader(std::cout, "E(g)");
    for (int j = 0; j <= n; ++j) {
        const double g = start + j * step;
        const auto value = Lb5::nestedExpression(g);
        std::cout << "| " << std::setw(8) << g << " | ";
        if (value) std::cout << std::setw(14) << *value;
        else std::cout << "undefined";
        std::cout << " |\n";
    }
    Lb5::UI::printTwoColumnFooter(std::cout);
}

void runRecursiveSumsTask() {
    std::cout << "\n=== Task 4: Recursive Series Sums ===\n";
    int n = 0;
    std::cout << "-> n: ";
    if (!Common::IO::read(std::cin, n)) return;
    const auto values = Lb5::recursiveSums(n);
    const char* labels[] = {"iter", "rec up ++", "rec up --", "rec down ++", "rec down --"};
    for (int i = 0; i < 5; ++i) {
        std::cout << labels[i] << ": " << values[i] << '\n';
    }
}

void runGeometricTask() {
    std::cout << "\n=== Task 5: Geometric Progression ===\n";
    double first = 0.0, ratio = 0.0;
    int n = 0;
    std::cout << "-> first term (b1): ";
    if (!Common::IO::read(std::cin, first)) return;
    std::cout << "-> common ratio (q): ";
    if (!Common::IO::read(std::cin, ratio)) return;
    std::cout << "-> n (number of terms): ";
    if (!Common::IO::read(std::cin, n)) return;

    const auto result = Lb5::geometric(first, ratio, n);
    std::cout << "b_n = " << result.term << "\nS_n = " << result.sum
              << "\nterm depth = " << result.termDepth << "\nsum depth = " << result.sumDepth << '\n';
}

} // namespace

int main() {
    std::cout << std::fixed << std::setprecision(8);
    while (true) {
        std::cout << "\nAvailable tasks:\n";
        std::cout << "1. Rational expression evaluation\n";
        std::cout << "2. Taylor series table for ln(x)\n";
        std::cout << "3. Piecewise helper table\n";
        std::cout << "4. Recursive sums\n";
        std::cout << "5. Geometric progression\n";
        std::cout << "Write 0 for exit\n";
        std::cout << "Choice: ";

        int task = 0;
        if (!(std::cin >> task)) {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::string dummy;
            std::cin >> dummy;
            std::cout << "Invalid input. Please enter an integer.\n";
            continue;
        }

        if (task == 0) {
            return 0;
        }

        try {
            if (task == 1) {
                runExpressionTask();
            } else if (task == 2) {
                runTaylorTableTask();
            } else if (task == 3) {
                runHelperTableTask();
            } else if (task == 4) {
                runRecursiveSumsTask();
            } else if (task == 5) {
                runGeometricTask();
            } else {
                std::cout << "Invalid choice (max: 5)\n";
            }
        } catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
        }
    }
    return 0;
}
