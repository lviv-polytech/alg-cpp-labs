# Lab 5 — Functions and recursion

Implements the introductory isolated calculation (5.0), the parameterized expression, logarithm Taylor series, the helper-function table, five equivalent recursive/iterative sums, and geometric-progression recursion.

## Tasks Overview

- **Task 5.0 (`task0`):** Introductory calculation separating computation `calculate(x, y) = (x^2 + y) / 2.0` from console I/O for standalone unit testing.
- **Task 5.1 (`task1`):** Rational expression evaluation using helper function $h(x, y, z)$.
- **Task 5.2 (`task2`):** Taylor series tabulation for $\ln(x)$ with recurrent term step.
- **Task 5.3 (`task3`):** Piecewise helper table and nested expression $E(g)$.
- **Task 5.4 (`task4`):** Trigonometric series summation using 5 iterative and recursive methods.
- **Task 5.5 (`task5`):** Recursive geometric progression term, sum, and recursion depth tracking.

## Build, run, test

```sh
cmake -B build -S .
cmake --build build --target Lb5 Lb5_tests
./build/bin/Lb5
ctest --test-dir build --output-on-failure -R Lb5
```

Choose a task in the console and enter the values described in `.local/tasks/5.*`.

The 5.3 task sheet's stated approximation `h(0.5) ≈ 1.2553` conflicts with its explicit six-term series and recurrence. This implementation follows the formula; those terms give `h(0.5) ≈ 1.2605918365`.

## Flowchart

```mermaid
flowchart TD
    Start["Select task"] --> T{"Task"}
    T -->|0| Intro["Compute (x^2 + y) / 2"]
    T -->|1| Expr["Evaluate h-based expression"]
    T -->|2| Taylor["Check x domain and sum recurrence"]
    T -->|3| Helper["Tabulate nested helper calls"]
    T -->|4| Recur["Compute five sum variants"]
    T -->|5| Geom["Recurse for term and partial sum"]
    Intro --> Out["Print result"]
    Expr --> Out
    Taylor --> Out
    Helper --> Out
    Recur --> Out
    Geom --> Out
```

## Activity diagram

```mermaid
stateDiagram-v2
    [*] --> ReadChoice
    ReadChoice --> ReadArguments
    ReadArguments --> Validate
    Validate --> Calculate: valid
    Validate --> Error: invalid
    Calculate --> Display
    Display --> [*]
    Error --> [*]
```

## Structure

```mermaid
classDiagram
    class Presentation_UI {
        +Lb5_main()
        +TablePrinter
    }
    class ModuleFacade_Lb5 {
        +calculate()
        +expression()
        +taylorSum()
        +tabulateTaylor()
        +nestedExpression()
        +recursiveSums()
        +geometric()
    }
    class Task0_IntroCalculation {
        +calculate()
    }
    class Task1_RationalExpression {
        +h()
        +expression()
    }
    class Task2_TaylorSeries {
        +nextTaylorTerm()
        +taylorSum()
        +tabulateTaylor()
    }
    class Task3_PiecewiseExpression {
        +helper()
        +nestedExpression()
    }
    class Task4_RecursiveSeries {
        +term()
        +recursiveSums()
    }
    class Task5_GeometricProgression {
        +geometric()
    }
    class Common_IO {
        +read()
        +promptAndRead()
    }

    Presentation_UI --> ModuleFacade_Lb5
    Presentation_UI --> Common_IO
    ModuleFacade_Lb5 --> Task0_IntroCalculation
    ModuleFacade_Lb5 --> Task1_RationalExpression
    ModuleFacade_Lb5 --> Task2_TaylorSeries
    ModuleFacade_Lb5 --> Task3_PiecewiseExpression
    ModuleFacade_Lb5 --> Task4_RecursiveSeries
    ModuleFacade_Lb5 --> Task5_GeometricProgression
```
