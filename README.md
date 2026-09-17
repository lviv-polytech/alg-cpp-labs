# Algorithmic C++ Laboratories

This repository contains a collection of C++ laboratory assignments focused on algorithmic thinking, mathematical calculations, and test-driven development. The project is configured with CMake and uses CTest to run automated checks for the implemented solutions.

## Project Overview

The root project is organized into several lab directories and associated test folders:

- `Lb1` — first laboratory assignment and its implementation
- `Lb1.Tests` — automated tests for the first lab
- `Lb2` — second laboratory assignment and its implementation
- `Lb2.Tests` — automated tests for the second lab
- `Lb3` — additional laboratory work and supporting sources

The root `CMakeLists.txt` defines a single C++ project named `alg_cpp_labs`, sets the C++ standard to 17, enables testing, and builds executable targets for each lab together with their corresponding unit tests.

## Build and Run Instructions

The following commands are the standard workflow used to configure, build, and validate the project with CMake.

### 1. Configure and generate the build files

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
```

- `-B build`: Creates a `build` directory and stores generated files and cache there instead of polluting the repository root.
- `-S .`: Tells CMake to use the current directory as the source root.
- `-DCMAKE_BUILD_TYPE=Release`: Enables optimized release settings and disables extra debug output.

### 2. Compile the project

```bash
cmake --build build --config Release
```

- `--build build`: Instructs CMake to build the project from the `build` directory.
- `--config Release`: Applies release configuration for the build.

### 3. Run the tests

```bash
cd build
ctest -C Release --output-on-failure
```

- `ctest`: Runs the tests defined through `add_test(...)` in the CMake configuration.
- `-C Release`: Selects the Release configuration.
- `--output-on-failure`: Prints output logs only when a test fails.

### Optional: verbose test output

```bash
ctest -C Release -V
```

This prints detailed output from all test runs, including successful ones.

## Output Structure

After configuration and build, the binaries are placed under the `build` directory, with runtime artifacts generated in the binary output folder configured by the project.

## Notes

- The project is intended for educational and laboratory use.
- The build system is designed to keep generated artifacts in `build/` for a clean repository layout.
- You can inspect the individual lab directories for task-specific explanations and implementation details.

## Quick Start

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
cd build
ctest -C Release --output-on-failure
```
