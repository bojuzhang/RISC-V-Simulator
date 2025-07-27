#pragma once
#include "alu.hpp"
#include "rs.hpp"
#include <cstdint>

class ExecuteUnit {    
private:
    ALU alu;
    bool isbusy = 0;
    int32_t rsidx = -1;
    int32_t robidx = -1;
    
public:
    ExecuteUnit(Memory*);
    bool is_busy();
    
    void execute(int, int, const RSData&);
    
    bool tick(uint32_t &);
    
    void reset();
};