#pragma once
#include <cstdint>

struct CDBData {
    int32_t idx = -1;
    uint32_t result = 0;
    bool valid = false;
};

class CDB {
private:
    CDBData cdb;
    
public:
    void broadcast(int32_t rob_index, uint32_t result);
    
    bool has_data();
    
    CDBData get_data();
};