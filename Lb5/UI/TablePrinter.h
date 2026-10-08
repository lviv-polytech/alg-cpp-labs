#pragma once

#include <iostream>

namespace Lb5::UI {

    /// <summary>
    /// Prints a two-column formatted table header for coordinates (x, valueLabel).
    /// </summary>
    /// <param name="out">Output stream.</param>
    /// <param name="valueLabel">Column title for the calculated values.</param>
    void printTwoColumnHeader(std::ostream& out, const char* valueLabel);

    /// <summary>
    /// Prints a two-column formatted table footer border.
    /// </summary>
    /// <param name="out">Output stream.</param>
    void printTwoColumnFooter(std::ostream& out);

    /// <summary>
    /// Prints the header for Taylor series tabulation table.
    /// </summary>
    /// <param name="out">Output stream.</param>
    void printTaylorHeader(std::ostream& out);

    /// <summary>
    /// Prints the footer border for Taylor series tabulation table.
    /// </summary>
    /// <param name="out">Output stream.</param>
    void printTaylorFooter(std::ostream& out);

} // namespace Lb5::UI
