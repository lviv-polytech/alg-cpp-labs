#include <iomanip>
#include <iostream>
#include <ostream>

#include "SevenTeen.h"

namespace {

    void runFirstTask() {
        bool isLoop = true;
        double x;

        std::cout << "Write 0 for exit" << std::endl;
        while (isLoop) {
            std::cout << "x = " << std::endl;
            std::cin >> x;

            if (x == 0) {
                isLoop = false;
                return;
            }
            std::cout << "\n=== Task 1 result ===" << std::fixed << std::setprecision(0) << SevenTeen::taskFirst(x) << std::endl;
        }
    }
} // namespace

int main() {
    runFirstTask();
    return 0;
}