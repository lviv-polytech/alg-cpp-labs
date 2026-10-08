# Lab 7 — Matrix processing

Includes matrix filtering by the non-multiple-of-six predicate, stable row sorting by columns 1/2/4, paired row-extrema swaps, largest-value placement on the main diagonal, and first nonpositive-row search. Both iterative and recursive implementations are available where required.

## Build, run, test

```sh
cmake -B build -S .
cmake --build build --target Lb7 Lb7_tests
./build/bin/Lb7
ctest --test-dir build --output-on-failure -R Lb7
```

Choose the task number. Tasks 1 and 3 also ask for the method (`0` iterative, `1` recursive); task 2 asks for row and column counts. Random examples use the current time as a seed.

## Flowchart

```mermaid
flowchart TD
    Start["Choose matrix task"] --> Task{"Task"}
    Task -->|1| Filter["Count and sum values not divisible by 6"]
    Filter --> Zero["Zero selected values"]
    Zero --> Sort["Stable lexicographic row sort"]
    Task -->|2| Pair["For each row pair, swap previous-row minimum with next-row maximum"]
    Task -->|3| Copy["Keep original matrix for row search"]
    Copy --> RowCheck["Find first row with no positive values"]
    RowCheck --> Diagonal["Place largest remaining value on each diagonal cell"]
    Sort --> Output["Print matrices and results"]
    Pair --> Output
    Diagonal --> Output
```

## Activity diagram

```mermaid
stateDiagram-v2
    [*] --> GenerateOrRead
    GenerateOrRead --> PreserveOriginal
    PreserveOriginal --> RunSelectedAlgorithm
    RunSelectedAlgorithm --> DisplayMatrices
    DisplayMatrices --> [*]
```

## Structure

```mermaid
classDiagram
    class Presentation_UI {
        +Lb7_main()
        +MatrixPrinter
    }
    class ModuleFacade_Lb7 {
        +countSelected()
        +sortRows()
        +processMatrixPairs()
        +diagonalLargest()
        +firstRowWithoutPositive()
    }
    class Core_MatrixTypes {
        +validateRectangular()
        +validateSquare()
    }
    class Infrastructure {
        +MatrixGenerator
    }
    class Task1_MatrixFilterAndSort {
        +selected()
        +countSelected()
        +sumSelected()
        +zeroSelected()
        +rowLess()
        +sortRows()
    }
    class Task2_MatrixRowPairs {
        +findMinInRow()
        +findMaxInRow()
        +swapElements()
        +processMatrixPairs()
    }
    class Task3_MatrixDiagonal {
        +diagonalLargest()
        +firstRowWithoutPositive()
    }
    class Common_IO {
        +read()
    }

    Presentation_UI --> ModuleFacade_Lb7
    Presentation_UI --> Common_IO
    Presentation_UI --> Infrastructure
    ModuleFacade_Lb7 --> Task1_MatrixFilterAndSort
    ModuleFacade_Lb7 --> Task2_MatrixRowPairs
    ModuleFacade_Lb7 --> Task3_MatrixDiagonal
    Task1_MatrixFilterAndSort --> Core_MatrixTypes
    Task2_MatrixRowPairs --> Core_MatrixTypes
    Task3_MatrixDiagonal --> Core_MatrixTypes
```
