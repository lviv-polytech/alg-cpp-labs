#include "Tasks.h"

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    std::cout << "Lab 4 tasks (4.5 omitted: target region is unspecified).\n"
                 "1 cycles sum, 2 formula table, 3 parametric table, 4 graph table,\n"
                 "5 nested loops, 6 Taylor table\n";
    int task;
    if (!(std::cin >> task)) return 1;
    std::cout << std::fixed << std::setprecision(6);
    try {
        if (task == 1) {
            int n;
            std::cin >> n;
            const auto values = Lb4::cycleSums(n);
            for (std::size_t i = 0; i < values.size(); ++i)
                std::cout << values[i] << (i + 1 == values.size() ? '\n' : ' ');
        } else if (task == 2 || task == 4 || task == 6) {
            double start, end, step, epsilon = 0.0, radius = 0.0;
            if (task == 4) std::cin >> radius;
            std::cin >> start >> end >> step;
            if (task == 6) std::cin >> epsilon;
            if (task == 2) {
                for (const auto& [x, y] : Lb4::tabulateFormula(start, end, step))
                    std::cout << std::setw(8) << x << " | " << std::setw(14) << y << '\n';
            } else if (task == 4) {
                for (const auto& [x, y] : Lb4::tabulateGraph(radius, start, end, step))
                    std::cout << std::setw(8) << x << " | " << std::setw(14) << y << '\n';
            } else {
                for (const auto& [x, result] : Lb4::tabulateTaylor(start, end, step, epsilon)) {
                    std::cout << std::setw(8) << x << " | " << std::setw(14) << std::log(x) << " | ";
                    if (result) std::cout << std::setw(14) << result->sum << " | " << result->terms;
                    else std::cout << "outside convergence domain";
                    std::cout << '\n';
                }
            }
        } else if (task == 3) {
            double a, b, c, start, end, step;
            std::cin >> a >> b >> c >> start >> end >> step;
            for (const auto& [x, y] : Lb4::tabulateParametric(a, b, c, start, end, step)) {
                std::cout << std::setw(8) << x << " | ";
                if (y) std::cout << std::setw(14) << *y;
                else std::cout << "undefined";
                std::cout << '\n';
            }
        } else if (task == 5) {
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
