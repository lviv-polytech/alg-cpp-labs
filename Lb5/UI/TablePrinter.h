#pragma once

#include <iostream>
#include <optional>
#include "../Tasks.h"

namespace Lb5::UI {

    /**
     * @brief Prints a two-column formatted table title and header for coordinates (x, valueLabel).
     */
    void printTwoColumnHeader(std::ostream& out, const char* valueLabel);

    /**
     * @brief Prints a single row of a two-column table without breaking column borders.
     */
    void printTwoColumnRow(std::ostream& out, double x, std::optional<double> value);

    /**
     * @brief Prints a two-column formatted table footer border.
     */
    void printTwoColumnFooter(std::ostream& out);

    /**
     * @brief Prints the title and column header for Taylor series tabulation table.
     */
    void printTaylorHeader(std::ostream& out);

    /**
     * @brief Prints a single row of the Taylor series table without breaking column borders.
     */
    void printTaylorRow(std::ostream& out, double x, std::optional<TaylorResult> result);

    /**
     * @brief Prints the footer border for Taylor series tabulation table.
     */
    void printTaylorFooter(std::ostream& out);

} // namespace Lb5::UI
