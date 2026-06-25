# Architecture diagram

This diagram shows how `core`, `labs`, and the launcher interact.

```mermaid
flowchart TD
  A[User] -->|runs| B[c++ executable]
  B --> C[core/main.cpp]
  C --> D[core/lab_registry.cpp]
  D --> E[labs/*_lab.cpp]
  E -->|executes| F[lab::topic::run()]
  F --> G[prints output / comments]

  subgraph Workspace
    C
    D
    E
  end
```

Lab creation checklist:

1. Copy `labs/template_lab.cpp` to `labs/<topic>_lab.cpp`.
2. Update the namespace and function name (e.g., `lab::references::run`).
3. Add an entry to `core/lab_registry.cpp` with the new key and function pointer.
4. Build and run: `cmake --preset dev && cmake --build --preset dev` then `./build/cpp_playground <key>`.
