#include "memory.hpp"
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
    if (!memorypc.count(pos)) {
        throw std::runtime_error("invalid pos of operator");
    }
    return memorypc[pos];
}
void Memory::addOp(uint32_t pos, const Operator &op) {
    memorypc[pos] = op;
}

uint8_t Memory::getByte(uint32_t pos) {
    if (!memoryval.count(pos)) {
        return 0;
    }
    return memoryval[pos];
}
void Memory::writeByte(uint32_t pos, uint8_t val) {
    memoryval[pos] = val;
}