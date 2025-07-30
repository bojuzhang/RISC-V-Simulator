#include "lsb.hpp"
#include "basic_operator.hpp"
#include "memory.hpp"
#include "rob.hpp"
#include <cstdint>
#include <stdexcept>

void LSB::link(ROB *rob_, Memory *mem_) {
    rob = rob_;
    mem = mem_;
}

void LSB::run() {
    if (nowhead == nowtail) return;
    auto p = now[nowhead];
    if (p.qj != -1 || p.qk != -1) return;
    int32_t pos = p.vj + p.imm;
    auto workL = [&](int32_t bit, bool issigned) {
        auto cur = rob->queryData(p.dest);
        cur.nowcir++;
        if (cur.nowcir == 3) {
            int32_t val;
            if (issigned) {
                val = sext(mem->load(pos, bit / 8), bit);
            } else {
                val = mem->load(pos, bit / 8);
            }
            cur.val = val;
            cur.state = ROBSTATE::WRITE;
            rob->modifyData(p.dest, cur);
            nexthead++;
        }
    };
    auto workS = [&]() {
        auto cur = rob->queryData(p.dest);
        cur.nowcir++;
        if (cur.nowcir == 3) {
            cur.val = p.vk;
            cur.valpos = pos;
            cur.state = ROBSTATE::WRITE;
            rob->modifyData(p.dest, cur);
            nexthead++;
        }
    };
    if (p.ins == InsType::LB) {
        workL(8, 1);
    } else if (p.ins == InsType::LH) {
        workL(16, 1);
    } else if (p.ins == InsType::LW) {
        workL(32, 1);
    } else if (p.ins == InsType::LBU) {
        workL(8, 0);
    } else if (p.ins == InsType::LHU) {
        workL(16, 0);
    } else if (p.ins == InsType::SB || p.ins == InsType::SW || p.ins == InsType::SH) {
        workS();
    } else {
        throw std::runtime_error("invalid lsb-instype");
    }
}
void LSB::update() {
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
    for (int i = nexthead; i < nexttail; i = (i + 1) % 32) {
        auto &p = next[i];
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