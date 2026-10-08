#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <vector>

#include "SevenTeen.h"

namespace {
    void varsLoop(const std::vector<std::string> &prompts,
                  const std::vector<std::reference_wrapper<double> > &targets) {
        if (prompts.size() != targets.size()) {
            std::cerr << "Error: prompts and targets size mismatch!\n";
            return;
        }

        for (size_t i = 0; i < targets.size(); ++i) {
            std::cout << prompts[i];
            double input;
            while (!(std::cin >> input)) {
                std::cin.clear();
                std::string dummy;
                std::cin >> dummy;
                std::cout << "Invalid input. Please enter a number for " << prompts[i];
            }

            targets[i].get() = input;
        }
    }

    void runFirstTask() {
        std::cout << "\n=== First Task ===" << std::endl;
        double x;
        varsLoop({"x = "}, {std::ref(x)});
        SevenTeen::taskFirst(x);
    }

    void runSecondTask() {
        std::cout << "\n=== Second Task ===" << std::endl;
        double a;
        double b;
        double c;
        double x;
        varsLoop({"a = ", "b = ", "c = ", "x = "}, {std::ref(a), std::ref(b), std::ref(c), std::ref(x)});
        const double result = SevenTeen::taskSecond(a, b, c, x);
        std::cout << "Result = " << std::fixed << std::setprecision(10) << result << std::endl;
    }

    void runThirdTask() {
        std::cout << "\n=== Third Task (Variant 17) ===" << std::endl;
        double x;
        double R;
        varsLoop({"x = ", "R = "}, {std::ref(x), std::ref(R)});
        const double y = SevenTeen::taskThird(x, R);
        std::cout << "y = " << std::fixed << std::setprecision(10) << y << std::endl;
    }

    void runFourthTask() {
        std::cout << "\n=== Fourth Task (Point in Shaded Region) ===" << std::endl;
        double x;
        double y;
        double R;

        varsLoop({"x = ", "y = "}, {std::ref(x), std::ref(y)});

        while (true) {
            varsLoop({"R = "}, {std::ref(R)});
            if (R > 0.0) {
                break;
            }
            std::cout << "Error: Radius R must be positive (R > 0). Please try again.\n";
        }

        const bool inside = SevenTeen::taskFourth(x, y, R);
        if (inside) {
            std::cout << "Result: Point (" << x << ", " << y << ") is INSIDE the shaded region (R = "
                      << R << ")." << std::endl;
        } else {
            std::cout << "Result: Point (" << x << ", " << y << ") is OUTSIDE the shaded region (R = "
                      << R << ")." << std::endl;
        }
    }
} // namespace

int main() {
    std::map<int, std::function<void()> > tasks;

    tasks[1] = runFirstTask;
    tasks[2] = runSecondTask;
    tasks[3] = runThirdTask;
    tasks[4] = runFourthTask;

    bool isLoop = true;
    int choice;
    while (isLoop) {
        std::cout << "\nAvailable tasks:" << std::endl;
        std::cout << "1. Function one variable" << std::endl;
        std::cout << "2. Function with params" << std::endl;
        std::cout << "3. Chart function" << std::endl;
        std::cout << "4. Check if point is in shaded region" << std::endl;
        std::cout << "Write 0 for exit" << std::endl;
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string dummy;
            std::cin >> dummy;
            std::cout << "Invalid input. Please enter an integer.\n";
            continue;
        }

        if (choice == 0) {
            isLoop = false;
            return 0;
        }
        if (tasks.find(choice) == tasks.end()) {
            std::cout << "Invalid choice (max: " << tasks.size() << ")" << std::endl;
            continue;
        }
        tasks[choice]();
    }

    return 0;
}
