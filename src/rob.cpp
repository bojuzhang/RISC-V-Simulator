#include "rob.hpp"
#include "basic_operator.hpp"
#include "lsb.hpp"
#include "register.hpp"
#include "rs.hpp"
#include <cstdint>
#include <iostream>

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
    // std::cerr << (int)p.state << " " << p.pospc << " " << to_string(p.op.Getinst()) << " " << p.op.Getvals()[0] << " " << p.op.Getvals()[1] << " " << p.op.Getvals()[2] << "\n";
     if (p.state == ROBSTATE::COMMIT) {
        for (int i = 0; i < 32; i++) {
            std::cout << reg->read(i) << " ";
        }
        std::cout << "\n";
        auto updval = [&](int32_t dest, int32_t val) {
            if (dest != -1) {
                if (reg->getdep(dest) == nowhead) {
                    reg->updatedep(nowhead, -1);
                }
                reg->write(dest, val);
            }
        };
        if (p.op.Getopt() == OpType::B) {
            predictor.update(p.val == p.predictpc);
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
        } else if (p.op.Getinst() == InsType::LH) {
            auto val = sext(mem->load(p.valpos, 2), 16);
            updval(p.op.Getvals()[0], val);
        } else if (p.op.Getinst() == InsType::LW) {
            auto val = static_cast<int32_t>(mem->load(p.valpos, 4));
            updval(p.op.Getvals()[0], val);
        } else if (p.op.Getinst() == InsType::LBU) {
            auto val = mem->load(p.valpos, 1);
            updval(p.op.Getvals()[0], val);
        } else if (p.op.Getinst() == InsType::LHU) {
            auto val = mem->load(p.valpos, 2);
            updval(p.op.Getvals()[0], val);
        } else if (p.op.Getinst() == InsType::JALR) {
            if (p.val != p.predictpc) {
                // std::cerr << "JALR " << p.val << " " << p.predictpc << "\n";
                nextpc = p.val;
                clear();
                reg->clear();
                rs->clear();
                lsb->clear();
                return;
            }
            updval(p.op.Getvals()[0], p.pospc + 4);
        } else if (p.op.Getinst() == InsType::JAL) {
            // std::cerr << "JAL " << p.op.Getvals()[0] << " " << p.pospc << "\n";
            updval(p.op.Getvals()[0], p.pospc + 4);
        } else {
            updval(p.op.Getvals()[0], p.val);
        }
        nexthead = (nexthead + 1) % 32;
    } else if (p.state == ROBSTATE::ISSUE) {
        if (p.op.Getopt() == OpType::S || p.op.Getopt() == OpType::IM) {
            LSBData data;
            data.ins = p.op.Getinst();
            data.imm = p.op.Getvals()[2];
            data.dest = nowhead;
            
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
            data.dest = nowhead;
            auto rs1 = p.op.Getvals()[1], rs2 = p.op.Getvals()[2];
            if (p.op.Getopt() == OpType::B) {
                rs1 = p.op.Getvals()[0], rs2 = p.op.Getvals()[1];
            }
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
        // std::cerr << "WRITE STAGE\n";
        next[nowhead].state = ROBSTATE::COMMIT;
        // if (p.dest == -1) return;
        lsb->delDep(nowhead, p.val);
        rs->delDep(nowhead, p.val);
    }
}
void ROB::update() {
    // std::cerr << nexthead << " " << nexttail << "\n";
    // for (int i = nexthead; (i + 1) % 32 != nexttail; i = (i + 1) % 32) {
    //     std::cerr << i << " " << to_string(next[i].op.Getinst()) << " " << (int)next[i].state << "\n";
    // }

    // std::cerr << "rob: " << nexthead << " " << nexttail << "\n";
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
    auto predicted =  predictor.predict();
    if (op.Getopt() == OpType::B) {
        nextpc = predicted ? pc + sext(op.Getvals()[2], 13) : pc + 4;
        data.predictpc = nextpc;
    } else if (op.Getinst() == InsType::JAL) {
        nextpc = pc + sext(op.Getvals()[2], 21);
    } else {
        nextpc = pc + 4;
    }
    // std::cerr << pc << " " << nextpc << " " << to_string(op.Getinst()) << "\n";
    next[nexttail] = data;
    nexttail = (nexttail + 1) % 32;
}