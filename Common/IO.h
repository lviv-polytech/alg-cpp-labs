#pragma once

#include <iostream>
#include <limits>
#include <string>

namespace Common::IO {

    /// <summary>
    /// Safely attempts to read a value of type T from the input stream.
    /// In case of extraction failure, clears the error flags and discards the rest of the line.
    /// </summary>
    /// <typeparam name="T">The type of the value to extract.</typeparam>
    /// <param name="in">The input stream to read from.</param>
    /// <param name="value">The variable where extracted value will be stored.</param>
    /// <returns>True if extraction succeeded, false otherwise.</returns>
    template <typename T>
    bool read(std::istream& in, T& value) {
        if (in >> value) {
            return true;
        }
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    /// <summary>
    /// Prompts the user with a prompt message and reads a value of type T safely.
    /// </summary>
    /// <typeparam name="T">The type of the value to extract.</typeparam>
    /// <param name="in">The input stream to read from.</param>
    /// <param name="out">The output stream to display the prompt.</param>
    /// <param name="prompt">The prompt message to display.</param>
    /// <param name="value">The variable where the extracted value is stored.</param>
    /// <returns>True if extraction was successful; false otherwise.</returns>
    template <typename T>
    bool promptAndRead(std::istream& in, std::ostream& out, const std::string& prompt, T& value) {
        out << prompt;
        return read(in, value);
    }

    /// <summary>
    /// Repeatedly prompts the user and reads a value until input succeeds and passes validation predicate.
    /// </summary>
    /// <typeparam name="T">The type of value to read.</typeparam>
    /// <typeparam name="Predicate">Callable taking const T& and returning bool.</typeparam>
    /// <param name="in">The input stream.</param>
    /// <param name="out">The output stream.</param>
    /// <param name="prompt">The user prompt message.</param>
    /// <param name="validator">Validation function or lambda.</param>
    /// <param name="errorMessage">Error message to display upon invalid input.</param>
    /// <returns>The validated value.</returns>
    template <typename T, typename Predicate>
    T promptAndReadWithValidation(std::istream& in, std::ostream& out, const std::string& prompt,
                                  Predicate validator, const std::string& errorMessage) {
        while (true) {
            T value{};
            out << prompt;
            if (in >> value) {
                if (validator(value)) {
                    return value;
                }
            } else {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            out << errorMessage << '\n';
        }
    }

} // namespace Common::IO
