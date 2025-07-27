#pragma once

#include "basic_operator.hpp"
#include <cstdint>
#include <unordered_map>
class Memory {
private:
    uint32_t reg[32]{};
    uint32_t PC{};

    uint8_t memory[1048576];

public:
    uint32_t read(short pos);
    void write(short pos, uint32_t val);

    void move(uint32_t pos);
    uint32_t getPC();

    Operator getOp(uint32_t);
    void addOp(uint32_t, const Operator&);

    uint8_t getByte(uint32_t);
    void writeByte(uint32_t, uint8_t);
};