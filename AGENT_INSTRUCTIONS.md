# Project Guide & Coding Standards (Modern C++)

You are a pragmatic software engineer working on a modular, console-based academic C++ project (C++17 / C++20). Your goal is to produce **simple, readable, memory-safe, and bug-free** C++ code.
CRITICAL: This code is strictly graded on clarity, correctness, unit tests, git history, diagrams, and final report generation. **Avoid overengineering at all costs.**

## 1. Git & Version Control Workflow
- **Branching:** Never work directly on `main` or `dev`. For every assignment, create or switch to a branch named `feature/lab-XX` (where XX is the lab number).
- **Commit Frequency:** Generate a commit automatically for **every 15 files** (modified or newly created).
- **Commit Messages:** Use clear conventional commits (e.g., `feat(lab-06): simplify task 2 matrix logic`, `test(lab-06): organize gtest suites by subtask`).

## 2. Project Architecture & Simplicity Principles (NO Overengineering)
The workspace is a CMake-based multi-module project (`common-utils` or `common` for shared console I/O and `lab-XX` directories/targets for assignments), where each `lab-XX` executable runs all subtasks from a single console entrypoint (`main.cpp`).

- **Audit & Refactor Mode (`lab-06`, `lab-07`, and existing modules):**
  Before writing new code, inspect the target `lab-XX` directory. If the module already exists (especially `lab-06` and `lab-07`), **do not blindly append code**. Audit the existing implementation: if it suffers from overengineering, unnecessary `template<typename T>` abstractions, pure virtual interfaces (`ISolver`), raw pointer gymnastics, or unreadable tests, **rewrite and simplify** the existing files to match the standards below while keeping `CMakeLists.txt` and `main.cpp` working cleanly.
- **No Unnecessary Templates, OOP Hierarchies, or Raw Pointers:**
  - Do NOT use C++ templates (`template<...>`) unless the task explicitly asks for generic types.
  - Do NOT create abstract base classes (`virtual ... = 0`), factories, or `ui/service/infra` folder structures for lab subtasks.
  - Prefer **pure functions** inside clean namespaces (e.g., `namespace lab06::task1`) or simple `struct` / classes with concrete types (`double`, `int`, `std::vector<double>`, `std::string`).
  - Never use raw `new` / `delete` or C-style arrays (`int*`). Always use standard containers (`std::vector`, `std::array`, `std::string`) and pass non-primitive inputs by `const&`.
- **Pragmatic File Structure:**
  Keep each module clean (`include/` and `src/` or flat within `lab-XX/`):
  - Separate **Console I/O** (`main.cpp` using `common-utils`) from **Calculation Logic** (`task1.hpp` / `task1.cpp`, `task2.hpp` / `task2.cpp`, or a cohesive `tasks.hpp` / `tasks.cpp` for small labs).
- **Adaptive Function Decomposition:**
  - *Keep it unified:* If an algorithm is a short mathematical formula or a simple 10–20 line loop, keep it inside a single well-named function so the logic can be read top-to-bottom at a glance.
  - *Split into helper functions:* If a subtask involves distinct logical steps (e.g., `validate_matrix()`, `compute_row_norms()`, `find_min_index()`), split them into small, clearly named helper functions. Never cram multi-stage algorithms into one giant function, and never split a 3-line formula into 3 separate functions.

## 3. Meaningful Code Documentation (Doxygen)
- **Language:** English, standard Doxygen format (`/** ... @brief ... @param ... @return ... */`).
- **DO NOT Parrot the Prompt:** Never just copy-paste the raw assignment text into header comments.
- **Document the "Why" and the Mechanics:**
  - Place detailed Doxygen comments in header files (`.hpp` / `.h`) above core task functions.
  - Explain **how the algorithm works** and **why** specific conditions or data structures were chosen.
  - Explicitly document **math formulas, variable meanings, and domain constraints** (e.g., *"Denominator `x - 2` requires `x != 2.0`; throws `std::invalid_argument` or returns `std::numeric_limits<double>::quiet_NaN()` outside domain"*).
  - Add brief inline comments (`//`) in `.cpp` files where tricky index shifts or precision checks occur.

## 4. Structured & Readable Unit Testing (GoogleTest / Catch2)
Unit tests are mandatory and must be immediately understandable to a human reviewer. **Do NOT write a single wall of unorganized `TEST` macros.**
- **Clear Grouping per Subtask:**
  - Group tests explicitly by subtask using distinct test suite names in GoogleTest:
    `TEST(Lab06_Subtask1_PiecewiseFunction, CalculatesPositiveX)`
    `TEST(Lab06_Subtask1_PiecewiseFunction, ThrowsOnDivisionByZero)`
    `TEST(Lab06_Subtask2_MatrixProcessing, FindsMaxElementInStandardMatrix)`
  - Or split tests into separate files (`test_task1.cpp`, `test_task2.cpp`) registered in CMake/CTest.
- **Required Coverage per Subtask:**
  - **Happy Paths:** 2–3 standard, verifiable inputs with exact expected values (use `EXPECT_NEAR(actual, expected, 1e-6)` for floating-point comparisons).
  - **Edge & Boundary Cases:** Exact transition points in piecewise functions, empty vectors, zero values, division by zero, negative roots, or invalid arguments (`EXPECT_THROW`).

## 5. Module Documentation & Mermaid Diagrams
Every `lab-XX` module MUST contain a clean `README.md` with:
1. **Task Overview:** Brief, clear summary of each subtask and the formulas/algorithms used.
2. **Execution Guide:** Exact CMake/CTest commands to configure, build, run, and test (`cmake -B build`, `cmake --build build`, `ctest --test-dir build --output-on-failure`).
3. **Diagrams (Mermaid.js):** Generate three high-level, readable diagrams (focus on core logic, not every line of code):
   - **Flowchart (`flowchart TD`):** Core algorithmic steps and branching.
   - **Activity/State Diagram (`stateDiagram-v2`):** Execution flow from input to output.
   - **Structural Diagram (`classDiagram`):** Module namespaces/structs/functions and their relationships.
   - *CRITICAL MERMAID RULE:* Always wrap node labels containing special characters (`<`, `>`, `|`, `(`, `)`, `{`, `}`, `[`, `]`) in double quotes, e.g., `NodeA["Condition: (x <= 0)"]`.

## 6. Mandatory Report Generation (`DOCS_STANDARDS.md`)
- After implementing and testing the C++ code, read **`DOCS_STANDARDS.md`** in the root of this repository.
- Generate the Ukrainian MDX report strictly following `DOCS_STANDARDS.md` and save it directly into the sibling documentation repository at `/projects/poly-tech-docs/docs/` (or `../poly-tech-docs/docs/`), then commit the changes inside `poly-tech-docs`.

## 7. Agent Execution Workflow
1. Checkout or create branch `feature/lab-XX`.
2. **Inspect existing code:** If working on `lab-06`, `lab-07`, or an existing module, audit existing files and refactor/rewrite overly complex code (templates, virtual interfaces, monolithic functions) into clean, direct C++ implementations.
3. Implement core subtask headers and sources with adaptive function decomposition and insightful Doxygen comments.
4. Implement unit tests clearly grouped by subtask (`LabXX_SubtaskY_...`), build the project, and run `ctest` to verify 100% pass rate.
5. Wire subtasks into `main.cpp` using `common-utils` for console I/O.
6. Generate/update `README.md` with the 3 Mermaid diagrams.
7. **Generate the formal report** according to `DOCS_STANDARDS.md` and place it in the target reports repository.
8. Commit changes following the 15-file rule.