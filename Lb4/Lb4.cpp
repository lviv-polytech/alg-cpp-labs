#include "Tasks.h"
#include "UI/TablePrinter.h"
#include "../Common/IO.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {

void runCycleSums() {
    std::cout << "\n=== Task 1: Cycles Sum ===\n";
    int n = 0;
    std::cout << "-> n: ";
    if (!Common::IO::read(std::cin, n)) return;
    const auto values = Lb4::cycleSums(n);
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i] << (i + 1 == values.size() ? '\n' : ' ');
    }
}

void runFormulaTabulation() {
    std::cout << "\n=== Task 2: Piecewise Formula Tabulation ===\n";
    double start = 0.0, end = 0.0, step = 0.0;
    std::cout << "-> start: ";
    if (!Common::IO::read(std::cin, start)) return;
    std::cout << "-> end: ";
    if (!Common::IO::read(std::cin, end)) return;
    std::cout << "-> step: ";
    if (!Common::IO::read(std::cin, step)) return;

    Lb4::UI::printPairHeader(std::cout, "y");
    for (const auto& [x, y] : Lb4::tabulateFormula(start, end, step)) {
        std::cout << "| " << std::setw(8) << x << " | " << std::setw(14) << y << " |\n";
    }
    Lb4::UI::printPairFooter(std::cout);
}

void runParametricTask() {
    std::cout << "\n=== Task 3: Parametric Function Tabulation ===\n";
    double a = 0.0, b = 0.0, c = 0.0, start = 0.0, end = 0.0, step = 0.0;
    std::cout << "-> a: ";
    if (!Common::IO::read(std::cin, a)) return;
    std::cout << "-> b: ";
    if (!Common::IO::read(std::cin, b)) return;
    std::cout << "-> c: ";
    if (!Common::IO::read(std::cin, c)) return;
    std::cout << "-> start: ";
    if (!Common::IO::read(std::cin, start)) return;
    std::cout << "-> end: ";
    if (!Common::IO::read(std::cin, end)) return;
    std::cout << "-> step: ";
    if (!Common::IO::read(std::cin, step)) return;

    Lb4::UI::printPairHeader(std::cout, "F(x)");
    for (const auto& [x, y] : Lb4::tabulateParametric(a, b, c, start, end, step)) {
        std::cout << "| " << std::setw(8) << x << " | ";
        if (y) {
            std::cout << std::setw(14) << *y;
        } else {
            std::cout << std::setw(14) << "undefined";
        }
        std::cout << " |\n";
    }
    Lb4::UI::printPairFooter(std::cout);
}

void runGraphTabulation() {
    std::cout << "\n=== Task 4: Graph Function Tabulation ===\n";
    double radius = 0.0, start = 0.0, end = 0.0, step = 0.0;
    std::cout << "-> radius: ";
    if (!Common::IO::read(std::cin, radius)) return;
    std::cout << "-> start: ";
    if (!Common::IO::read(std::cin, start)) return;
    std::cout << "-> end: ";
    if (!Common::IO::read(std::cin, end)) return;
    std::cout << "-> step: ";
    if (!Common::IO::read(std::cin, step)) return;

    Lb4::UI::printPairHeader(std::cout, "y");
    for (const auto& [x, y] : Lb4::tabulateGraph(radius, start, end, step)) {
        std::cout << "| " << std::setw(8) << x << " | " << std::setw(14) << y << " |\n";
    }
    Lb4::UI::printPairFooter(std::cout);
}

void runNestedSumsTask() {
    std::cout << "\n=== Task 5: Nested Loops Sum ===\n";
    std::cout << "Computing nested loop sum S = sum_{k=1}^{20} sqrt(sin^2(k) + |sum_{i=1}^k cos(i+k)|)...\n";
    std::cout << "(No additional input required)\n";
    const auto values = Lb4::nestedSums();
    const char* loopLabels[] = {"while-while", "do-while", "for (ascending)", "for (descending)"};
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << loopLabels[i] << ": " << values[i] << '\n';
    }
}

void runTaylorTableTask() {
    std::cout << "\n=== Task 6: Taylor Series Table for ln(x) ===\n";
    double start = 0.0, end = 0.0, step = 0.0, epsilon = 0.0;
    std::cout << "-> start (x > 0.5): ";
    if (!Common::IO::read(std::cin, start)) return;
    std::cout << "-> end: ";
    if (!Common::IO::read(std::cin, end)) return;
    std::cout << "-> step: ";
    if (!Common::IO::read(std::cin, step)) return;
    std::cout << "-> epsilon: ";
    if (!Common::IO::read(std::cin, epsilon)) return;

    Lb4::UI::printTaylorHeader(std::cout);
    for (const auto& [x, result] : Lb4::tabulateTaylor(start, end, step, epsilon)) {
        std::cout << "| " << std::setw(8) << x << " | ";
        if (x > 0.0) {
            std::cout << std::setw(14) << std::log(x);
        } else {
            std::cout << std::setw(14) << "undefined";
        }
        std::cout << " | ";
        if (result) {
            std::cout << std::setw(14) << result->sum << " | " << std::setw(10)
                      << result->terms << " |\n";
        } else {
            std::cout << std::setw(14) << "outside domain" << " | " << std::setw(10) << "-" << " |\n";
        }
    }
    Lb4::UI::printTaylorFooter(std::cout);
}

} // namespace

int main() {
    std::cout << std::fixed << std::setprecision(6);
    while (true) {
        std::cout << "\nAvailable tasks:\n";
        std::cout << "1. Cycles sum (four loop variants)\n";
        std::cout << "2. Piecewise formula table\n";
        std::cout << "3. Parametric function table\n";
        std::cout << "4. Graph function table\n";
        std::cout << "5. Nested loops sum\n";
        std::cout << "6. Taylor series table for ln(x)\n";
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
                runCycleSums();
            } else if (task == 2) {
                runFormulaTabulation();
            } else if (task == 3) {
                runParametricTask();
            } else if (task == 4) {
                runGraphTabulation();
            } else if (task == 5) {
                runNestedSumsTask();
            } else if (task == 6) {
                runTaylorTableTask();
            } else {
                std::cout << "Invalid choice (max: 6)\n";
            }
        } catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
        }
    }
    return 0;
}
