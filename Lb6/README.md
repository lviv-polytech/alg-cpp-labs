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
    Start["Start Task 6.2: Search Max Even Index"] --> Input["Vector a of size n, initialize bestIndex = -1, i = 0"]
    Input --> CheckEnd{"i < n?"}
    CheckEnd -- "Yes" --> CheckEven{"a[i] % 2 == 0?"}
    CheckEven -- "Yes" --> Compare{"bestIndex == -1 || a[i] > a[bestIndex]?"}
    Compare -- "Yes" --> UpdateBest["bestIndex = i"]
    Compare -- "No" --> NextStep["i = i + 1"]
    CheckEven -- "No" --> NextStep
    UpdateBest --> NextStep
    NextStep --> CheckEnd
    CheckEnd -- "No" --> Result["Return bestIndex (-1 if no even elements)"]
    Result --> Finish["End"]
```

### Execution Flow / Activity Diagram (`stateDiagram-v2`)

```mermaid
stateDiagram-v2
    [*] --> Initialization
    Initialization --> ArrayGeneration: "Generate n elements in [-50, 50]"
    ArrayGeneration --> DisplayInitial: "Print formatted array (width = 5)"
    DisplayInitial --> SearchState
    
    state SearchState {
        [*] --> EvaluateElement: "Check parity (a[i] % 2 == 0)"
        EvaluateElement --> CandidateUpdate: "Update bestIndex if a[i] > a[bestIndex]"
        CandidateUpdate --> CheckNext: "Next index i + 1"
        EvaluateElement --> CheckNext: "Element is odd -> skip"
        CheckNext --> EvaluateElement: "i < n"
        CheckNext --> [*]: "i >= n"
    }
    
    SearchState --> OutputResult: "Return bestIndex (-1 sentinel if absent)"
    OutputResult --> [*]
```

### Module Architecture Diagram (`classDiagram`)

```mermaid
classDiagram
    namespace Lb6 {
        class Task2 {
            +isEven(value: int) bool
            +initArrayIterative(a: vector~int~, minVal: int, maxVal: int) void
            +printArrayIterative(out: ostream, a: vector~int~) void
            +findMaxEvenIndexIterative(a: vector~int~) int
            +initArrayRecursive(a: vector~int~, minVal: int, maxVal: int, i: size_t) void
            +printArrayRecursive(out: ostream, a: vector~int~, i: size_t) void
            +findMaxEvenIndexRecursive(a: vector~int~, i: size_t, bestIndex: int) int
            +maxEvenIndex(values: vector~int~, recursive: bool) int
        }
    }
```
