# sim-cpu

**A computer built from first principles in C++ — from MOSFET switches, to logic gates, to an 8-bit CPU.**

[![Status: Combinational Layer Complete](https://img.shields.io/badge/status-combinational%20layer%20complete-brightgreen)]()
[![Language: C++20](https://img.shields.io/badge/language-C%2B%2B20-blue)]()
[![Tests: 65k+ cases passing](https://img.shields.io/badge/tests-65%2C536%20adder%20cases%20passing-success)]()

Most "build a CPU" projects start at the instruction set. This one starts at the transistor.

A MOSFET is a switch. Wires connect switches. Switches form gates. Gates form adders, muxes, and registers. Those form an ALU, a datapath, and eventually a CPU that runs programs. **sim-cpu builds every layer explicitly** and verifies each one before the next is built.

---

## Current Status

> **The combinational (calculator) half is complete and exhaustively tested.**
> The sequential (machine) half — flip-flops, registers, control — is in progress.

| Layer | Status | Verification |
|---|---|---|
| 1–3. Wires, transistors, switch-level simulator | ✅ Done | Union-find connectivity, fixed-point settling |
| 4. Gates (NOT, NAND, NOR, AND, OR, XOR) | ✅ Done | Exhaustive truth tables |
| 5. `Chip` abstraction | ✅ Done | Used by all tests |
| 6. `Bus` abstraction | ✅ Done | Verified via adder sweep |
| 7. Combinational blocks | ✅ Done | See table below |
| 8. Sequential blocks (DFF, registers) |  ⏳ Planned | — |
| 9–12. Datapath, control, CPU | ⏳ Planned | — |
| 13–14. Assembler, programs, BASIC | ⏳ Planned | — |

---

## What Works Today

Every block below has an automated test. "Exhaustive" means every possible input is checked.

| Block | Test coverage |
|---|---|
| NOT, NAND, NOR, AND, OR, XOR | Exhaustive |
| Full adder (1-bit) | Exhaustive (8/8 rows) |
| Ripple-carry adder (8-bit) | **Exhaustive (65,536/65,536 cases)** |
| 2:1 mux (wire and bus) | Exhaustive |
| 4:1 mux (wire and bus) | All 4 selectors |
| Bus bitwise ops (AND, OR, XOR, NOT) | Sanity vectors |
| **8-bit ALU (ADD, AND, OR, XOR + flags)** | **144/144 cases** |

**Verified:** `42 + 3 = 45` through the full transistor-level adder chain.  
**Verified:** `144 cases, 0 failures` through the ALU sweep.

---

## How It Works (in 60 seconds)

1. **Wires** hold one of four states: `HIGH`, `LOW`, `DISCONNECTED`, or `CONFLICT`.
2. **Transistors** connect two wires (source/drain) when their gate wire is in the right state (PMOS conducts on LOW, NMOS on HIGH).
3. **`evaluate()`** finds conducting transistors, unions their connected wires with a union-find, and resolves each connected component's state from any fixed wires in it.
4. **`settle()`** repeats `evaluate()` until no wire changes. A stable feedback loop (a latch) is a fixed point; an unstable one (a ring oscillator) returns `false`.
5. **Gates** are just small transistor networks. **Adders, muxes, and the ALU** are compositions of gates.
6. **`Bus`** groups wires into a value so you can write `setBus(chip, a, 42)` instead of 8 separate wire writes.

---

## Build & Run

### Requirements
- C++20 compiler (GCC 10+, Clang 12+, MSVC 19.29+)
- CMake 3.20+ (Not tested, optional; tests can be compiled directly)

### Build and test

```bash
git clone https://github.com/SunavaG/sim-cpu.git
cd sim-cpu


# Currently compile a single example directly
g++ -std=c++20 examples/alu.cpp -o alu && ./alu