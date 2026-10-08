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
    class Tasks_h {
      +countSelected(matrix, recursive)
      +sortRows(matrix, recursive)
      +processMatrixPairs(matrix)
      +diagonalLargest(matrix, recursive)
      +firstRowWithoutPositive(matrix, recursive)
    }
    class Tasks_cpp {
      +matrix algorithms and validation
    }
    class Lb7_console {
      +main()
    }
    class Lb7_tests {
      +main()
    }
    Lb7_console --> Tasks_h
    Lb7_tests --> Tasks_h
    Tasks_h --> Tasks_cpp
```
