#pragma once

#include "calc.hpp"
#include "exec.hpp"
#include "rob.hpp"
#include "rs.hpp"
#include "cdb.hpp"
#include "renametable.hpp"
#include "memory.hpp"
#include <cstdint>

class TomasuloCPU {
private:
    Calc alu;
    Memory mem;
    
    RenameTable rnt;
    ROB rob;
    RS rs;
    CDB cdb;

    ExecuteUnit integerunit, memoryunit, branchunit;

    uint32_t pc, nextpc;

    bool brachmis = false;
    uint32_t recoverpc;

public:
    TomasuloCPU();
    void reset();
    void init();
    void run();

    void issuestage();
    void execstage();
    void writestage();
    void commitstage();
};