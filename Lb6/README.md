# Lab 6 — One-dimensional arrays

Contains iterative and recursive solutions for selection/count/sum/zeroing, maximum-even search, array input overloads/templates, and dynamic-array statistics with stable partitioning.

## Build, run, test

```sh
cmake -B build -S .
cmake --build build --target Lb6 Lb6_tests
./build/bin/Lb6
ctest --test-dir build --output-on-failure -R Lb6
```

Choose a task and then `0` for iterative or `1` for recursive. Randomized examples use the current time as their seed; tests use deterministic fixtures.

## Flowchart

```mermaid
flowchart TD
    Start["Choose array task and method"] --> Task{"Task"}
    Task -->|1| Select["Apply divisibility or index predicate"]
    Task -->|2| Even["Find first index of largest even value"]
    Task -->|3| Input["Read typed values iteratively or recursively"]
    Task -->|4| Dynamic["Count positives and find last zero"]
    Dynamic --> HasZero{"Zero exists"}
    HasZero -->|Yes| Sum["Sum values after last zero"]
    HasZero -->|No| Undefined["Report undefined sum"]
    Sum --> Partition["Stable partition at value 2"]
    Select --> Print["Display results"]
    Even --> Print
    Input --> Print
    Partition --> Print
    Undefined --> Print
```

## Activity diagram

```mermaid
stateDiagram-v2
    [*] --> ChooseMethod
    ChooseMethod --> ReadOrGenerate
    ReadOrGenerate --> ProcessArray
    ProcessArray --> DisplayResults
    DisplayResults --> [*]
```

## Structure

```mermaid
classDiagram
    class Presentation_UI {
        +Lb6_main()
        +ArrayPrinter
    }
    class ModuleFacade_Lb6 {
        +processSelection()
        +maxEvenIndex()
        +inputTemplate()
        +Dynamic.countPositive()
        +Dynamic.stablePartition()
    }
    class Infrastructure {
        +ArrayGenerator
    }
    class Task1_ArraySelection {
        +isSelected()
        +countSelected()
        +sumSelected()
        +zeroSelected()
        +processSelection()
    }
    class Task2_EvenIndexSearch {
        +maxEvenIndex()
    }
    class Task3_ArrayInput {
        +Iterative.input()
        +Recursive.input()
        +inputTemplate()
        +inputTemplateRecursive()
    }
    class Task4_DynamicArrayOperations {
        +countPositive()
        +lastZeroIndex()
        +sumAfter()
        +stablePartition()
    }
    class Common_IO {
        +read()
    }

    Presentation_UI --> ModuleFacade_Lb6
    Presentation_UI --> Common_IO
    Presentation_UI --> Infrastructure
    ModuleFacade_Lb6 --> Task1_ArraySelection
    ModuleFacade_Lb6 --> Task2_EvenIndexSearch
    ModuleFacade_Lb6 --> Task3_ArrayInput
    ModuleFacade_Lb6 --> Task4_DynamicArrayOperations
```
