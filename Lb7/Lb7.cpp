#include "Tasks.h"
#include "Infrastructure/MatrixGenerator.h"
#include "UI/MatrixPrinter.h"
#include "../Common/IO.h"
#include "../Common/RecursionTracker.h"

#include <ctime>
#include <iostream>
#include <stdexcept>

namespace {

void runFilterAndSortTask() {
    std::cout << "\n=== Task 1: Matrix Filter and Row Sort ===\n";
    int method = 0;
    std::cout << "-> Method (0 for iterative, 1 for recursive): ";
    if (!Common::IO::read(std::cin, method) || (method != 0 && method != 1)) {
        std::cout << "Invalid method. Please enter 0 or 1.\n";
        return;
    }
    const bool recursive = (method == 1);

    auto matrix = Lb7::createIntMatrix(8, 5, static_cast<unsigned>(std::time(nullptr)));
    std::cout << "Original matrix (8x5):\n";
    Lb7::printMatrix(std::cout, matrix);
    if (recursive) {
        Common::Recursion::printSummary(std::cout, "Matrix Filter (count/sum/zero recursive)", 8 * 5 + 1);
    }
    std::cout << "Selected count = " << Lb7::countSelected(matrix, recursive)
              << ", sum = " << Lb7::sumSelected(matrix, recursive) << '\n';
    auto filtered = matrix;
    Lb7::zeroSelected(filtered, recursive);
    std::cout << "Filtered matrix (values not divisible by 6 set to 0):\n";
    Lb7::printMatrix(std::cout, filtered);
    if (recursive) {
        Common::Recursion::printSummary(std::cout, "sortRows (recursive)", 8 + 1);
    }
    Lb7::sortRows(matrix, recursive);
    std::cout << "Rows sorted by columns 1, 2, 4 (0-based: 0, 1, 3):\n";
    Lb7::printMatrix(std::cout, matrix);
}

void runPairedRowSwapTask() {
    std::cout << "\n=== Task 2: Paired Row Extrema Swap ===\n";
    std::size_t rows = 0, columns = 0;
    std::cout << "-> rows: ";
    if (!Common::IO::read(std::cin, rows)) return;
    std::cout << "-> columns: ";
    if (!Common::IO::read(std::cin, columns)) return;

    auto matrix = Lb7::createIntMatrix(rows, columns, static_cast<unsigned>(std::time(nullptr)));
    std::cout << "Original matrix:\n";
    Lb7::printMatrix(std::cout, matrix);
    Lb7::processMatrixPairs(matrix);
    std::cout << "After paired swaps (min of row 2k swapped with max of row 2k+1):\n";
    Lb7::printMatrix(std::cout, matrix);
}

void runDiagonalLargestTask() {
    std::cout << "\n=== Task 3: Largest Diagonal Elements ===\n";
    std::size_t size = 0;
    int method = 0;
    std::cout << "-> matrix size (N x N): ";
    if (!Common::IO::read(std::cin, size)) return;
    std::cout << "-> Method (0 for iterative, 1 for recursive): ";
    if (!Common::IO::read(std::cin, method) || (method != 0 && method != 1)) {
        std::cout << "Invalid method. Please enter 0 or 1.\n";
        return;
    }
    const bool recursive = (method == 1);

    auto matrix = Lb7::createRealMatrix(size, static_cast<unsigned>(std::time(nullptr)));
    const auto original = matrix;
    std::cout << "Original matrix:\n";
    Lb7::printMatrix(std::cout, original);
    if (recursive) {
        Common::Recursion::printSummary(std::cout, "firstRowWithoutPositive (recursive)", static_cast<int>(size + 1));
    }
    const int row = Lb7::firstRowWithoutPositive(original, recursive);
    if (row < 0) {
        std::cout << "No row without positive elements.\n";
    } else {
        std::cout << "First row without positive elements (zero-based) = " << row << '\n';
    }
    if (recursive) {
        Common::Recursion::printSummary(std::cout, "diagonalLargest (recursive)", static_cast<int>(size + 1));
    }
    Lb7::diagonalLargest(matrix, recursive);
    std::cout << "Matrix with largest values placed on main diagonal in descending order:\n";
    Lb7::printMatrix(std::cout, matrix);
}

} // namespace

int main() {
    while (true) {
        std::cout << "\nAvailable tasks:\n";
        std::cout << "1. Matrix filter and row sort\n";
        std::cout << "2. Paired row extrema swap\n";
        std::cout << "3. Largest values on diagonal\n";
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
                runFilterAndSortTask();
            } else if (task == 2) {
                runPairedRowSwapTask();
            } else if (task == 3) {
                runDiagonalLargestTask();
            } else {
                std::cout << "Invalid choice (max: 3)\n";
            }
        } catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
        }
    }
    return 0;
}
