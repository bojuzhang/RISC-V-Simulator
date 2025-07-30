#pragma once

#include "basic_operator.hpp"
#include "rob.hpp"
#include <cstdint>
class RSData {
    InsType ins;
    uint32_t vj = 0, vk = 0;
    int32_t qj = -1, qk = -1;
    int32_t imm = 0;
    int32_t dest = -1;
};

class ROB;

class RS {
private:
    RSData now[32], next[32];
    bool visnow[32], visnext[32];

    ROB *rob;

public:
    void link(ROB *);

    void run();
    void update();

    void clear();

    bool full();
    void addData(const RSData &);

    void delDep(int32_t, uint32_t);
};