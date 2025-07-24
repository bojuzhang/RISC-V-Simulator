#include "memory.hpp"
#include "basic_operator.hpp"
#include <cstdint>
#include <stdexcept>

uint32_t Memory::read(short pos) {
    return reg[pos];
}
void Memory::write(short pos, uint32_t val) {
    reg[pos] = val;
}

void Memory::move(uint32_t pos) {
    PC = pos;
}
uint32_t Memory::getPC() {
    return PC;
}

Operator Memory::getOp(uint32_t pos) {
    uint32_t val = memory[pos] + (memory[pos + 1] << 8) + (memory[pos + 2] << 16) + (memory[pos + 3] << 24);
    return Operator(val);
}
void Memory::addOp(uint32_t pos, const Operator &op) {
    // memory[pos] = op;
    throw std::runtime_error("deleted ways");
}

uint8_t Memory::getByte(uint32_t pos) {
    return memory[pos];
}
void Memory::writeByte(uint32_t pos, uint8_t val) {
    memory[pos] = val;
}