#include "MatrixPrinter.h"

#include <iomanip>

namespace Lb7::UI {

void printMatrix(std::ostream& out, const IntMatrix& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) out << std::setw(4) << value;
        out << '\n';
    }
}

void printMatrix(std::ostream& out, const RealMatrix& matrix) {
    out << std::fixed << std::setprecision(2);
    for (const auto& row : matrix) {
        for (double value : row) out << std::setw(8) << value;
        out << '\n';
    }
}

} // namespace Lb7::UI
