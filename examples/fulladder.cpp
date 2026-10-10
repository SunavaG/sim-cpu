#include "../src/gates/gates.hpp"
#include "../src/chip.hpp"
#include <iostream>

 void fatest(Chip& c)
        {
            for (int a = 0; a <= 1; a++)
            {
                for (int b = 0; b <= 1; b++)
                {
                    for (int cin = 0; cin <= 1; cin++)
                    {
                        uint32_t inputA =
                            c.input(a ? State::HIGH : State::LOW);

                        uint32_t inputB =
                            c.input(b ? State::HIGH : State::LOW);

                        uint32_t carryIn =
                            c.input(cin ? State::HIGH : State::LOW);

                        // Full adder
                        uint32_t xor1 = c.XOR(inputA, inputB);
                        uint32_t sum = c.XOR(xor1, carryIn);

                        uint32_t and1 = c.AND(inputA, inputB);
                        uint32_t and2 = c.AND(xor1, carryIn);
                        uint32_t carryOut = c.OR(and1, and2);

                        c.settle();

                        std::cout
                            << "A: " << static_cast<int>(c.get(inputA))
                            << "  B: " << static_cast<int>(c.get(inputB))
                            << "  Cin: " << static_cast<int>(c.get(carryIn))
                            << "  Sum: " << static_cast<int>(c.get(sum))
                            << "  Cout: " << static_cast<int>(c.get(carryOut))
                            << '\n';
                    }
                }
            }
        }

int main()
{
    {
    Circuit cir;

    uint32_t VCC = cir.createWire(true, State::HIGH);
    uint32_t GND = cir.createWire(true, State::LOW);

    uint32_t inputA = cir.createWire(true, State::HIGH);
    uint32_t inputB = cir.createWire(true, State::HIGH);

    uint32_t sum = cir.createWire(false);
    uint32_t carry = cir.createWire(false);
    uint32_t carryIn = cir.createWire(true, State::HIGH);
    
    uint32_t xor1out = cir.createWire(false); //A Xor B
    uint32_t andAB = cir.createWire(false); // A and B
    uint32_t andCX = cir.createWire(false); // CarryIn XOR (A Xor B)

    gates::addXOR(cir, inputA, inputB, xor1out, VCC, GND);
    gates::addXOR(cir, carryIn, xor1out, sum, VCC, GND);
    gates::addAND(cir, inputA, inputB, andAB, VCC, GND);
    gates::addAND(cir, xor1out, carryIn, andCX, VCC, GND);
    gates::addOR(cir, andAB, andCX, carry, VCC, GND);

    if (!cir.settle()) {
        std::cout << "circuit did not converge\n";
        return 1;
    }

    std::cout << "Input: " << static_cast<int>(cir.getWireState(inputA)) << std::endl;
    std::cout << "Input: " << static_cast<int>(cir.getWireState(inputB)) << std::endl;
    std::cout << "CarryIn: " << static_cast<int>(cir.getWireState(carryIn)) << std::endl; 
    std::cout << "Carry: " << static_cast<int>(cir.getWireState(carry)) << std::endl;
    std::cout << "Sum: " << static_cast<int>(cir.getWireState(sum));
    }


    {
        Chip fa;
        uint32_t inputA = fa.input(State::HIGH);
        uint32_t inputB = fa.input(State::HIGH);
        uint32_t carryIn = fa.input(State::HIGH);
        
        uint32_t xor1 = fa.XOR(inputA, inputB);
        uint32_t sum = fa.XOR(xor1, carryIn);
        uint32_t andIP = fa.AND(inputA, inputB);
        uint32_t and2 = fa.AND(xor1, carryIn);
        uint32_t carry = fa.OR(andIP,and2);

        fa.settle();

        std::cout << "Input: " << static_cast<int>(fa.get(inputA)) << std::endl;
        std::cout << "Input: " << static_cast<int>(fa.get(inputB)) << std::endl;
        std::cout << "Carry: " << static_cast<int>(fa.get(carryIn)) <<std::endl;
        std::cout << "Sum: " << static_cast<int>(fa.get(sum)) << std::endl;
        std::cout << "CarryOut: " << static_cast<int>(fa.get(carry));
    }

    {
        Chip c;
        fatest(c);
    }

}