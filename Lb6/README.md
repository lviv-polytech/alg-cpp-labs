# Lab 6 — One-Dimensional Arrays (Modern C++)

Modular C++17 implementation of one-dimensional array algorithms using iterative and recursive techniques.

## Subtasks Overview

1. **Task 6.1 (Variant 17): Array Selection, Counting, Summation, and Zeroing**
   - **Domain:** Pseudo-random integers in $[4, 73]$ inclusive, vector dimension $n = 25$.
   - **Criterion:** $(r_i \bmod 6 = 0) \lor (i \bmod 5 \neq 0)$.
   - **Invariants:**
     - $20 \le K \le 25$ matching elements.
     - $80 \le S \le 1825$ cumulative sum.
     - Sequence: $\text{Generate} \to \text{Print} \to (\text{Count}, \text{Sum}) \to \text{Zero} \to \text{Print}$.
   - **Decomposition:** `generateArray`, `printArray`, `countElements`, `sumElements`, `zeroElements` (with recursive counterparts `generateArrayRec`, `printArrayRec`, `countElementsRec`, `sumElementsRec`, `zeroElementsRec`).

2. **Task 6.2 (Variant 17): Search for the Index of the Maximum Even Element**
   - **Domain:** One-dimensional array $a = (a_0, a_1, \dots, a_{n-1})$ of arbitrary dimension $n \ge 1$ with $a_i \in [-50, 50]$.
   - **Evenness Predicate:** $P(x) \iff (x \bmod 2 = 0)$ (correctly handles negative values and zero: $0 \bmod 2 = 0$).
   - **Solution Existence & Tie-Breaking:**
     - If no even numbers exist ($I_{\text{even}} = \varnothing$), returns sentinel value $k^* = -1$.
     - If duplicates of the maximum even value exist, returns the first occurrence (smallest index): $k^* = \min \{ i \in I_{\text{even}} \mid a_i = \max_{j \in I_{\text{even}}} a_j \}$.
   - **Decomposition:** `initArrayIterative`, `printArrayIterative`, `findMaxEvenIndexIterative`, `initArrayRecursive`, `printArrayRecursive`, `findMaxEvenIndexRecursive`.

3. **Task 6.3: Keyboard & Stream Array Input via Ordinary and Function Templates**
   - **Domain:** Sequential reading and formatted printing of 1D arrays of size $n$ from input streams (`std::istream`, with default `std::cin`).
   - **Dual Typification:**
     - **Part A (Ordinary Functions):** Type-specialized for `int`: `inputArrayIterative`, `printArrayIterative`, `inputArrayRecursive`, `printArrayRecursive`.
     - **Part B (Function Templates):** Parametric polymorphism for generic type $T$ (`int`, `double`, `std::string`): `inputArrayIterativeTemplate<T>`, `printArrayIterativeTemplate<T>`, `inputArrayRecursiveTemplate<T>`, `printArrayRecursiveTemplate<T>`.
   - **Deterministic Unit Testing:** Supports dependency injection of streams (`std::istringstream` and `std::ostringstream`) to verify automated execution without interactive user intervention.

