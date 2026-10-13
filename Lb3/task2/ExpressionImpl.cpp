#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Expression.h"

using Params = Task2::Expression::Params;

namespace {

    /// <summary>
    /// Branch A evaluation: F = a * x^2 - c * x + b
    /// Applied when (x + 10 < 0) and (b != 0).
    /// </summary>
    double branchA(const Params &params) {
        return params.a * params.x * params.x - params.c * params.x + params.b;
    }

    /// <summary>
    /// Branch B evaluation: F = (x - a) / (x - c)
    /// Applied when (x + 10 > 0) and (b == 0).
    /// Requires x != c to prevent division by zero.
    /// </summary>
    double branchB(const Params &params) {
        return (params.x - params.a) / (params.x - params.c);
    }

    /// <summary>
    /// Branch C evaluation: F = -x / (a - c)
    /// Applied in all other cases.
    /// Requires a != c to prevent division by zero.
    /// </summary>
    double branchC(const Params &params) {
        return -params.x / (params.a - params.c);
    }

} // namespace

namespace Task2::Expression {

    /// <summary>
    /// Evaluates piecewise function F using Method 1:
    /// Strictly using short 'if' statements without 'else' for formula resolution.
    /// Branch C is set as default, and overwritten if Condition A or Condition B is met.
    /// Edge cases for division by zero are validated independently.
    /// </summary>
    double calcShort(const Params &params) {
        // Step 1: Check division by zero condition for Branch C
        bool errorC1 = false;
        if (params.a == params.c) {
            errorC1 = true;
        }

        // Step 2: Check division by zero condition for Branch B
        const bool conditionB = (params.x + 10.0 > 0.0) && (params.b == 0.0);
        bool errorB1 = false;
        if (conditionB && params.x == params.c) {
            errorB1 = true;
        }

        // Step 3: Handle error for Branch B
        if (errorB1) {
            std::cout << "Method 1: Error - division by zero in Branch B (x = c)" << std::endl;
            throw std::runtime_error("Division by zero in Branch B (x = c)");
        }

        // Step 4: Set default value to Branch C if valid
        double f1 = 0.0;
        if (params.a != params.c) {
            f1 = branchC(params);
        }

        // Step 5: Override F1 if Condition A holds
        const bool conditionA = (params.x + 10.0 < 0.0) && (params.b != 0.0);
        if (conditionA) {
            f1 = branchA(params);
        }

        // Step 6: Override F1 if Condition B holds
        // (Condition A and Condition B are mutually exclusive because signs of (x + 10) differ)
        if (conditionB) {
            f1 = branchB(params);
        }

        // Step 7: Handle error for Branch C if Branch C was reached
        if (errorC1 && !conditionA && !conditionB) {
            std::cout << "Method 1: Error - division by zero in Branch C (a = c)" << std::endl;
            throw std::runtime_error("Division by zero in Branch C (a = c)");
        }

        return f1;
    }

    /// <summary>
    /// Evaluates piecewise function F using Method 2:
    /// Strictly using full 'if-else' statements (nested).
    /// Edge cases for division by zero are validated independently in respective branches.
    /// </summary>
    double calcLong(const Params &params) {
        double f2 = 0.0;

        if (params.x + 10.0 < 0.0 && params.b != 0.0) {
            // Branch A: x + 10 < 0 and b != 0
            f2 = branchA(params);
        } else {
            // Not A: either (x + 10 >= 0) or (b == 0)
            if (params.x + 10.0 > 0.0 && params.b == 0.0) {
                // Branch B: x + 10 > 0 and b == 0
                if (params.x == params.c) {
                    std::cout << "Method 2: Error - division by zero in Branch B (x = c)" << std::endl;
                    throw std::runtime_error("Division by zero in Branch B (x = c)");
                } else {
                    f2 = branchB(params);
                }
            } else {
                // Branch C: all other cases
                if (params.a == params.c) {
                    std::cout << "Method 2: Error - division by zero in Branch C (a = c)" << std::endl;
                    throw std::runtime_error("Division by zero in Branch C (a = c)");
                } else {
                    f2 = branchC(params);
                }
            }
        }

        return f2;
    }

    /// <summary>
    /// Evaluates function F using both methods, validates equality, and prints results in English.
    /// </summary>
    double calc(const Params &params) {
        std::cout << "\n--- Results ---" << std::endl;
        const double f1 = calcShort(params);
        const double f2 = calcLong(params);

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Method 1 (short form): F = " << f1 << std::endl;
        std::cout << "Method 2 (full form):  F = " << f2 << std::endl;

        if (std::abs(f1 - f2) < 1e-9) {
            std::cout << "Results match" << std::endl;
        } else {
            std::cout << "WARNING: Results do not match! Implementation error." << std::endl;
            throw std::runtime_error("Mismatch between Method 1 and Method 2 results");
        }

        return f1;
    }

} // namespace Task2::Expression
