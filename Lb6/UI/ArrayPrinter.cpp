#include "ArrayPrinter.h"

#include <iomanip>

namespace Lb6::UI {

void printArray(std::ostream& out, const std::vector<int>& values) {
    for (int value : values) out << std::setw(4) << value;
    out << '\n';
}

void printArray(std::ostream& out, const std::vector<double>& values) {
    out << std::fixed << std::setprecision(2);
    for (double value : values) out << std::setw(8) << value;
    out << '\n';
}

} // namespace Lb6::UI
