#pragma once

#include "alu.hpp"
#include "memory.hpp"

class BasicCPU {
private:
    Memory mem;
    ALU alu;

public:
    BasicCPU();
    void init();
    bool tick();
    void main();
};