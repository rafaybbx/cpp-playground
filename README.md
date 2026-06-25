# cpp-playground

`cpp-playground` is a personal C++ learning workspace built as a long-term playground for prototyping ideas, testing concepts from [learncpp.com](https://www.learncpp.com/), and keeping a record of learning through code, comments, and notes.

For a full tutorial-style explanation of how the project works, see [DEEP_DIVE.md](DEEP_DIVE.md).

## Continuous Integration (CI)

This repository includes a GitHub Actions workflow at `.github/workflows/ci.yml` that:

- configures and builds the project using the `dev` preset
- installs `@mermaid-js/mermaid-cli` and attempts to render `ARCHITECTURE.mmd` to `docs/architecture.png`
- uploads the rendered diagram as a workflow artifact

The workflow runs on pushes to `main` and any `feat/**` branches, and on pull requests targeting `main`.

You can inspect the rendered diagram artifact from the Actions UI after a run.

## VS Code snippet for new labs

There is a snippet configured at `.vscode/snippets/lab.code-snippets` with the prefix `newlab`.

Use it to scaffold a new lab quickly inside Codespaces or your local VS Code:

1. Create a new file under `labs/`.
2. Type `newlab` and press Tab to expand the snippet.
3. Update the namespace and function body.

## Diagram source

The Mermaid source file is `ARCHITECTURE.mmd`. The CI workflow renders it using `mmdc` and uploads the PNG as an artifact.


## Big Picture

The repository is organized around three layers:

- `core/` contains the application launcher and the lab registry.
- `labs/` contains isolated learning experiments, one concept or chapter fragment at a time.
- `notes/` contains written reflections, summaries, and follow-up notes.

The goal is not to build a tiny demo project. The goal is to build a learning system that can grow naturally while staying easy to use every day.

## Current Architecture

### `core/`

The `core` folder holds the program entry point and the dispatch layer.

Responsibilities of `core/`:

- start the program
- read the requested lab key
- list available labs
- dispatch execution to the selected lab

This keeps the launcher logic separate from the actual lesson code.

### `labs/`

The `labs` folder holds the actual C++ experiments.

Rules for labs:

- each lab is about one topic, one chapter fragment, or one focused concept
- labs use descriptive topic-based names
- labs can contain multiple helper functions, comments, and small experiments
- a lab should stay isolated so it can be revisited later without confusion

The current lesson from the original root `main.cpp` now lives in `labs/initialization.cpp` and is registered as the `initialization` lab.

### `notes/`

The `notes` folder is for written learning notes.

Use it for:

- chapter summaries
- explanations in your own words
- things that were confusing the first time
- follow-up ideas and questions

The code comments inside each lab remain the primary in-code notes, while `notes/` is there for longer written reflections.

## Folder Layout

```text
.
├── CMakeLists.txt
├── README.md
├── core/
│   ├── lab.hpp
│   ├── lab_registry.cpp
│   └── main.cpp
├── labs/
│   └── initialization.cpp
├── notes/
│   └── README.md
└── .gitignore
```

Generated build output lives in `build/` and should not be committed.

## Naming Rules

### Lab file names

Lab file names should be descriptive and topic-driven.

Good examples:

- `initialization.cpp`
- `references.cpp`
- `pointers.cpp`
- `classes.cpp`
- `strings.cpp`

Rules:

- prefer topic names over numeric names
- avoid numbering unless it becomes genuinely useful later
- keep one main topic per lab file whenever possible
- use comments inside the lab as your working notes

### Lab function names

Each lab should expose one clear entry function.

Recommended pattern:

- `lab::initialization::run()`
- `lab::references::run()`
- `lab::pointers::run()`
- `lab::classes::run()`

Rules:

- use `run()` as the standard entry name
- keep the namespace aligned with the topic name
- avoid `main()` in lab files

### Branch names

Branch names should be topic-based and easy to scan.

Good examples:

- `lab-initialization`
- `lab-references`
- `lab-pointers`
- `lab-classes`
- `core-dispatch`

Rules:

- prefer descriptive names over progress numbers
- keep names short
- use hyphens for branch names

## Build System

This repository uses CMake and produces one executable: `cpp_playground`.

Build files are generated outside the source tree in `build/`.

### Configure

```bash
cmake -S . -B build
```

### Build

```bash
cmake --build build
```

### Run

Run without arguments to see the available labs:

```bash
./build/cpp_playground
```

Run a specific lab by key:

```bash
./build/cpp_playground initialization
```

## Optional Preset Workflow

If you prefer preset-based commands, CMake presets can be used as well:

```bash
cmake --preset dev
cmake --build --preset dev
```

This still builds the same executable, but it gives a cleaner repeatable workflow inside Codespaces.

## Learning Workflow

The intended daily workflow is:

1. Read a new concept or chapter.
2. Create a new lab file in `labs/`.
3. Prototype the code.
4. Add comments that explain what was tested or learned.
5. Register the lab in `core/lab_registry.cpp`.
6. Build and run the lab.
7. Add a note in `notes/` if the topic deserves a longer summary.
8. Commit and push the change.

That keeps the repository as both a playground and a personal archive of progress.

## Current Lab

The current lab is:

- `labs/initialization.cpp`

It contains the variable declaration and initialization experiments that were originally in the root `main.cpp`.

## Future Growth

This structure leaves room for later improvements without forcing them now.

Possible future additions:

- more labs for later learncpp.com chapters
- shared helpers inside `core/`
- shared declarations in `include/`
- reusable implementations in `src/`
- better lab selection or categories
- test targets if validation becomes useful later

## Philosophy

This repository should stay:

- easy to open
- easy to extend
- easy to revisit
- useful as proof of learning
- cool enough that it feels like a real evolving project, not a throwaway scratchpad

## Continuous Integration (GitHub Actions)

This repository includes a CI workflow at `.github/workflows/ci.yml` that:

- configures and builds the project using CMake on every push and PR
- runs a separate job that renders the `ARCHITECTURE.mmd` Mermaid file into
	`architecture.svg` and `architecture.png` using `@mermaid-js/mermaid-cli` and
	uploads them as build artifacts (visible in the workflow run)

Why this helps:

- the build job verifies your labs compile on push
- the diagram job produces a visual asset you can download from the workflow

To see the artifacts, open the workflow run in GitHub and look for the
`architecture-diagrams` artifact.

## Editor snippet for quick lab creation

There is a VS Code snippet at `.vscode/lab-snippets.code-snippets`.

To use it in Codespaces:

1. Open a new file under `labs/` and name it `<topic>_lab.cpp`.
2. Type `newlab` and accept the snippet.
3. Fill in the topic name and goals and implement `lab::<topic>::run()`.

This keeps new labs consistent and speeds up the daily workflow.

## Architecture diagram export

The repository contains `ARCHITECTURE.mmd` which is the raw Mermaid diagram.

On CI the diagram is rendered into `architecture.svg` and `architecture.png` and
uploaded as artifacts for easy viewing.

If you want a local copy and you have Node.js installed, you can render it
locally with:

```bash
npm install -g @mermaid-js/mermaid-cli
mmdc -i ARCHITECTURE.mmd -o architecture.svg
mmdc -i ARCHITECTURE.mmd -o architecture.png
```

