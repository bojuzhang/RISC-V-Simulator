#pragma once

#include "basic_operator.hpp"
#include "lsb.hpp"
#include "rs.hpp"
#include <cstdint>
enum class ROBSTATE {
    ISSUE, EXEC, WRITE, COMMIT
};

struct ROBData {
    ROBSTATE state{};
    Operator op;
    int32_t dest = -1;
    int32_t val = 0;
    int32_t valpos = 0;
    int32_t nowcir = 0;
};

class RS;
class LSB;

class ROB {
private:
    ROBData now[32], next[32];
    int nowhead, nowtail;
    int nexthead, nexttail;

    RS *rs;
    LSB *lsb;

public:

    void link(RS *, LSB *);

    void run();
    void update();

    void clear();

    void modifyvalue(int32_t, int32_t);
    void modifystate(int32_t, ROBSTATE);
    void addcir(int32_t, int32_t);
    void modifypos(int32_t, int32_t);
};