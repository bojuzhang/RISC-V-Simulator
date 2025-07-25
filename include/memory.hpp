#pragma once

#include "basic_operator.hpp"
#include <cstdint>
#include <unordered_map>
class Memory {
private:
    uint32_t reg[32]{};
    uint32_t PC{};

    std::unordered_map<uint32_t, uint8_t> memory;

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