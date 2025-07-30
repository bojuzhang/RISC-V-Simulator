#pragma once
#include "basic_operator.hpp"
#include <cstdint>

struct ROBData {
    bool isready = false;
    bool isexcuted = false;
    bool isstore = false;
    uint32_t pc;
    InsType instype;
    int32_t destination = -1;
    uint32_t result = 0;
    uint32_t add = 0, val = 0;
    int32_t rsidx = -1;

    bool isjump = false;
    uint32_t jumpto = 0;
};

class ROB {
private:
    ROBData *ops;
    int32_t head, tail;
    int32_t cap;

public:
    ROB(int32_t cap_);
    ~ROB();

    bool full();
    bool empty();

    ROBData get(int32_t);
    ROBData front();

    ROBData commit();


    int32_t add(uint32_t, InsType, int32_t, bool, bool);

    void modifyresult(int32_t, uint32_t);
    void modifyadd(int32_t, uint32_t);
    void modifyval(int32_t, uint32_t);
    void modifyready(int32_t, bool);
    void modifyidx(int32_t, int32_t);
};