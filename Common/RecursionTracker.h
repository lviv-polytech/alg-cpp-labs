#pragma once

#include <iostream>
#include <string>

namespace Common::Recursion {

    /// <summary>
    /// Prints formatted recursion level and depth information for an active recursive call.
    /// Visual indentation corresponds to current recursion level.
    /// </summary>
    /// <param name="out">The output stream.</param>
    /// <param name="functionName">Name of the recursive function.</param>
    /// <param name="level">0-based recursion level (number of active calls in stack above root).</param>
    /// <param name="depth">Current call depth (level + 1).</param>
    inline void printStep(std::ostream& out, const char* functionName, const int level, const int depth) {
        if (level < 60) {
            const std::string indent(static_cast<std::size_t>(level * 2), ' ');
            out << indent << "[Recursion: " << functionName << "] Level = " << level
                << ", Depth = " << depth << '\n';
        } else if (level == 60) {
            out << "  [Recursion: " << functionName << "] ... (further recursive steps omitted for brevity)\n";
        }
    }

    /// <summary>
    /// Prints a formatted summary block displaying the total recursion depth and level range.
    /// </summary>
    /// <param name="out">The output stream.</param>
    /// <param name="functionName">Name of the recursive function/operation.</param>
    /// <param name="totalDepth">The maximum recursion depth reached.</param>
    inline void printSummary(std::ostream& out, const char* functionName, const int totalDepth) {
        out << "+--------------------------------------------------+\n"
            << "| Recursion: " << functionName << '\n'
            << "| Total Depth: " << totalDepth << '\n'
            << "| Level Range: [0 .. " << (totalDepth > 0 ? totalDepth - 1 : 0) << "]\n"
            << "+--------------------------------------------------+\n";
    }

} // namespace Common::Recursion
