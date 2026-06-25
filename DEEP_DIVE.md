# cpp-playground deep dive

This document explains how the playground works from two angles at once:

- the **code side**, so you can understand what each file does and how the C++ pieces fit together
- the **user side**, so you can understand what you do in practice when you add a new lab, build the project, and run it

The goal is to make this repository feel predictable and easy to grow as you learn C++.

## What this repository is trying to be

This is not a tiny demo and it is not meant to be a production application.

It is a personal learning workspace where you can:

- read a concept from learncpp.com
- prototype the idea in code
- run it and observe the output
- keep comments in the source as working notes
- keep longer reflections in markdown notes
- commit the result so your progress is visible over time

The important idea is that the repository should act like a learning journal backed by real code.

## The big architecture idea

The project uses three main areas:

- `core/` for the launcher and the lab registry
- `labs/` for learning experiments and concept work
- `notes/` for written summaries and reflections

The project builds into a single executable named `cpp_playground`.

That executable is the thing you run.

It does not mean every lab is its own program. Instead, the executable chooses which lab to run.

This gives you:

- one program to build
- one place to start execution
- many isolated labs underneath it
- a structure that can grow over time without becoming messy

## File-by-file explanation

### `CMakeLists.txt`

This file tells CMake how to build the project.

Think of it as the build recipe.

It answers questions like:

- What is the project called?
- What C++ standard should be used?
- Which source files belong to the executable?
- Which warnings should be enabled?
- Where should include paths point?

### `CMakePresets.json`

This file gives CMake a named, repeatable build configuration.

Think of it as a saved build profile.

Instead of remembering long command lines, you can say:

```bash
cmake --preset dev
cmake --build --preset dev
```

and CMake knows how to configure and build the project the same way every time.

### `core/main.cpp`

This is the actual executable entry point.

Every C++ program starts somewhere, and this is that somewhere.

It does not contain lesson code itself. Instead, it:

- reads the command-line arguments
- asks the registry which labs exist
- runs the selected lab
- prints help when no lab name is given or when the name is unknown

### `core/lab.hpp`

This is the shared definition file for the lab system.

It declares:

- the lab function type
- the `lab_info` structure
- the registry functions used by `main.cpp`

### `core/lab_registry.cpp`

This file contains the list of available labs.

Right now it knows about one lab:

- `initialization`

The registry maps the lab name to the function that runs that lab.

This is why `main.cpp` does not need to know the details of every lab file.

### `labs/initialization.cpp`

This is the first real learning lab.

It contains the code that used to live in the old root `main.cpp`.

The code demonstrates:

- declaration
- definition
- default initialization
- copy initialization
- direct initialization
- list initialization
- narrowing conversion awareness

The comments inside the file are intentionally part of the learning process.

### `notes/README.md`

This folder is for written notes that go beyond inline code comments.

You can use it later for:

- chapter summaries
- personal explanations
- tricky concepts
- reflections after a lab

## How the program runs, step by step

When you run the executable, the flow is simple:

1. The operating system starts `core/main.cpp`.
2. `main()` checks whether a lab name was provided.
3. If no lab name was provided, the program prints the available labs.
4. If a lab name was provided, the registry searches for that name.
5. If the lab exists, the corresponding function is called.
6. That function runs the code inside the lab file.

In this repo, the lab function for the current learning topic is:

```cpp
lab::initialization::run();
```

That is why each lab does not need its own `main()` function.

## Why the architecture is designed this way

This layout is chosen to solve a very practical learning problem:

you want to keep many experiments in one repository without losing control of the structure.

If every lab had its own `main()`, the repository would quickly become awkward.

Instead, this design gives you:

- one launcher
- many isolated labs
- simple registration
- easy build behavior
- room to expand later

It is a better long-term shape for a learning project.

## CMake explained from a beginner’s point of view

If you are new to CMake, the main idea is this:

**CMake does not compile your code directly in the way a compiler does.**

Instead, CMake generates build files for another build system.

In this project, the generated build files go into `build/`.

### What CMake is doing here

When you run:

```bash
cmake --preset dev
```

CMake reads the project files and creates a build configuration.

When you run:

```bash
cmake --build --preset dev
```

CMake asks the underlying build tool to compile the source files and link them into the final executable.

### What each CMake line means

#### `cmake_minimum_required(VERSION 3.20)`

This says the project expects at least CMake 3.20.

It is a compatibility check.

#### `project(cpp_playground LANGUAGES CXX)`

This gives the project its name and tells CMake that we are building C++ code.

#### `set(CMAKE_CXX_STANDARD 17)`

This tells CMake to compile using C++17.

That matters because C++ has different language versions, and you want the compiler to use the version you expect.

#### `set(CMAKE_CXX_STANDARD_REQUIRED ON)`

