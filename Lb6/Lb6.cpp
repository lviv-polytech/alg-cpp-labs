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
    std::cout << "\n=== Task 2: Largest Even Value Index (Variant 17) ===\n";
    std::size_t n = 0;
    std::cout << "-> array size n: ";
    if (!Common::IO::read(std::cin, n) || n == 0) return;
    std::vector<int> values(n);

    if (recursive) {
        std::cout << "[Recursive approach]\n";
        Common::Recursion::printSummary(std::cout, "maxEvenIndex (recursive)", static_cast<int>(n + 1));
        Lb6::Task2::initArrayRecursive(values, Lb6::Task2::DEFAULT_MIN_VAL, Lb6::Task2::DEFAULT_MAX_VAL, 0);
        std::cout << "Generated array:\n";
        Lb6::Task2::printArrayRecursive(std::cout, values, 0);
        const int index = Lb6::Task2::findMaxEvenIndexRecursive(values, 0, -1);
        if (index < 0) std::cout << "even elements not found\n";
        else std::cout << "largest even value index = " << index << " (value = " << values[index] << ")\n";
    } else {
        std::cout << "[Iterative approach]\n";
        Lb6::Task2::initArrayIterative(values, Lb6::Task2::DEFAULT_MIN_VAL, Lb6::Task2::DEFAULT_MAX_VAL);
        std::cout << "Generated array:\n";
        Lb6::Task2::printArrayIterative(std::cout, values);
        const int index = Lb6::Task2::findMaxEvenIndexIterative(values);
        if (index < 0) std::cout << "even elements not found\n";
        else std::cout << "largest even value index = " << index << " (value = " << values[index] << ")\n";
    }
}

void runInputFunctionsTask(const bool recursive) {
    std::cout << "\n=== Task 3: Array Input Functions ===\n";
    constexpr std::size_t size = 3;
    int integers[size]{};
    double reals[size]{};
    std::string words[size];
    if (recursive) {
        std::cout << "[Recursive approach]\n";
        Common::Recursion::printSummary(std::cout, "ArrayInput (recursive)", static_cast<int>(size + 1));
        std::cout << "Enter three integers:\n";
        Lb6::Task3::inputArrayRecursive(integers, size, 0, std::cin, &std::cout);
        std::cout << "Formatted integers:\n";
        Lb6::Task3::printArrayRecursive(integers, size, 0, std::cout);

        std::cout << "Enter three doubles:\n";
        Lb6::Task3::inputArrayRecursiveTemplate(reals, size, 0, std::cin, &std::cout);
        std::cout << "Formatted doubles:\n";
        Lb6::Task3::printArrayRecursiveTemplate(reals, size, 0, std::cout);

        std::cout << "Enter three strings:\n";
        Lb6::Task3::inputArrayRecursiveTemplate(words, size, 0, std::cin, &std::cout);
        std::cout << "Formatted strings:\n";
        Lb6::Task3::printArrayRecursiveTemplate(words, size, 0, std::cout);
    } else {
        std::cout << "[Iterative approach]\n";
        std::cout << "Enter three integers:\n";
        Lb6::Task3::inputArrayIterative(integers, size, std::cin, &std::cout);
        std::cout << "Formatted integers:\n";
        Lb6::Task3::printArrayIterative(integers, size, std::cout);

        std::cout << "Enter three doubles:\n";
        Lb6::Task3::inputArrayIterativeTemplate(reals, size, std::cin, &std::cout);
        std::cout << "Formatted doubles:\n";
        Lb6::Task3::printArrayIterativeTemplate(reals, size, std::cout);

        std::cout << "Enter three strings:\n";
        Lb6::Task3::inputArrayIterativeTemplate(words, size, std::cin, &std::cout);
        std::cout << "Formatted strings:\n";
        Lb6::Task3::printArrayIterativeTemplate(words, size, std::cout);
    }
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
