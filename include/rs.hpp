#pragma once

#include "basic_operator.hpp"
#include "memory.hpp"
#include "rob.hpp"
#include <cstdint>
struct RSData {
    InsType ins;
    uint32_t vj = 0, vk = 0;
    int32_t qj = -1, qk = -1;
    int32_t imm = 0;
    int32_t dest = -1;
};

class ROB;


// designed from discussion with konpaku-ming
class RS {
private:
    RSData now[32], next[32];
    bool visnow[32]{}, visnext[32]{};

    ROB *rob;
    Memory *mem;

public:
    void link(ROB *, Memory *);

    void run();
    void update();

    void clear();

    bool full();
    int addData(const RSData &);

    void delDep(int32_t, uint32_t);
};