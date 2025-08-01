#include "rob.hpp"
#include "basic_operator.hpp"
#include "lsb.hpp"
#include "predictor.hpp"
#include "register.hpp"
#include "rs.hpp"
#include <cstdint>

void ROB::link(Register *reg_, RS *rs_, LSB *lsb_, Memory *mem_, Predictor *pre_) {
    reg = reg_;
    rs = rs_;
    lsb = lsb_;
    mem = mem_;
    predictor = pre_;
}

void ROB::run() {
    static int cnt = 0;
    addOP();
    if (nowhead == nowtail) return;
    auto p = now[nowhead];
    if (p.state == ROBSTATE::COMMIT) {
        auto updval = [&](int32_t dest, int32_t val) {
            if (dest != -1) {
                if (reg->getdep(dest) == nowhead) {
                    reg->updatedep(dest, -1);
                }
                reg->write(dest, val);
            }
        };
        if (p.op.Getopt() == OpType::B) {
            predictor->update(p.val == p.predictpc);
            if (p.val != p.predictpc) {
                nextpc = p.val;
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
        } else if (p.op.Getinst() == InsType::LB) {
            auto val = sext(mem->load(p.valpos, 1), 8);
            updval(p.op.Getvals()[0], val);
            lsb->delDep(nowhead, val);
            rs->delDep(nowhead, val);
        } else if (p.op.Getinst() == InsType::LH) {
            auto val = sext(mem->load(p.valpos, 2), 16);
            updval(p.op.Getvals()[0], val);
            lsb->delDep(nowhead, val);
            rs->delDep(nowhead, val);
        } else if (p.op.Getinst() == InsType::LW) {
            auto val = static_cast<int32_t>(mem->load(p.valpos, 4));
            updval(p.op.Getvals()[0], val);
            lsb->delDep(nowhead, val);
            rs->delDep(nowhead, val);
        } else if (p.op.Getinst() == InsType::LBU) {
            auto val = mem->load(p.valpos, 1);
            updval(p.op.Getvals()[0], val);
            lsb->delDep(nowhead, val);
            rs->delDep(nowhead, val);
        } else if (p.op.Getinst() == InsType::LHU) {
            auto val = mem->load(p.valpos, 2);
            updval(p.op.Getvals()[0], val);
            lsb->delDep(nowhead, val);
            rs->delDep(nowhead, val);
        } else if (p.op.Getinst() == InsType::JALR) {
            if (p.val != p.predictpc) {
                nextpc = p.val;
                clear();
                reg->clear();
                rs->clear();
                lsb->clear();
                return;
            }
            updval(p.op.Getvals()[0], p.pospc + 4);
            lsb->delDep(nowhead, p.pospc + 4);
            rs->delDep(nowhead, p.pospc + 4);
        } else if (p.op.Getinst() == InsType::JAL) {
            updval(p.op.Getvals()[0], p.pospc + 4);
            lsb->delDep(nowhead, p.pospc + 4);
            rs->delDep(nowhead, p.pospc + 4);
        } else {
            updval(p.op.Getvals()[0], p.val);
            lsb->delDep(nowhead, p.val);
            rs->delDep(nowhead, p.val);
        }
        nexthead = (nexthead + 1) % 32;
        return;
    } 
    for (int i = nowhead; i != nowtail; i = (i + 1) % 32) {
        auto p = now[i];
        if (p.state == ROBSTATE::ISSUE) {
            if (p.op.Getopt() == OpType::S || p.op.Getopt() == OpType::IM) {
                LSBData data;
                data.ins = p.op.Getinst();
                data.imm = p.op.Getvals()[2];
                data.dest = i;
                
                auto work = [&](int32_t &q, uint32_t &v, uint32_t rs) {
                    int dep = reg->getdep(rs);
                    if (dep == -1) {
                        v = reg->read(rs);
                    } else {
                        q = dep;
                    }
                };
                 if (p.op.Getopt() == OpType::S) {
                    work(data.qj, data.vj, p.op.Getvals()[0]);
                    work(data.qk, data.vk, p.op.Getvals()[1]);
                } else {
                    work(data.qj, data.vj, p.op.Getvals()[1]);
                }
                lsb->addData(data);
            } else {
                RSData data;
                data.ins = p.op.Getinst();
                data.imm = p.op.Getvals()[2];
                data.dest = i;
                auto rs1 = p.op.Getvals()[1], rs2 = p.op.Getvals()[2];
                if (p.op.Getopt() == OpType::B) {
                    rs1 = p.op.Getvals()[0], rs2 = p.op.Getvals()[1];
                }
                auto work = [&](int32_t &q, uint32_t &v, uint32_t rs) {
                    int dep = reg->getdep(rs);
                    if (dep == -1) {
                        v = reg->read(rs);
                    } else {
                        q = dep;
                    }
                };
                work(data.qj, data.vj, rs1);
                if (p.op.Getopt() == OpType::R || p.op.Getopt() == OpType::B) {
                    work(data.qk, data.vk, rs2);
                }
                rs->addData(data);
            }

            if (p.op.Getopt() != OpType::B && p.op.Getopt() != OpType::S) {
                reg->updatedep(p.op.Getvals()[0], i);
            }
            next[i].state = ROBSTATE::EXEC;
            break;
        }
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
    if (op.Getopt() == OpType::EXIT) {
        return;
    }
    ROBData data;
    data.op = op;
    data.pospc = pc;
    auto predicted =  predictor->predict();
    if (op.Getopt() == OpType::B) {
        nextpc = predicted ? pc + sext(op.Getvals()[2], 13) : pc + 4;
        data.predictpc = nextpc;
    } else if (op.Getinst() == InsType::JAL) {
        nextpc = pc + sext(op.Getvals()[2], 21);
    } else {
        nextpc = pc + 4;
    }
    next[nexttail] = data;
    nexttail = (nexttail + 1) % 32;
}