#include "TablePrinter.h"

#include <iomanip>

namespace Lb5::UI {

void printTwoColumnHeader(std::ostream& out, const char* valueLabel) {
    out << "+---------------+----------------+\n"
        << "| " << std::setw(13) << "x" << " | " << std::setw(14) << valueLabel << " |\n"
        << "+---------------+----------------+\n";
}

void printTwoColumnFooter(std::ostream& out) {
    out << "+---------------+----------------+\n";
}

void printTaylorHeader(std::ostream& out) {
    out << "+---------------+----------------+----------------+------------+\n"
        << "| " << std::setw(13) << "x" << " | " << std::setw(14) << "ln(x)"
        << " | " << std::setw(14) << "Taylor sum" << " | " << std::setw(10) << "terms" << " |\n"
        << "+---------------+----------------+----------------+------------+\n";
}

void printTaylorFooter(std::ostream& out) {
    out << "+---------------+----------------+----------------+------------+\n";
}

} // namespace Lb5::UI
