#include "TablePrinter.h"

#include <iomanip>

namespace Lb4::UI {

void printPairHeader(std::ostream& out, const char* valueLabel) {
    out << "+----------+----------------+\n"
        << "| Function Tabulation Table |\n"
        << "+----------+----------------+\n"
        << "| " << std::setw(8) << "x" << " | " << std::setw(14) << valueLabel << " |\n"
        << "+----------+----------------+\n";
}

void printPairFooter(std::ostream& out) {
    out << "+----------+----------------+\n";
}

void printTaylorHeader(std::ostream& out) {
    out << "+----------+----------------+----------------+------------+\n"
        << "|     Taylor Series Tabulation for ln(x) (Variant 17)     |\n"
        << "+----------+----------------+----------------+------------+\n"
        << "| " << std::setw(8) << "x" << " | " << std::setw(14) << "ln(x)"
        << " | " << std::setw(14) << "Taylor sum" << " | " << std::setw(10) << "terms" << " |\n"
        << "+----------+----------------+----------------+------------+\n";
}

void printTaylorFooter(std::ostream& out) {
    out << "+----------+----------------+----------------+------------+\n";
}

} // namespace Lb4::UI
