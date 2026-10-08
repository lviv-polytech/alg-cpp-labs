# Lab 5 — Functions and recursion

Implements the parameterized expression, logarithm Taylor series, the helper-function table, five equivalent recursive/iterative sums, and geometric-progression recursion.

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
    T -->|1| Expr["Evaluate h-based expression"]
    T -->|2| Taylor["Check x domain and sum recurrence"]
    T -->|3| Helper["Tabulate nested helper calls"]
    T -->|4| Recur["Compute five sum variants"]
    T -->|5| Geom["Recurse for term and partial sum"]
    Expr --> Out["Print result"]
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
    class Tasks_h {
      +expression(a, b)
      +taylorSum(x, epsilon)
      +nestedExpression(g)
      +recursiveSums(n)
      +geometric(first, ratio, n)
    }
    class Tasks_cpp {
      +helper and recursive implementations
    }
    class Lb5_console {
      +main()
    }
    class Lb5_tests {
      +main()
    }
    Lb5_console --> Tasks_h
    Lb5_tests --> Tasks_h
    Tasks_h --> Tasks_cpp
```
