#pragma once

#include "basic_operator.hpp"
#include <cstdint>

class Memory {
private:
    uint8_t memory[1048576];

public:
    Operator getOp(uint32_t);

    uint8_t getByte(uint32_t);
    void writeByte(uint32_t, uint8_t);

    void store(uint32_t, uint32_t, uint32_t);
    uint32_t load(uint32_t, uint32_t);
};