#include "register.hpp"

Register::Register() {
    for (int i = 0; i < 32; i++) {
        regnow[i] = regnext[i] = 0;
        depnow[i] = depnext[i] = -1;
    }
}

uint32_t Register::read(short pos) {
    return regnow[pos];
}
void Register::write(short pos, uint32_t val) {
    regnext[pos] = val;
}

uint32_t Register::getdep(short pos) {
    return depnow[pos];
}
void Register::updatedep(short pos, int32_t val) {
    if (pos == 0) return;
    depnext[pos] = val;
}

void Register::update() {
    for (int i = 0; i < 32; i++) {
        regnow[i] = regnext[i];
        depnow[i] = depnext[i];
    }
    regnow[0] = regnext[0] = 0;
}

void Register::clear() {
    for (int i = 0; i < 32; i++) {
        depnow[i] = depnext[i] = -1;
    }
}