4. **Task 6.4: Real Dynamic Array Analysis and In-Place Stable Partition**
   - **Domain:** Dynamically allocated real vector $a = (a_0, \dots, a_{n-1})$ with $a_i \in \mathbb{R}$.
   - **Mathematical Calculations:**
     - Positive elements count: $C_{+} = \sum_{i=0}^{n-1} \chi_{+}(a_i)$, where $\chi_{+}(x) = 1$ if $x > 0$ else $0$.
     - Last zero search: $k_{\text{last}} = \max \{ i \mid |a_i| < 10^{-9} \}$ (or $-1$ if absent).
     - Sum after last zero: $S_{\text{after}} = \sum_{j = k_{\text{last}} + 1}^{n - 1} a_j$ (returns $0.0$ if $k_{\text{last}} = -1$ or $k_{\text{last}} = n - 1$).
   - **In-Place Stable Partition:**
     - Partition predicate: $\text{trunc}(x) \le 1 \iff x < 2.0$.
     - Reorders elements so that elements with $\text{trunc}(x) \le 1$ precede all other elements, maintaining their relative order ($O(1)$ auxiliary space).
   - **Decomposition:** `initArray`, `printArray`, `countPositive`, `findLastZeroIndex`, `sumAfterLastZero`, `partitionByIntPart` in both iterative and recursive forms.

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
    Start["Start Task 6.4: Dynamic Array Operations"] --> InputSize["Enter array size n, allocate dynamic memory"]
    InputSize --> InitArr["Generate random real values in [-5.0, 5.0]"]
    InitArr --> PrintInit["Print initial formatted array (width = 8, prec = 2)"]
    PrintInit --> CountPos["Calculate count of positive elements (x > 0.0)"]
    CountPos --> FindZero["Find last zero index k_last (from right to left)"]
    FindZero --> CheckZero{"k_last >= 0 && k_last < n - 1?"}
    CheckZero -- "Yes" --> SumElements["Sum elements from k_last + 1 to n - 1"]
    CheckZero -- "No" --> ZeroSum["Sum after last zero = 0.0"]
    SumElements --> Partition["In-place stable partition: trunc(x) <= 1 before others"]
    ZeroSum --> Partition
    Partition --> PrintFinal["Print modified formatted array with identical format"]
    PrintFinal --> Dealloc["Deallocate dynamic memory"]
    Dealloc --> Finish["End"]
```

### Execution Flow / Activity Diagram (`stateDiagram-v2`)

```mermaid
stateDiagram-v2
    [*] --> Allocation
    Allocation --> DataInitialization: "Generate n real elements in [-5.0, 5.0]"
    DataInitialization --> DisplayInitial: "Formatted print to stdout"
    DisplayInitial --> AnalysisPhase
    
    state AnalysisPhase {
        [*] --> ComputePositive: "Count positive elements (x > 0)"
        ComputePositive --> LocateLastZero: "Search for last zero (right-to-left)"
        LocateLastZero --> ComputeSumAfter: "Sum suffix strictly after last zero"
        ComputeSumAfter --> [*]
    }
    
    AnalysisPhase --> InPlacePartition: "Stable partition: shift elements with trunc(x) <= 1"
    InPlacePartition --> DisplayModified: "Formatted print of partitioned array"
    DisplayModified --> Deallocation: "Free memory"
    Deallocation --> [*]
```

### Module Architecture Diagram (`classDiagram`)

```mermaid
classDiagram
    namespace Task4 {
        class DynamicArrayIterative {
            +initArrayIterative(a: vector~double~, minVal: double, maxVal: double) void
            +printArrayIterative(out: ostream, a: vector~double~, width: int, prec: int) void
            +countPositiveIterative(a: vector~double~) int
            +findLastZeroIndexIterative(a: vector~double~, eps: double) int
            +sumAfterLastZeroIterative(a: vector~double~, eps: double) double
            +partitionByIntPartIterative(a: vector~double~) void
        }

        class DynamicArrayRecursive {
            +initArrayRecursive(a: vector~double~, minVal: double, maxVal: double, i: size_t) void
            +printArrayRecursive(out: ostream, a: vector~double~, i: size_t, width: int, prec: int) void
            +countPositiveRecursive(a: vector~double~, i: size_t) int
            +findLastZeroIndexRecursive(a: vector~double~, i: int, eps: double) int
            +sumAfterLastZeroRecursive(a: vector~double~, eps: double) double
            +shiftRightRecursive(a: vector~double~, writePos: size_t, k: size_t) void
            +partitionByIntPartRecursive(a: vector~double~, i: size_t, writePos: size_t) void
        }
    }

    class Lb6Main {
        +runDynamicArrayTask(recursive: bool) void
    }

    Lb6Main ..> DynamicArrayIterative : invokes iterative
    Lb6Main ..> DynamicArrayRecursive : invokes recursive
```
