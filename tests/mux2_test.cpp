#include "../src/chip.hpp"
#include "../src/combinational/mux_2.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    int failures = 0;
    for (int sel = 0; sel < 2; ++sel)
    for (int a = 0; a < 2; ++a)
    for (int b = 0; b < 2; ++b) {
        Chip chip;
        uint32_t SEL = chip.input(sel ? State::HIGH : State::LOW);
        uint32_t A   = chip.input(a   ? State::HIGH : State::LOW);
        uint32_t B   = chip.input(b   ? State::HIGH : State::LOW);

        uint32_t out = mux2(chip, A, B, SEL);
        if (!chip.settle()) { std::cerr << "no converge\n"; return 1; }

        int expected = sel ? b : a;
        int got      = chip.get(out) == State::HIGH ? 1 : 0;
        if (got != expected) {
            std::cout << "FAIL sel=" << sel << " a=" << a << " b=" << b
                      << " expected " << expected << " got " << got << "\n";
            ++failures;
        }
    }
    std::cout << (failures ? "FAILED\n" : "all 8 cases passed\n");
    return failures ? 1 : 0;
}