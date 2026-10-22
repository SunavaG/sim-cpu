#include "../src/busOps.hpp"
#include "../src/combinational/rcadder.hpp"
#include <iostream>

struct ALUres
{
    Bus result;
    uint32_t carryOut;
    
};