This means CMake should not silently fall back to another C++ version.

If the build cannot use C++17, the build should fail rather than guess.

#### `set(CMAKE_CXX_EXTENSIONS OFF)`

This keeps the build focused on standard C++ instead of compiler-specific extensions.

That makes the code more portable and easier to understand.

#### `add_executable(cpp_playground ...)`

This tells CMake to build one executable named `cpp_playground`.

The files listed underneath it are compiled together into that executable.

That is why the project has one launcher and many labs.

#### `target_include_directories(cpp_playground PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})`

This tells the compiler where to search for headers.

Because the project uses includes like:

```cpp
#include "core/lab.hpp"
```

the compiler needs the project root in its include path.

#### `target_compile_options(...)`

This adds warning flags.

Warnings are important because they help you catch mistakes earlier.

In a learning project, warnings are useful because they teach you when something is suspicious even if the code still compiles.

## What happens when you build

The build process is basically:

1. CMake reads the project files.
2. CMake creates build files in `build/`.
3. The compiler compiles each `.cpp` file into an object file.
4. The linker combines the object files into one executable.

In this repository, the final executable is:

```text
build/cpp_playground
```

## What happens when you run

When you run the program without arguments:

```bash
./build/cpp_playground
```

the launcher prints the available labs.

When you run a lab by name:

```bash
./build/cpp_playground initialization
```

the launcher finds the lab in the registry and calls its `run()` function.

That is the entire dispatch chain.

## User workflow tutorial

This is the practical everyday workflow.

### First time setup

If the repository is fresh, you do the following:

```bash
cmake --preset dev
cmake --build --preset dev
```

Then run the executable:

```bash
./build/cpp_playground
```

### Running a lab

To run the current lab:

```bash
./build/cpp_playground initialization
```

### Adding a new lab

When you study a new concept, the usual process is:

1. Create a new `.cpp` file in `labs/`.
2. Give the file a descriptive topic-based name.
3. Put your experiment code and comments inside a `run()` function.
4. Declare the function in `core/lab.hpp` or a small topic-specific header if you later want to split declarations more formally.
5. Add the new lab to `core/lab_registry.cpp`.
6. Rebuild the project.
7. Run the lab by name.
8. Optionally write longer reflections in `notes/`.

### What files you change for a new lab

Usually you will change these files:

- a new file in `labs/`
- `core/lab_registry.cpp`
- sometimes `core/lab.hpp` if a new declaration is needed
- sometimes `README.md` or `notes/` if you want to document the concept

If the new lab only adds another concept function, you usually do **not** need to touch the build system because `core/lab_registry.cpp` already references the lab mechanism and the project is already built around that pattern.

## How to think about a new lab file

Each lab file should be treated like a self-contained notebook page, but in code form.

That means a lab file can contain:

- one main learning function
- helper functions used only by that lab
- comments describing what you are testing
- temporary experiments that you may later replace

The lab should answer a question.

Examples:

- What happens with different initialization styles?
- What is the difference between declaration and definition?
- What does a reference change?
- How do class constructors behave?

## Why comments are important here

In this repository, comments are not just filler.

They are part of the learning record.

Use comments to explain:

- what you expected to happen
- what actually happened
- what surprised you
- what you learned
- what you want to verify next

That makes the code useful later when you return to it.

## Why the project does not use one main function per lab

That would be easy at first, but it would scale poorly.

If every file had its own `main()`, then:

- you would need separate executables for each lab
- the project would be harder to navigate
- the build system would become more complicated
- it would stop feeling like one evolving project

The current design keeps one executable and many labs underneath it.

That is the cleaner long-term choice for this kind of learning repository.

## How to add a new lab in practice

Here is a concrete example.

Suppose you want a lab for references.

You would do something like this:

1. Create `labs/references.cpp`.
2. Put your reference experiments in `lab::references::run()`.
3. Add the declaration to `core/lab.hpp` if you keep using the central registry model.
4. Register the function in `core/lab_registry.cpp`.
5. Build again.
6. Run:

```bash
./build/cpp_playground references
```

That is the entire pattern.

## Suggested mental model

Think of the repository like this:

- `core` is the control room
- `labs` are the experiment stations
- `notes` are the notebook pages

That mental model usually makes the structure easier to remember.

## The current lab example

The current lab demonstrates initialization basics.

The output numbers come from the variables inside the lab:

- `a`
- `b`
- `c`
- `d`
- `e`
- `f`
- `ab`

Those values show that the code is being executed and the initialization examples are actually running.

## Final takeaway

This repository is designed so you can:

- learn a concept
- write code for it
- run it immediately
- keep it isolated
- keep notes about it
- come back later and still understand what you did

That is the real purpose of the architecture.
