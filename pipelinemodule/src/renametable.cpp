#include "renametable.hpp"

RenameTable::RenameTable() {
    clear();
}
void RenameTable::clear() {
    for (int i = 0; i < 32; i++) {
        table[i] = -1;
    }
}

int32_t RenameTable::get(int32_t idx) {
    return table[idx];
}
void RenameTable::set(int32_t idx, int32_t val) {
    table[idx] = val;
}