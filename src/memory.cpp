#include "memory.hpp"
#include "basic_operator.hpp"
#include <cstdint>

Operator Memory::getOp(uint32_t pos) {
    uint32_t val = memory[pos] + (memory[pos + 1] << 8) + (memory[pos + 2] << 16) + (memory[pos + 3] << 24);
    return Operator(val);
}

uint8_t Memory::getByte(uint32_t pos) {
    return memory[pos];
}
void Memory::writeByte(uint32_t pos, uint8_t val) {
    memory[pos] = val;
}

void Memory::store(uint32_t pos, uint32_t val, uint32_t len) {
    for (int i = 0; i < len; i++) {
        writeByte(pos + i, val & 0xFF);
        val >>= 8;
    }
}
uint32_t Memory::load(uint32_t pos, uint32_t len) {
    uint32_t res = 0;
    for (int i = 0; i < len; i++) {
        res |= (uint32_t)(getByte(pos + i)) << (i * 8);
    }
    return res;
}