#include "Tasks.h"
#include "UI/TablePrinter.h"
#include "../Common/IO.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {

void runExpressionTask() {
    double a = 0.0, b = 0.0;
    std::cout << "-> a b: ";
    std::cin >> a >> b;
    std::cout << "R = " << Lb5::expression(a, b) << '\n';
}

void runTaylorTableTask() {
    double start = 0.0, end = 0.0, step = 0.0, epsilon = 0.0;
    std::cout << "-> start end step epsilon: ";
    std::cin >> start >> end >> step >> epsilon;
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
    double start = 0.0, end = 0.0;
    int n = 0;
    std::cout << "-> start end n: ";
    std::cin >> start >> end >> n;
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
    int n = 0;
    std::cout << "-> n: ";
    std::cin >> n;
    const auto values = Lb5::recursiveSums(n);
    const char* labels[] = {"iter", "rec up ++", "rec up --", "rec down ++", "rec down --"};
    for (int i = 0; i < 5; ++i) {
        std::cout << labels[i] << ": " << values[i] << '\n';
    }
}

void runGeometricTask() {
    double first = 0.0, ratio = 0.0;
    int n = 0;
    std::cout << "-> first ratio n: ";
    std::cin >> first >> ratio >> n;
    const auto result = Lb5::geometric(first, ratio, n);
    std::cout << "b_n = " << result.term << "\nS_n = " << result.sum
              << "\nterm depth = " << result.termDepth << "\nsum depth = " << result.sumDepth << '\n';
}

} // namespace

int main() {
    std::cout << "Lab 5: 1 expression, 2 Taylor table, 3 helper table, 4 recursive sums, 5 geometric series\n";
    std::cout << "-> Select task: ";
    int task;
    if (!Common::IO::read(std::cin, task)) {
        return 1;
    }
    std::cout << std::fixed << std::setprecision(8);
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
            std::cerr << "Unknown task.\n";
            return 1;
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
