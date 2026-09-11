# ready_set_bool

Boolean algebra and set theory exercises from École 42's _Ready, Set, Bool!_ subject, implemented as
a C++17 static library with a Catch2 test suite built through CMake.

The library (`namespace m42`) implements bit-level arithmetic without the `+` and `*` operators, a
propositional-logic engine over reverse Polish notation (evaluation, truth tables, negation and
conjunctive normal forms, satisfiability), set algebra driven by the same formulas, powersets and a
Morton-order space-filling curve. Each exercise has its own source file and test file.

## Highlights

- **A small expression-tree engine (`Proposition`) shared by five exercises.** The RPN parser
  builds a binary tree with a stack, validating tokens (`0 1 A–Z ! & | ^ > =`) and arity in the
  node constructor and freeing everything already allocated before throwing on malformed input. The
  class follows the rule of five with copy-and-swap and deep-copies the tree.
- **Normal forms by term rewriting.** `to_negation_normal_form()` eliminates `=`, `>` and `^`,
  pushes `!` inward with De Morgan's laws and cancels double negation; `to_conjunctive_normal_form()`
  then distributes `|` over `&` and right-associates chains so the output matches the subject's
  canonical strings (e.g. `ABCD&|&` → `ABC|BD|&&`).
- **Set evaluation reuses the logic tree.** `eval_set` converts the formula to NNF and interprets
  `&`, `|`, `!` as `std::set_intersection`, `set_union` and complement relative to the union of all
  input sets, using the standard algorithms on sorted sets.
- **Arithmetic from gates.** `adder` chains a 32-stage ripple-carry of `full_adder`s built from
  two `half_adder`s each; `multiplier` is shift-and-add on top of `adder`, masking each partial
  product with a sign-extended bit; `gray_code` is `n ^ (n >> 1)`.
- **Space-filling curve with an exact inverse.** `map(x, y)` interleaves the 16-bit coordinates
  into a 32-bit Morton code and scales it into `[0, 1]`; `reverse_map` de-interleaves it back. The
  test drives 100 random coordinate pairs through the round trip and requires equality.
- **Every exercise is unit-tested** with the subject's examples plus edge cases, and the tests are
  registered individually with CTest via `catch_discover_tests`.

## How it works

| File                             | Exercise                                            |
| -------------------------------- | --------------------------------------------------- |
| `src/adder.cpp`                  | `half_adder`, `full_adder`, `adder(a, b)`           |
| `src/multiplier.cpp`             | `multiplier(a, b)`                                  |
| `src/gray_code.cpp`              | `gray_code(n)`                                      |
| `src/Proposition.cpp`            | RPN parser, tree, evaluate, substitute, NNF, CNF, SAT, set evaluation |
| `src/eval_formula.cpp`           | `eval_formula("10&")` → `bool`                      |
| `src/truth_table.cpp`            | `print_truth_table("AB&C|")` (Markdown table on stdout) |
| `src/negation_normal_form.cpp`   | `negation_normal_form("AB=")` → `"AB&A!B!&|"`      |
| `src/conjunctive_normal_form.cpp`| `conjunctive_normal_form("AB&!")` → `"A!B!|"`      |
| `src/sat.cpp`                    | `sat("AA!&")` → `false`                             |
| `src/powerset.cpp`               | `powerset({1,2,3})` → all 8 subsets                 |
| `src/eval_set.cpp`               | `eval_set("AB&", {{'A',{0,1,2}},{'B',{0,3,4}}})` → `{0}` |
| `src/curve.cpp`                  | `interleave`, `map`, `deinterleave`, `reverse_map`  |
| `src/common.cpp`                 | `extend_bit`, `pop_two` helper                      |

SAT and the truth table both enumerate all `2^n` assignments of the formula's variables: for each
bit pattern a copy of the tree has its variables substituted with `0`/`1` leaves and is evaluated.
`powerset` grows the result iteratively, adding each element to every subset found so far.

## Building and running

Requires CMake 3.27+, a C++17 compiler and Catch2 (v3, found via `find_package(Catch2)`).
Compilation uses `-Wall -Wextra -Werror`; `compile_commands.json` export is on.

```sh
cmake -B build
cmake --build build
```

This produces the static library `libready_set_bool.a` and the `tests` executable. Include
`include/ready_set_bool.hpp` to use the functions; `include/Proposition.hpp` exposes the tree class
directly (`vars()`, `postfix_notation()`, `evaluate()`, `is_satisfiable()`, `print_tree()`).

## Testing

```sh
ctest --test-dir build          # every TEST_CASE as a separate CTest entry
./build/tests "[sat]"           # or filter with Catch2 tags
```

22 test cases across 12 files: one file per exercise plus `test_proposition_class.cpp` for the
parser itself. A `.clang-tidy` configuration (bugprone, cert, modernize, performance and
readability checks) is included.

## Project layout

```
include/ready_set_bool.hpp   public function declarations
include/Proposition.hpp      expression-tree class
src/                         12 sources, one per exercise plus Proposition.cpp
tests/                       12 Catch2 files
CMakeLists.txt, .clang-tidy
```

About 1,200 lines of C++ in 27 files.

## Limitations

- `sat` and `print_truth_table` are brute force, exponential in the number of variables (at most
  26 single-letter variables, enumerated in a 32-bit counter).
- `eval_set` treats the universe as the union of the provided sets, so `A!` with a single set is
  empty, as the subject specifies.
- Tree nodes are raw-pointer managed with explicit `delete`; the rewriting passes free and
  reallocate nodes by hand.
- No CI configuration.

## Context

École 42, _Ready, Set, Bool!_: exercises 00–11 (adder, multiplier, gray code, boolean evaluation,
truth table, NNF, CNF, SAT, powerset, set evaluation, space-filling curve and its inverse). The
subject fixes the RPN syntax and the expected output strings that the tests assert.
