#pragma once

#include "basic_operator.hpp"
#include "lsb.hpp"
#include "memory.hpp"
#include "predictor.hpp"
#include "register.hpp"
#include "rs.hpp"
#include <cstdint>
enum class ROBSTATE {
    ISSUE, EXEC, COMMIT
};

struct ROBData {
    ROBSTATE state = ROBSTATE::ISSUE;
    Operator op;
    uint32_t val = 0;
    int32_t valpos = 0;
    int32_t nowcir = 0;

    int32_t predictpc, calcpc;
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

    Predictor *predictor;  

public:
    int pc, nextpc;

    void link(Register *, RS *, LSB *, Memory *, Predictor *);

    void run();
    void update();

    void clear();

    ROBData queryData(int32_t);
    void modifyData(int32_t, const ROBData &);

    void addOP();
};