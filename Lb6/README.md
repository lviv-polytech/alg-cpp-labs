# Lab 6 — One-Dimensional Arrays (Modern C++)

Modular C++17 implementation of one-dimensional array algorithms using iterative and recursive techniques.

## Subtasks Overview

1. **Task 6.1 (Variant 17): Array Selection, Counting, Summation, and Zeroing**
   - **Domain:** Pseudo-random integers in $[4, 73]$ inclusive, vector dimension $n = 25$.
   - **Criterion:** $(r_i \bmod 6 = 0) \lor (i \bmod 5 \neq 0)$.
   - **Invariants:**
     - $20 \le K \le 25$ matching elements.
     - $80 \le S \le 1825$ cumulative sum.
     - Modifications occur strictly after calculation: $\text{Generate} \to \text{Print} \to (\text{Count}, \text{Sum}) \to \text{Zero} \to \text{Print}$.
   - **Decomposition (Single Responsibility):** Separate functions for iterative (`generateArray`, `printArray`, `countElements`, `sumElements`, `zeroElements`) and recursive (`generateArrayRec`, `printArrayRec`, `countElementsRec`, `sumElementsRec`, `zeroElementsRec`) approaches.
2. **Task 6.2:** Search for the first index of the maximum even element.
3. **Task 6.3:** Array input overloads and template functions.
4. **Task 6.4:** Dynamic array processing: positive count, sum after last zero, and stable partition around value $2.0$.

## Execution Guide

Configure, compile, and run the module and test suite via CMake and CTest:

```bash
# Configure build directory
cmake -B build -S .

# Build executable and test suite
cmake --build build --target Lb6 Lb6_tests

# Run interactive console application
./build/bin/Lb6

# Execute automated tests
ctest --test-dir build --output-on-failure -R Lb6
```

## Diagrams (Mermaid.js)

### Algorithmic Flowchart (`flowchart TD`)

```mermaid
flowchart TD
    Start["Start Task 6.1: Variant 17"] --> Gen["Generate array: 25 integers in range [4, 73]"]
    Gen --> PrintInit["Print initial formatted array: width = 4"]
    PrintInit --> EvalLoop["Evaluate elements: (i = 0 .. 24)"]
    EvalLoop --> Match{"(r[i] % 6 == 0) || (i % 5 != 0)?"}
    Match -- "Yes" --> Accum["Increment count K, accumulate sum S"]
    Match -- "No" --> NextElem["Keep element intact"]
    Accum --> NextElem
    NextElem --> CheckEnd{"i == 24?"}
    CheckEnd -- "No" --> EvalLoop
    CheckEnd -- "Yes" --> ModLoop["Zero elements where predicate is true"]
    ModLoop --> PrintResult["Print Count K and Sum S"]
    PrintResult --> PrintFinal["Print modified formatted array (with zeros)"]
    PrintFinal --> Finish["End"]
```

### Execution Flow / Activity Diagram (`stateDiagram-v2`)

```mermaid
stateDiagram-v2
    [*] --> Initialization
    Initialization --> ArrayGeneration: "Generate values in [4, 73]"
    ArrayGeneration --> DisplayInitial: "Formatted print"
    DisplayInitial --> Processing
    
    state Processing {
        [*] --> CountElements: "Count matching elements (iterative / recursive)"
        CountElements --> SumElements: "Sum matching elements (iterative / recursive)"
        SumElements --> ZeroElements: "In-place zeroing after metrics computed"
        ZeroElements --> [*]
    }
    
    Processing --> DisplayMetrics: "Print K and S"
    DisplayMetrics --> DisplayModified: "Formatted print of modified array"
    DisplayModified --> [*]
```

### Module Architecture Diagram (`classDiagram`)

```mermaid
classDiagram
    namespace Lb6 {
        class Task1 {
            +isSelected(index: int, value: int) bool
            +generateArray(values: vector~int~, low: int, high: int) void
            +printArray(out: ostream, values: vector~int~) void
            +countElements(values: vector~int~) int
            +sumElements(values: vector~int~) int
            +zeroElements(values: vector~int~) void
            +generateArrayRec(values: vector~int~, low: int, high: int, i: size_t) void
            +printArrayRec(out: ostream, values: vector~int~, i: size_t) void
            +countElementsRec(values: vector~int~, i: size_t) int
            +sumElementsRec(values: vector~int~, i: size_t) int
            +zeroElementsRec(values: vector~int~, i: size_t) void
            +processSelection(values: vector~int~, recursive: bool) SelectionResult
        }
        class SelectionResult {
            +count: int
            +sum: int
        }
    }
    
    Task1 --> SelectionResult : returns
```
