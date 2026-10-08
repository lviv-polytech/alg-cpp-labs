#pragma once

#include "../../Common/RecursionTracker.h"

#include <cstddef>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace Lb6::Task3 {

    namespace Iterative {
        /// <summary>
        /// Reads an array of integers iteratively from an input stream with prompt printing.
        /// </summary>
        void input(std::istream& in, std::ostream& out, int* values, std::size_t size);
    } // namespace Iterative

    namespace Recursive {
        /// <summary>
        /// Reads an array of integers recursively from an input stream with prompt printing.
        /// </summary>
        void input(std::istream& in, std::ostream& out, int* values, std::size_t size);
    } // namespace Recursive

    /// <summary>
    /// Generic iterative template function for array input with formatted prompts.
    /// </summary>
    template <typename T>
    void inputTemplate(std::istream& in, std::ostream& out, T* values, std::size_t size) {
        for (std::size_t i = 0; i < size; ++i) {
            out << "a[" << i << "] = ";
            if (!(in >> values[i])) throw std::runtime_error("Failed to read array element.");
        }
    }

    /// <summary>
    /// Generic recursive template function for array input with formatted prompts and recursion tracing.
    /// </summary>
    template <typename T>
    void inputTemplateRecursive(std::istream& in, std::ostream& out, T* values,
                                std::size_t size, std::size_t index = 0, int level = 0) {
        Common::Recursion::printStep(out, "inputTemplateRecursive", level, level + 1);
        if (index >= size) return;
        out << "a[" << index << "] = ";
        if (!(in >> values[index])) throw std::runtime_error("Failed to read array element.");
        inputTemplateRecursive(in, out, values, size, index + 1, level + 1);
    }

} // namespace Lb6::Task3
