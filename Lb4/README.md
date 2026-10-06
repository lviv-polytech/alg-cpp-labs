# Lab 4 — Iteration and tabulation

This module implements cycle-based summation, three piecewise/tabulated functions, four nested-loop variants, and a logarithm Taylor-series table. Task 4.5 is intentionally excluded because its assignment file does not specify the target region.

## Build, run, test

From the repository root:

```sh
cmake -B build -S .
cmake --build build --target Lb4 Lb4_tests
./build/bin/Lb4
ctest --test-dir build --output-on-failure -R Lb4
```

The executable first asks for task number. Inputs are then read in the order stated in the corresponding task file; task 2 takes `start end step`, task 3 takes `a b c start end step`, task 4 takes `R start end step`, and task 6 takes `start end step epsilon`.

## Flowchart

```mermaid
flowchart TD
    Start["Select a task"] --> Choice{"Task number"}
    Choice -->|1| Sum["Evaluate sum with four loop forms"]
    Choice -->|2| Piecewise["Select formula branch and tabulate"]
    Choice -->|3| Parametric["Select parameter branch; guard zero division"]
    Choice -->|4| Graph["Select graph segment and tabulate"]
    Choice -->|5| Nested["Evaluate nested sums with four loop forms"]
    Choice -->|6| Taylor["Check convergence domain and sum terms"]
    Sum --> Output["Print results"]
    Piecewise --> Output
    Parametric --> Output
    Graph --> Output
    Nested --> Output
    Taylor --> Output
```

## Activity diagram

```mermaid
stateDiagram-v2
    [*] --> ReadTask
    ReadTask --> ValidateInput
    ValidateInput --> Compute: valid
    ValidateInput --> ReportError: invalid
    Compute --> FormatOutput
    FormatOutput --> [*]
    ReportError --> [*]
```

## Structure

```mermaid
classDiagram
    class Tasks_h {
      +cycleSums(n)
      +tabulateFormula(start, end, step)
      +tabulateParametric(a, b, c, start, end, step)
      +tabulateGraph(radius, start, end, step)
      +nestedSums()
      +tabulateTaylor(start, end, step, epsilon)
    }
    class Tasks_cpp {
      +piecewise and series implementations
    }
    class Lb4_console {
      +main()
    }
    class Lb4_tests {
      +main()
      +test assignments
    }
    Lb4_console --> Tasks_h
    Lb4_tests --> Tasks_h
    Tasks_h --> Tasks_cpp
```
