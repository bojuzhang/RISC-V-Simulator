#pragma once
#include "calc.hpp"
#include "rs.hpp"
#include <cstdint>

class ExecuteUnit {    
private:
    Calc alu;
    int32_t numcir, nowcir = 0;
    int32_t rsidx = -1;
    int32_t robidx = -1;
    
public:
    ExecuteUnit(Memory*, int32_t);
    bool is_busy();
    
    void execute(int32_t, int32_t, const RSData&);
    
    bool tick(uint32_t &);
    
    void reset();
};