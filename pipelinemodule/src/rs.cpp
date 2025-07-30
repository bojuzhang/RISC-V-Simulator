#include "rs.hpp"

RS::RS(int32_t x) {
    cap = x;
    stations = new RSData[cap];
}
RS::~RS() {
    delete [] stations;
}

int RS::allocate(const RSData &data) {
    for (int i = 0; i < cap; i++) {
        if (!stations[i].busy) {
            stations[i] = data;
            stations[i].busy = 1;
            return i;
        }
    }
    return -1;
}

RSData RS::get(int32_t idx) {
    return stations[idx];
}
void RS::free(int32_t idx) {
    stations[idx].busy = 0;
}

bool RS::isready(int32_t idx) {
    return stations[idx].qj == -1 && stations[idx].qk == -1;
}

void RS::doit(int32_t rsidx, int32_t robidx, uint32_t val) {
    auto &p = stations[rsidx];
    if (p.qj == robidx) {
        p.vj = val;
        p.qj = -1;
    }
    if (p.qk == robidx) {
        p.vk = val;
        p.qk = -1;
    }
}