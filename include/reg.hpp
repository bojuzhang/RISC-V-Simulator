#pragma once

#include <cstdint>
class Register {
private:
    uint32_t reg[32];
    uint32_t PC;

public:
    uint32_t read(short pos);
    void write(short pos, uint32_t val);

    void move(uint32_t pos);
    uint32_t getPC();
};