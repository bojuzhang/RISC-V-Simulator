#pragma once
#include "basic_operator.hpp"
#include <cstdint>

enum class FUType { INTEGER, MEMORY, BRANCH };
struct RSData {
    bool busy = false;
    InsType op;
    int32_t rob_index = -1;
    uint32_t pc;
    
    uint32_t vj = 0;
    uint32_t vk = 0;
    int32_t qj = -1;
    int32_t qk = -1;
    
    uint32_t imm = 0;
    FUType fu_type;
};

class RS {
private:
    RSData *stations;
    int32_t cap;

public:
    RS(int32_t);

    int allocate(InsType, uint32_t, uint32_t, int32_t, int32_t, uint32_t, uint32_t, int32_t, FUType);

    RSData get(int32_t);
    void free(int32_t);

    bool isread(int32_t);

    void doit(int32_t, int32_t, uint32_t);
};