# SOBFVM — OCaml Bytecode Virtual Machine

A C implementation of a virtual machine that interprets a simplified subset of OCaml bytecode.

## Project layout

```
.
├── Makefile
├── README.md
├── .gitignore
├── include/                       # Headers (.h)
│   ├── types.h                    # Base types and the VM struct (with tab_atoms[256] inside)
│   ├── stack.h                    # Stack operations
│   ├── loader.h                   # Reading the .sobf input file
│   ├── primitives.h               # Atoms initialization and primitive calls
│   ├── vm.h                       # State printing
│   ├── engine.h                   # Main fetch-evaluate loop
│   ├── engine_eval_base.h         # Evaluator: base / stack / accumulator opcodes
│   ├── engine_eval_arithmetic.h   # Evaluator: arithmetic and constants
│   ├── engine_eval_control.h      # Evaluator: control flow and C-calls
│   ├── engine_eval_memory.h       # Evaluator: globals, blocks, atoms
│   ├── instr_base.h
│   ├── instr_arithmetic.h
│   ├── instr_control.h
│   └── instr_memory.h
├── src/                           # Sources (.c)
│   ├── main.c                     # CLI entry point
│   ├── stack.c
│   ├── loader.c
│   ├── primitives.c
│   ├── vm.c
│   ├── engine.c                   # Just the loop with if/continue routing
│   ├── engine_eval_base.c         # Sub-switch for base opcodes
│   ├── engine_eval_arithmetic.c   # Sub-switch for arithmetic opcodes
│   ├── engine_eval_control.c      # Sub-switch for control-flow opcodes
│   ├── engine_eval_memory.c       # Sub-switch for memory opcodes
│   ├── instr_base.c
│   ├── instr_arithmetic.c
│   ├── instr_control.c
│   └── instr_memory.c
└── tests/                         # .sobf test files
```

## Architecture highlights

- **No global variables.** The 256 atoms (`tab_atoms`) are encapsulated as a field of the `vm` struct, so no `extern` is ever needed.
- **Single source of truth for the `vm` type.** The struct is defined exactly once, in `types.h`.
- **Split dispatch.** Instead of a single 80-case `switch` in one file, the engine routes each opcode through four small sub-switches (`engine_eval_base`, `_arithmetic`, `_control`, `_memory`). The main loop in `engine.c` is therefore reduced to four `if (engine_eval_xxx(mv, op)) continue;` calls.
- **Function contracts.** Every public function carries `@requires` / `@assigns` / `@ensures` clauses (in the spirit of Frama-C / ACSL) in both its header declaration and its source definition.

## Build

```bash
make
```

This produces the `sobfvm` executable at the project root. To start over:

```bash
make rebuild
```

To clean up:

```bash
make clean
```

## Usage

```bash
./sobfvm file.sobf
./sobfvm file.sobf --print-end-machine
```

- The first argument is mandatory: the path to a `.sobf` file.
- The optional flag `--print-end-machine` dumps the full machine state (program counter, accumulator, stack, globals) at the end of execution.

### Examples

```bash
./sobfvm tests/base.sobf
./sobfvm tests/fact.sobf --print-end-machine
./sobfvm tests/wumpus.sobf
```

## `.sobf` file format

- Line 1: the literal string `SOBF`
- Line 2: two integers `c v` (number of code cells, number of global cells)
- Binary code array: `c` × `int` (32-bit each)
- Binary global array: `v` × `long int` (64-bit each)

## Value encoding

- Integers are encoded as odd values: `n` → `2n + 1`.
- Booleans `true` and `false` correspond to the integers `1` and `0`, encoded as `3` and `1` respectively.

## Author

Ibrahima Diaby — ENSIIE, first year Computer Science & Computer Systems Engineering Student — PRIM11 project (2025-2026).

