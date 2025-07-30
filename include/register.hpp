#pragma once

#include <cstdint>

class Register {
private:
    uint32_t regnow[32]{};
    uint32_t regnext[32]{};
    int32_t depnow[32];
    int32_t depnext[32];

public:
    Register();

    uint32_t read(short pos);
    void write(short pos, uint32_t val);

    uint32_t getdep(short pos);
    void updatedep(short pos, int32_t val);

    void update();
};