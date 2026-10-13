#pragma once

namespace Task2::Expression {

    /// <summary>
    /// Parameters container for Task 2 mathematical function evaluation.
    /// </summary>
    struct Params {
        const double a, b, c, x;

        Params(double a, double b, double c, double x)
            : a(a), b(b), c(c), x(x) {}
    };

    /// <summary>
    /// Computes function F using Method 1 (short form, only 'if' without 'else').
    /// Throws std::runtime_error upon division by zero.
    /// </summary>
    /// <param name="params">The calculation parameters a, b, c, x.</param>
    /// <returns>Evaluated value of F.</returns>
    double calcShort(const Params& params);

    /// <summary>
    /// Computes function F using Method 2 (nested 'if-else' statements).
    /// Throws std::runtime_error upon division by zero.
    /// </summary>
    /// <param name="params">The calculation parameters a, b, c, x.</param>
    /// <returns>Evaluated value of F.</returns>
    double calcLong(const Params& params);

    /// <summary>
    /// Evaluates function F using both methods, logs comparisons to stdout, and returns the result.
    /// Throws std::runtime_error if division by zero occurs or if method results diverge.
    /// </summary>
    /// <param name="params">The calculation parameters a, b, c, x.</param>
    /// <returns>Evaluated value of F.</returns>
    double calc(const Params& params);
}

