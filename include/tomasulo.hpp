#pragma once

#include "lsb.hpp"
#include "memory.hpp"
#include "register.hpp"
class TomasuloCPU {
private:
    Memory mem;
    LSB lsb;
    RS rs;
    ROB rob;
    Register reg;

public:
    TomasuloCPU();

    void init();
    void run();
};