#include "cdb.hpp"

void CDB::broadcast(int32_t robidx_, int32_t rsidx_, uint32_t result) {
    cdb.robidx = robidx_;
    cdb.rsidx = rsidx_;
    cdb.result = result;
    cdb.valid = 1;
}

bool CDB::has() {
    return cdb.valid;
}

CDBData CDB::getdata() {
    return cdb;
}