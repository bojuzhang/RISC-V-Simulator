#pragma once

#include "lsb.hpp"
#include "memory.hpp"
#include "predictor.hpp"
#include "register.hpp"
class TomasuloCPU {
private:
    Memory mem;
    LSB lsb;
    RS rs;
    ROB rob;
    Register reg;
    Predictor pre;

public:
    TomasuloCPU();

    void init();
    void run();
};