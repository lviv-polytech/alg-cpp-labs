#include "Tasks.h"
#include "Infrastructure/ArrayGenerator.h"
#include "UI/ArrayPrinter.h"
#include "../Common/IO.h"
#include "../Common/RecursionTracker.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

namespace {

void runSelectedArrayTask(const bool recursive) {
    std::cout << "\n=== Task 1: Selected Array Processing (Variant 17) ===\n";
    std::vector<int> values(Lb6::Task1::SELECTION_SIZE);
    if (recursive) {
        std::cout << "[Recursive approach]\n";
        Common::Recursion::printSummary(std::cout, "ArraySelection (recursive)", 26);
        Lb6::Task1::generateArrayRec(values, Lb6::Task1::DEFAULT_LOW, Lb6::Task1::DEFAULT_HIGH, 0);
        std::cout << "Original array:\n";
        Lb6::Task1::printArrayRec(std::cout, values, 0);

        const int count = Lb6::Task1::countElementsRec(values, 0);
        const int sum = Lb6::Task1::sumElementsRec(values, 0);
        Lb6::Task1::zeroElementsRec(values, 0);

        std::cout << "Count = " << count << ", Sum = " << sum << '\n';
        std::cout << "Modified array (selected elements replaced by 0):\n";
        Lb6::Task1::printArrayRec(std::cout, values, 0);
    } else {
        std::cout << "[Iterative approach]\n";
        Lb6::Task1::generateArray(values, Lb6::Task1::DEFAULT_LOW, Lb6::Task1::DEFAULT_HIGH);
        std::cout << "Original array:\n";
        Lb6::Task1::printArray(std::cout, values);

        const int count = Lb6::Task1::countElements(values);
        const int sum = Lb6::Task1::sumElements(values);
        Lb6::Task1::zeroElements(values);

        std::cout << "Count = " << count << ", Sum = " << sum << '\n';
        std::cout << "Modified array (selected elements replaced by 0):\n";
        Lb6::Task1::printArray(std::cout, values);
    }
}

void runMaxEvenIndexTask(const bool recursive) {
    std::cout << "\n=== Task 2: Largest Even Value Index ===\n";
    std::size_t n = 0;
    std::cout << "-> array size n: ";
    if (!Common::IO::read(std::cin, n)) return;
    std::mt19937 engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(-50, 50);
    std::vector<int> values(n);
    for (int& value : values) value = distribution(engine);
    std::cout << "Generated array:\n";
    Lb6::printArray(std::cout, values);
    if (recursive) {
        Common::Recursion::printSummary(std::cout, "maxEvenIndex (recursive)", static_cast<int>(n + 1));
    }
    const int index = Lb6::maxEvenIndex(values, recursive);
    if (index < 0) std::cout << "even elements not found\n";
    else std::cout << "largest even value index = " << index << " (value = " << values[index] << ")\n";
}

void runInputFunctionsTask(const bool recursive) {
    std::cout << "\n=== Task 3: Array Input Functions ===\n";
    constexpr std::size_t size = 3;
    int integers[size]{};
    double reals[size]{};
    std::string words[size];
    if (recursive) {
        Common::Recursion::printSummary(std::cout, "ArrayInput (recursive)", static_cast<int>(size + 1));
    }
    std::cout << "Enter three integers:\n";
    if (recursive) Lb6::Recursive::input(std::cin, std::cout, integers, size);
    else Lb6::Iterative::input(std::cin, std::cout, integers, size);
    std::cout << "Enter three doubles:\n";
    if (recursive) Lb6::inputTemplateRecursive(std::cin, std::cout, reals, size);
    else Lb6::inputTemplate(std::cin, std::cout, reals, size);
    std::cout << "Enter three strings:\n";
    if (recursive) Lb6::inputTemplateRecursive(std::cin, std::cout, words, size);
    else Lb6::inputTemplate(std::cin, std::cout, words, size);
    std::cout << "int: ";
    for (int value : integers) std::cout << value << ' ';
    std::cout << "\ndouble: " << std::fixed << std::setprecision(2);
    for (double value : reals) std::cout << value << ' ';
    std::cout << "\nstring: ";
    for (const auto& value : words) std::cout << value << ' ';
    std::cout << '\n';
}

void runDynamicArrayTask(const bool recursive) {
    std::cout << "\n=== Task 4: Dynamic Array Operations ===\n";
    std::size_t n = 0;
    std::cout << "-> array size n: ";
    if (!Common::IO::read(std::cin, n)) return;
    if (n == 0) throw std::invalid_argument("Array size must be positive.");
    std::mt19937 engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(-20, 20);
    std::vector<double> values(n);
    for (double& value : values) value = distribution(engine) / 2.0;
    std::cout << "Original array:\n";
    Lb6::printArray(std::cout, values);
    if (recursive) {
        Common::Recursion::printSummary(std::cout, "DynamicArrayOperations (recursive)", static_cast<int>(n + 1));
    }
    std::cout << "positive count = " << Lb6::Dynamic::countPositive(values, recursive) << '\n';
    const int lastZero = Lb6::Dynamic::lastZeroIndex(values, recursive);
    if (lastZero < 0) std::cout << "no zero elements; sum is undefined\n";
    else std::cout << "sum after last zero = "
                   << Lb6::Dynamic::sumAfter(values, lastZero, recursive) << '\n';
    Lb6::Dynamic::stablePartition(values, recursive);
    std::cout << "Array after stable partition (< 2 before >= 2):\n";
    Lb6::printArray(std::cout, values);
}

} // namespace

int main() {
    while (true) {
        std::cout << "\nAvailable tasks:\n";
        std::cout << "1. Selected array processing\n";
        std::cout << "2. Largest even value index\n";
        std::cout << "3. Array input functions\n";
        std::cout << "4. Dynamic array operations\n";
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

        if (task < 1 || task > 4) {
            std::cout << "Invalid choice (max: 4)\n";
            continue;
        }

        int method = 0;
        std::cout << "-> Method (0 for iterative, 1 for recursive): ";
        if (!Common::IO::read(std::cin, method) || (method != 0 && method != 1)) {
            std::cout << "Invalid method. Please enter 0 or 1.\n";
            continue;
        }
        const bool recursive = (method == 1);

        try {
            if (task == 1) {
                runSelectedArrayTask(recursive);
            } else if (task == 2) {
                runMaxEvenIndexTask(recursive);
            } else if (task == 3) {
                runInputFunctionsTask(recursive);
            } else if (task == 4) {
                runDynamicArrayTask(recursive);
            }
        } catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
        }
    }
    return 0;
}
