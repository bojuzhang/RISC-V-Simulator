#pragma once

#include "basic_operator.hpp"
#include "lsb.hpp"
#include "memory.hpp"
#include "predictor.hpp"
#include "register.hpp"
#include "rs.hpp"
#include <cstdint>
enum class ROBSTATE {
    ISSUE, EXEC, WRITE, COMMIT
};

struct ROBData {
    ROBSTATE state = ROBSTATE::ISSUE;
    Operator op;
    int32_t dest = -1;
    int32_t val = 0;
    int32_t valpos = 0;
    // int32_t newpc = 0;
    int32_t nowcir = 0;

    bool predicted;
    int32_t pospc;
};

class RS;
class LSB;

class ROB {
private:
    ROBData now[32], next[32];
    int nowhead, nowtail;
    int nexthead, nexttail;

    Register *reg;
    RS *rs;
    LSB *lsb;
    Memory *mem;

    Predictor predictor;

    int pc, nextpc;

public:
    void link(Register *, RS *, LSB *, Memory *);

    void run();
    void update();

    void clear();

    ROBData queryData(int32_t);
    void modifyData(int32_t, const ROBData &);

    void addOP();
};