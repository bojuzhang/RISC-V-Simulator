#include "lsb.hpp"
#include "basic_operator.hpp"
#include "memory.hpp"
#include "rob.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>

void LSB::link(ROB *rob_, Memory *mem_) {
    rob = rob_;
    mem = mem_;
}

void LSB::run() {
    if (nowhead == nowtail) return;
    auto p = now[nowhead];
    if (p.qj != -1 || p.qk != -1) return;
    int32_t pos = p.vj + sext(p.imm, 12);
    auto cur = rob->queryData(p.dest);
    cur.nowcir++;
    if (cur.nowcir == 3) {
        cur.val = p.vk;
        cur.valpos = pos;
        cur.state = ROBSTATE::WRITE;
        nexthead = (nexthead + 1) % 32;
    }
    rob->modifyData(p.dest, cur);
}
void LSB::update() {
    // std::cerr << "lsb: " << nexthead << " " << nexttail << "\n";
    for (int i = 0; i < 32; i++) {
        now[i] = next[i];
    }
    nowhead = nexthead, nowtail = nexttail;
}

void LSB::clear() {
    nowhead = nowtail = 0; // ?
    nexthead = nexttail = 0;
}

bool LSB::full() {
    return (nexttail + 1) % 32 == nexthead;
}
void LSB::addData(const LSBData &data) {
    next[nexttail] = data;
    nexttail = (nexttail + 1) % 32;
}

void LSB::delDep(int32_t idx, uint32_t val) {
    if (nexthead == nexttail) return;
    for (int i = nexthead; i != nexttail; i = (i + 1) % 32) {
        auto &p = next[i];
        // std::cerr << "deltest " << i << " " << p.qj << " " << p.qk << " " << idx << "\n";
        if (p.qj == idx) {
            p.qj = -1;
            p.vj = val;
        }
        if (p.qk == idx) {
            p.qk = -1;
            p.vk = val;
        }
    }
}