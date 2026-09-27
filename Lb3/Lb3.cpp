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
            std::cin >> input;

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
    }
} // namespace

int main() {
    std::map<int, std::function<void()> > tasks;

    tasks[1] = runFirstTask;
    tasks[2] = runSecondTask;

    bool isLoop = true;
    int choice;
    while (isLoop) {
        std::cout << "Write 0 for exit" << std::endl;
        std::cin >> choice;

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
