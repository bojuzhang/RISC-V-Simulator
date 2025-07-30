#include "rob.hpp"
#include "basic_operator.hpp"
#include "lsb.hpp"
#include "register.hpp"
#include "rs.hpp"
#include <cstdint>

void ROB::link(Register *reg_, RS *rs_, LSB *lsb_, Memory *mem_) {
    reg = reg_;
    rs = rs_;
    lsb = lsb_;
    mem = mem_;
}

void ROB::run() {
    addOP();
    if (nowhead == nowtail) return;
    auto p = now[nowhead];
    if (p.state == ROBSTATE::COMMIT) {
        auto updval = [&](int32_t dest, int32_t val) {
            if (dest != -1) {
                if (reg->getdep(dest) == nowhead) {
                    reg->updatedep(nowhead, -1);
                }
                reg->write(dest, val);
            }
        };
        if (p.op.Getopt() == OpType::B) {
            predictor.update(p.val);
            if (p.val != p.predicted) {
                if (p.val) {
                    nextpc = p.pospc + sext(p.op.Getvals()[2], 13);
                } else {
                    nextpc = p.pospc + 4;
                }
                clear();
                reg->clear();
                rs->clear();
                lsb->clear();
                return;
            }
        } else if (p.op.Getinst() == InsType::SB) {
            mem->store(p.valpos, p.val, 1);
        } else if (p.op.Getinst() == InsType::SH) {
            mem->store(p.valpos, p.val, 2);
        } else if (p.op.Getinst() == InsType::SW) {
            mem->store(p.valpos, p.val, 4);
        } else if (p.op.Getinst() == InsType::JALR) {
            nextpc = p.valpos;
            updval(p.dest, p.val);
        } else {
            updval(p.dest, p.val);
        }
    } else if (p.state == ROBSTATE::ISSUE) {
        p.state = ROBSTATE::EXEC;
        if (p.op.Getopt() == OpType::S || p.op.Getopt() == OpType::IM) {
            LSBData data;
            data.ins = p.op.Getinst();
            data.imm = p.op.Getvals()[2];
            data.dest = nowhead;
            auto rs1 = p.op.Getvals()[0], rs2 = p.op.Getvals()[1];
            auto work = [&](int32_t &q, uint32_t &v, uint32_t rs) {
                int dep = reg->getdep(rs);
                if (dep == -1) {
                    v = reg->read(rs);
                } else {
                    if (next[dep].state == ROBSTATE::COMMIT) {
                        v = next[dep].val;
                    } else {
                        q = dep;
                    }
                }
            };
            work(data.qj, data.vj, rs1);
            if (p.op.Getopt() == OpType::S) {
                work(data.qk, data.vk, rs2);
            }
            lsb->addData(data);
        } else {
            RSData data;
            data.ins = p.op.Getinst();
            data.imm = p.op.Getvals()[2];
            data.dest = nowhead;
            auto rs1 = p.op.Getvals()[0], rs2 = p.op.Getvals()[1];
            auto work = [&](int32_t &q, uint32_t &v, uint32_t rs) {
                int dep = reg->getdep(rs);
                if (dep == -1) {
                    v = reg->read(rs);
                } else {
                    if (next[dep].state == ROBSTATE::COMMIT) {
                        v = next[dep].val;
                    } else {
                        q = dep;
                    }
                }
            };
            work(data.qj, data.vj, rs1);
            if (p.op.Getopt() == OpType::R || p.op.Getopt() == OpType::B) {
                work(data.qk, data.vk, rs2);
            }
            rs->addData(data);
        }
        next[nowhead].state = ROBSTATE::EXEC;
    } else if (p.state == ROBSTATE::WRITE) {
        next[nowhead].state = ROBSTATE::COMMIT;
        // if (p.dest == -1) return;
        lsb->delDep(nowhead, p.val);
        rs->delDep(nowhead, p.val);
    }
}
void ROB::update() {
    for (int i = 0; i < 32; i++) {
        now[i] = next[i];
    }
    nowhead = nexthead, nowtail = nexttail;
    pc = nextpc;
}

void ROB::clear() {
    nowhead = nowtail = 0; // ?
    nexthead = nexttail = 0;
}

ROBData ROB::queryData(int32_t idx) {
    return now[idx];
}
void ROB::modifyData(int32_t idx, const ROBData &data) {
    next[idx] = data;
}

void ROB::addOP() {
    if ((nexttail + 1) % 32 == nexthead) return;
    Operator op = mem->getOp(pc);
    ROBData data;
    data.op = op;
    data.pospc = pc;
    data.predicted = predictor.predict();
    if (op.Getopt() == OpType::B) {
        nextpc = data.predicted ? pc + sext(op.Getvals()[2], 13) : pc + 4;
    } else if (op.Getinst() == InsType::JAL) {
        nextpc = pc + sext(op.Getvals()[2], 21);
    } else {
        nextpc = pc + 4;
    }
    next[nexttail] = data;
    nexttail = (nexttail + 1) % 32;
}