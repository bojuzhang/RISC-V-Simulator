#pragma once
#include <cstdint>

struct CDBData {
    int32_t robidx = -1, rsidx = -1;
    uint32_t result = 0;
    bool valid = false;
};

class CDB {
private:
    CDBData cdb;
    
public:
    void broadcast(int32_t, int32_t, uint32_t);
    
    bool has();
    
    CDBData getdata();
};