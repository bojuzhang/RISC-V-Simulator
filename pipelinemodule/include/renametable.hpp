#pragma once
#include <cstdint>

class RenameTable {
private:
    int32_t table[32];

public:
    RenameTable();
    void clear();

    int32_t get(int32_t idx);
    void set(int32_t idx, int32_t val);
};