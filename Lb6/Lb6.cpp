#include "Tasks.h"
#include "Infrastructure/ArrayGenerator.h"
#include "UI/ArrayPrinter.h"
#include "../Common/IO.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

namespace {

void runSelectedArrayTask(const bool recursive) {
    auto values = Lb6::createArray(static_cast<unsigned>(std::time(nullptr)));
    Lb6::printArray(std::cout, values);
    const auto result = Lb6::processSelection(values, recursive);
    std::cout << "count = " << result.count << ", sum = " << result.sum << '\n';
    Lb6::printArray(std::cout, values);
}

void runMaxEvenIndexTask(const bool recursive) {
    std::size_t n = 0;
    std::cout << "-> n: ";
    std::cin >> n;
    std::mt19937 engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(-50, 50);
    std::vector<int> values(n);
    for (int& value : values) value = distribution(engine);
    Lb6::printArray(std::cout, values);
    const int index = Lb6::maxEvenIndex(values, recursive);
    if (index < 0) std::cout << "even elements not found\n";
    else std::cout << "largest even value index = " << index << '\n';
}

void runInputFunctionsTask(const bool recursive) {
    constexpr std::size_t size = 3;
    int integers[size]{};
    double reals[size]{};
    std::string words[size];
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
    std::size_t n = 0;
    std::cout << "-> n: ";
    std::cin >> n;
    if (n == 0) throw std::invalid_argument("Array size must be positive.");
    std::mt19937 engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(-20, 20);
    std::vector<double> values(n);
    for (double& value : values) value = distribution(engine) / 2.0;
    Lb6::printArray(std::cout, values);
    std::cout << "positive count = " << Lb6::Dynamic::countPositive(values, recursive) << '\n';
    const int lastZero = Lb6::Dynamic::lastZeroIndex(values, recursive);
    if (lastZero < 0) std::cout << "no zero elements; sum is undefined\n";
    else std::cout << "sum after last zero = "
                   << Lb6::Dynamic::sumAfter(values, lastZero, recursive) << '\n';
    Lb6::Dynamic::stablePartition(values, recursive);
    Lb6::printArray(std::cout, values);
}

} // namespace

int main() {
    std::cout << "Lab 6: 1 selected array, 2 max even index, 3 input functions, 4 dynamic array\n";
    std::cout << "-> Select task: ";
    int task, method;
    if (!Common::IO::read(std::cin, task)) return 1;
    try {
        std::cout << "-> Method (0 iterative, 1 recursive): ";
        if (!Common::IO::read(std::cin, method) || (method != 0 && method != 1)) return 1;
        const bool recursive = method == 1;

        if (task == 1) {
            runSelectedArrayTask(recursive);
        } else if (task == 2) {
            runMaxEvenIndexTask(recursive);
        } else if (task == 3) {
            runInputFunctionsTask(recursive);
        } else if (task == 4) {
            runDynamicArrayTask(recursive);
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
