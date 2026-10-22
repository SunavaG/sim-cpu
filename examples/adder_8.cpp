#include "../src/combinational/rcadder.hpp"
#include <iostream>


int redSweep()
{
    const uint32_t vals[] = { 0, 1, 127, 128, 254, 255 };
    int failures = 0;
    for (uint32_t a : vals)
    for (uint32_t b : vals) {
        Chip chip;
        Bus A = makeInputBus(chip, 8);
        Bus B = makeInputBus(chip, 8);
        setBus(chip, A, a);
        setBus(chip, B, b);
        
        auto r = rippleCarryAdder(chip, A, B, State::LOW);
        if (!chip.settle()) { std::cerr << "no converge\n"; return 1; }

        uint32_t got = readBus(chip, r.sum);
        uint32_t exp = (a + b) & 0xFF;
        if (got != exp) {
            std::cout << "FAIL: " << a << " + " << b
                    << " = " << got << " (expected " << exp << ")\n";
            ++failures;
        }
    }
    std::cout << (failures ? "FAILED\n" : "all " + std::to_string(6*6) + " cases passed\n");
    return failures ? 1 : 0;
}

int exhaustSweepLow()
{
    uint32_t total = 0;
    int failures = 0;
    for (uint32_t a = 0; a < 256; a++)
    for (uint32_t b = 0; b < 256; b++) {
        Chip chip;
        Bus A = makeInputBus(chip, 8);
        Bus B = makeInputBus(chip, 8);
        setBus(chip, A, a);
        setBus(chip, B, b);

        auto r = rippleCarryAdder(chip, A, B, State::LOW);
        if (!chip.settle()) { std::cerr << "no converge\n"; return 1; }

        uint32_t got = readBus(chip, r.sum);
        uint32_t exp = (a + b) & 0xFF;
        if (got != exp) {
            std::cout << "FAIL: " << a << " + " << b
                    << " = " << got << " (expected " << exp << ")\n";
            ++failures;
        }
    }
    std::cout << (failures ? "FAILED\n" : "all " + std::to_string(256*256) + " cases passed\n");
    return failures ? 1 : 0;    
}

int main()
{
    Chip rca8;
    Bus a = makeInputBus(rca8, 8), b = makeInputBus(rca8, 8);
    setBus(rca8, a, 42);
    setBus(rca8, b, 3);
    
    auto r = rippleCarryAdder(rca8, a, b, State::LOW);

    rca8.settle();

    std::cout << "Bus A: " << readBus(rca8, a) << std::endl;
    std::cout << "Bus B: " << readBus(rca8, b) << std::endl;
    std::cout << "Sum: " << readBus(rca8, r.sum) << std::endl;

    int fail = 0;
    fail |= redSweep();
    fail |= exhaustSweepLow();
    return fail;

}