#include "exec.hpp"
#include <cstdint>

ExecuteUnit::ExecuteUnit(Memory *mem, int32_t cirs) : alu(mem) {
    numcir = cirs;
}
bool ExecuteUnit::is_busy() {
    return nowcir > 0;
}

void ExecuteUnit::execute(int32_t rsidx_, int32_t robidx_, const RSData& data) {
    rsidx = rsidx_;
    robidx = robidx_;
    
}

bool ExecuteUnit::tick(uint32_t &) {

}

void ExecuteUnit::reset() {

}