#include "Tasks.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
void printPairHeader(const char* valueLabel) {
    std::cout << "+----------+----------------+\n"
              << "| " << std::setw(8) << "x" << " | " << std::setw(14) << valueLabel << " |\n"
              << "+----------+----------------+\n";
}
void printPairFooter() { std::cout << "+----------+----------------+\n"; }
void printTaylorHeader() {
    std::cout << "+----------+----------------+----------------+------------+\n"
              << "| " << std::setw(8) << "x" << " | " << std::setw(14) << "ln(x)"
              << " | " << std::setw(14) << "Taylor sum" << " | " << std::setw(10) << "terms" << " |\n"
              << "+----------+----------------+----------------+------------+\n";
}
void printTaylorFooter() {
    std::cout << "+----------+----------------+----------------+------------+\n";
}
}

int main() {
    std::cout << "Lab 4 tasks (4.5 omitted: target region is unspecified).\n"
                 "1 cycles sum, 2 formula table, 3 parametric table, 4 graph table,\n"
                 "5 nested loops, 6 Taylor table\n";
    std::cout << "-> Select task: ";
    int task;
    if (!(std::cin >> task)) return 1;
    std::cout << std::fixed << std::setprecision(6);
    try {
        // Task 1: sums for four loop variants.
        if (task == 1) {
            int n;
            std::cout << "-> n: ";
            std::cin >> n;
            const auto values = Lb4::cycleSums(n);
            for (std::size_t i = 0; i < values.size(); ++i)
                std::cout << values[i] << (i + 1 == values.size() ? '\n' : ' ');
        // Task 2/4/6: build tables for formula, graph, and Taylor series.
        } else if (task == 2 || task == 4 || task == 6) {
            double start, end, step, epsilon = 0.0, radius = 0.0;
            if (task == 4) {
                std::cout << "-> radius: ";
                std::cin >> radius;
            }
            std::cout << "-> start end step: ";
            std::cin >> start >> end >> step;
            if (task == 6) {
                std::cout << "-> epsilon: ";
                std::cin >> epsilon;
            }
            if (task == 2) {
                printPairHeader("y");
                for (const auto& [x, y] : Lb4::tabulateFormula(start, end, step))
                    std::cout << "| " << std::setw(8) << x << " | " << std::setw(14) << y << " |\n";
                printPairFooter();
            } else if (task == 4) {
                printPairHeader("y");
                for (const auto& [x, y] : Lb4::tabulateGraph(radius, start, end, step))
                    std::cout << "| " << std::setw(8) << x << " | " << std::setw(14) << y << " |\n";
                printPairFooter();
            } else {
                printTaylorHeader();
                for (const auto& [x, result] : Lb4::tabulateTaylor(start, end, step, epsilon)) {
                    std::cout << "| " << std::setw(8) << x << " | ";
                    if (x > 0.0) std::cout << std::setw(14) << std::log(x);
                    else std::cout << std::setw(14) << "undefined";
                    std::cout << " | ";
                    if (result)
                        std::cout << std::setw(14) << result->sum << " | " << std::setw(10)
                                  << result->terms << " |\n";
                    else std::cout << std::setw(14) << "outside domain" << " | " << std::setw(10) << "-" << " |\n";
                }
                printTaylorFooter();
            }
        // Task 3: parametric function values over a range.
        } else if (task == 3) {
            double a, b, c, start, end, step;
            std::cout << "-> a b c start end step: ";
            std::cin >> a >> b >> c >> start >> end >> step;
            printPairHeader("F(x)");
            for (const auto& [x, y] : Lb4::tabulateParametric(a, b, c, start, end, step)) {
                std::cout << "| " << std::setw(8) << x << " | ";
                if (y) std::cout << std::setw(14) << *y;
                else std::cout << std::setw(14) << "undefined";
                std::cout << " |\n";
            }
            printPairFooter();
        // Task 5: nested loop sums.
        } else if (task == 5) {
            std::cout << "-> no extra input required\n";
            for (double value : Lb4::nestedSums()) std::cout << value << '\n';
        } else {
            std::cerr << "Unknown task.\n";
            return 1;
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
