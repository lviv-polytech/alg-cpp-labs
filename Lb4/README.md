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
    class Presentation_UI {
        +Lb4_main()
        +TablePrinter
    }
    class ModuleFacade_Lb4 {
        +cycleSums()
        +tabulateFormula()
        +tabulateParametric()
        +tabulateGraph()
        +nestedSums()
        +tabulateTaylor()
    }
    class Core_Tabulation {
        +validateRange()
        +tabulate()
    }
    class Task1_CycleSums {
        +term()
        +cycleSums()
    }
    class Task2_PiecewiseFormula {
        +formula()
        +tabulateFormula()
    }
    class Task3_ParametricTabulation {
        +parametric()
        +tabulateParametric()
    }
    class Task4_GraphTabulation {
        +graphFunction()
        +tabulateGraph()
    }
    class Task5_NestedSums {
        +nestedSums()
    }
    class Task6_TaylorLog {
        +taylorLog()
        +tabulateTaylor()
    }
    class Common_IO {
        +read()
        +promptAndRead()
    }

    Presentation_UI --> ModuleFacade_Lb4
    Presentation_UI --> Common_IO
    ModuleFacade_Lb4 --> Task1_CycleSums
    ModuleFacade_Lb4 --> Task2_PiecewiseFormula
    ModuleFacade_Lb4 --> Task3_ParametricTabulation
    ModuleFacade_Lb4 --> Task4_GraphTabulation
    ModuleFacade_Lb4 --> Task5_NestedSums
    ModuleFacade_Lb4 --> Task6_TaylorLog
    Task2_PiecewiseFormula --> Core_Tabulation
    Task3_ParametricTabulation --> Core_Tabulation
    Task4_GraphTabulation --> Core_Tabulation
    Task6_TaylorLog --> Core_Tabulation
```
