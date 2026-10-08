#pragma once

#include <iostream>

namespace Lb4::UI {

    /// <summary>
    /// Prints a two-column formatted table header for coordinates (x, valueLabel).
    /// </summary>
    /// <param name="out">The output stream.</param>
    /// <param name="valueLabel">Column title for the calculated value.</param>
    void printPairHeader(std::ostream& out, const char* valueLabel);

    /// <summary>
    /// Prints the table footer border for two-column tables.
    /// </summary>
    /// <param name="out">The output stream.</param>
    void printPairFooter(std::ostream& out);

    /// <summary>
    /// Prints the formatted table header for Taylor series approximation comparison.
    /// </summary>
    /// <param name="out">The output stream.</param>
    void printTaylorHeader(std::ostream& out);

    /// <summary>
    /// Prints the table footer border for Taylor series comparison table.
    /// </summary>
    /// <param name="out">The output stream.</param>
    void printTaylorFooter(std::ostream& out);

} // namespace Lb4::UI
