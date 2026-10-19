#include "TablePrinter.h"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

namespace Lb5::UI {
namespace {

std::string formatDouble(const double value, const int width, const int precision = 6) {
    std::ostringstream oss;
    if (std::fabs(value) >= 1e6 || (std::fabs(value) > 0.0 && std::fabs(value) < 1e-4)) {
        oss << std::scientific << std::setprecision(4) << value;
    } else {
        oss << std::fixed << std::setprecision(precision) << value;
    }
    std::string str = oss.str();
    if (static_cast<int>(str.size()) > width) {
        std::ostringstream fallback;
        fallback << std::scientific << std::setprecision(3) << value;
        str = fallback.str();
    }
    return str;
}

} // namespace

void printTwoColumnHeader(std::ostream& out, const char* valueLabel) {
    out << "+--------------------------------+\n"
        << "| " << std::left << std::setw(30) << "Function Tabulation Table" << std::right << " |\n"
        << "+---------------+----------------+\n"
        << "| " << std::setw(13) << "x" << " | " << std::setw(14) << valueLabel << " |\n"
        << "+---------------+----------------+\n";
}

void printTwoColumnRow(std::ostream& out, const double x, const std::optional<double> value) {
    out << "| " << std::setw(13) << formatDouble(x, 13, 6) << " | ";
    if (value) {
        out << std::setw(14) << formatDouble(*value, 14, 6);
    } else {
        out << std::setw(14) << "undefined";
    }
    out << " |\n";
}

void printTwoColumnFooter(std::ostream& out) {
    out << "+---------------+----------------+\n";
}

void printTaylorHeader(std::ostream& out) {
    out << "+--------------------------------------------------------------+\n"
        << "| " << std::left << std::setw(60) << "Taylor Series Tabulation for ln(x) (Variant 17)" << std::right << " |\n"
        << "+---------------+----------------+----------------+------------+\n"
        << "| " << std::setw(13) << "x" << " | " << std::setw(14) << "ln(x)"
        << " | " << std::setw(14) << "Taylor sum" << " | " << std::setw(10) << "terms" << " |\n"
        << "+---------------+----------------+----------------+------------+\n";
}

void printTaylorRow(std::ostream& out, const double x, const std::optional<TaylorResult> result) {
    out << "| " << std::setw(13) << formatDouble(x, 13, 6) << " | ";
    if (x > 0.0) {
        out << std::setw(14) << formatDouble(std::log(x), 14, 6);
    } else {
        out << std::setw(14) << "undefined";
    }
    out << " | ";
    if (result) {
        out << std::setw(14) << formatDouble(result->sum, 14, 6)
            << " | " << std::setw(10) << result->terms << " |\n";
    } else {
        out << std::setw(14) << "outside domain"
            << " | " << std::setw(10) << "-" << " |\n";
    }
}

void printTaylorFooter(std::ostream& out) {
    out << "+---------------+----------------+----------------+------------+\n";
}

} // namespace Lb5::UI
