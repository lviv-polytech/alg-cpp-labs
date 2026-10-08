#include "Tasks.h"
#include "Infrastructure/MatrixGenerator.h"
#include "UI/MatrixPrinter.h"
#include "../Common/IO.h"

#include <ctime>
#include <iostream>
#include <stdexcept>

namespace {

void runFilterAndSortTask() {
    int recursive = 0;
    std::cout << "-> recursive flag (0/1): ";
    std::cin >> recursive;
    auto matrix = Lb7::createIntMatrix(8, 5, static_cast<unsigned>(std::time(nullptr)));
    std::cout << "Original matrix:\n";
    Lb7::printMatrix(std::cout, matrix);
    std::cout << "Selected count = " << Lb7::countSelected(matrix, recursive != 0)
              << ", sum = " << Lb7::sumSelected(matrix, recursive != 0) << '\n';
    auto filtered = matrix;
    Lb7::zeroSelected(filtered, recursive != 0);
    std::cout << "Filtered matrix:\n";
    Lb7::printMatrix(std::cout, filtered);
    Lb7::sortRows(matrix, recursive != 0);
    std::cout << "Rows sorted by columns 1, 2, 4:\n";
    Lb7::printMatrix(std::cout, matrix);
}

void runPairedRowSwapTask() {
    std::size_t rows = 0, columns = 0;
    std::cout << "-> rows columns: ";
    std::cin >> rows >> columns;
    auto matrix = Lb7::createIntMatrix(rows, columns, static_cast<unsigned>(std::time(nullptr)));
    std::cout << "Original matrix:\n";
    Lb7::printMatrix(std::cout, matrix);
    Lb7::processMatrixPairs(matrix);
    std::cout << "After paired swaps:\n";
    Lb7::printMatrix(std::cout, matrix);
}

void runDiagonalLargestTask() {
    std::size_t size = 0;
    int method = 0;
    std::cout << "-> size method (0/1): ";
    std::cin >> size >> method;
    if (method != 0 && method != 1) throw std::invalid_argument("Method must be 0 or 1.");
    auto matrix = Lb7::createRealMatrix(size, static_cast<unsigned>(std::time(nullptr)));
    const auto original = matrix;
    std::cout << "Original matrix:\n";
    Lb7::printMatrix(std::cout, original);
    const int row = Lb7::firstRowWithoutPositive(original, method != 0);
    if (row < 0) std::cout << "No row without positive elements.\n";
    else std::cout << "First row without positive elements (zero-based) = " << row << '\n';
    Lb7::diagonalLargest(matrix, method != 0);
    std::cout << "Matrix with largest values on diagonal:\n";
    Lb7::printMatrix(std::cout, matrix);
}

} // namespace

int main() {
    std::cout << "Lab 7: 1 matrix filter and row sort, 2 paired row swap, 3 largest diagonal\n";
    std::cout << "-> Select task: ";
    int task;
    if (!Common::IO::read(std::cin, task)) return 1;
    try {
        if (task == 1) {
            runFilterAndSortTask();
        } else if (task == 2) {
            runPairedRowSwapTask();
        } else if (task == 3) {
            runDiagonalLargestTask();
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
