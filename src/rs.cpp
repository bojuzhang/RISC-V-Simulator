#include "rs.hpp"
#include "basic_operator.hpp"
#include "alu.hpp"
#include "rob.hpp"
#include <cstdint>

void RS::link(ROB *rob_, Memory *mem_) {
    rob = rob_;
    mem = mem_;
}

void RS::run(int32_t nowpc) {
    auto calc = [&](InsType ins, uint32_t vj, uint32_t vk, int32_t imm) {
        uint32_t res = 0;
        if (ins == InsType::ADD) {
            res = ADD(vj, vk);
        } else if (ins == InsType::SUB) {
            res = SUB(vj, vk);
        } else if (ins == InsType::AND) {
            res = AND(vj, vk);
        } else if (ins == InsType::OR) {
            res = OR(vj, vk);
        } else if (ins == InsType::XOR) {
            res = XOR(vj, vk);
        } else if (ins == InsType::SLL) {
            res = SLL(vj, vk);
        } else if (ins == InsType::SRL) {
            res = SRL(vj, vk);
        } else if (ins == InsType::SRA) {
            res = SRA(vj, vk);
        } else if (ins == InsType::SLT) {
            res = SLT(vj, vk);
        } else if (ins == InsType::SLTU) {
            res = SLTU(vj, vk);
        } else if (ins == InsType::ADDI) {
            res = ADDI(vj, imm);
        } else if (ins == InsType::ANDI) {
            res = ANDI(vj, imm);
        } else if (ins == InsType::ORI) {
            res = ORI(vj, imm);
        } else if (ins == InsType::XORI) {
            res = XORI(vj, imm);
        } else if (ins == InsType::SLLI) {
            res = SLLI(vj, imm);
        } else if (ins == InsType::SRLI) {
            res = SRLI(vj, imm);
        } else if (ins == InsType::SRAI) {
            res = SRAI(vj, imm);
        } else if (ins == InsType::SLTI) {
            res = SLTI(vj, imm);
        } else if (ins == InsType::SLTIU) {
            res = SLTIU(vj, imm);
        } else if (ins == InsType::BEQ) {
            res = BEQ(vj, vk);
        } else if (ins == InsType::BGE) {
            res = BGE(vj, vk);
        } else if (ins == InsType::BGEU) {
            res = BGEU(vj, vk);
        } else if (ins == InsType::BLT) {
            res = BLT(vj, vk);
        } else if (ins == InsType::BLTU) {
            res = BLTU(vj, vk);
        } else if (ins == InsType::BNE) {
            res = BNE(vj, vk);
        } else if (ins == InsType::JAL) {
            res = JAL(vj, imm);
        } else if (ins == InsType::JALR) {
            res = JALR(vj, imm);
        } else if (ins == InsType::AUIPC) {
            res = AUIPC(vj, imm);
        } else if (ins == InsType::LUI) {
            res = imm;
        } 
        return res;
    };
    for (int i = 0; i < 32; i++) {
        if (!visnow[i]) continue;
        auto p = now[i];
        if (p.qj == -1 || p.qk == -1) continue;
        auto res = calc(p.ins, p.vj, p.vk, p.imm);
        auto cur = rob->queryData(p.dest)
        ;cur.val = res;
        if (p.ins == InsType::JAL || p.ins == InsType::JALR) {
            cur.newpc = nowpc + 4;
        }
        cur.nowcir = 1;
        cur.state = ROBSTATE::WRITE;
        visnow[i] = 1;
    }
}
void RS::update() {
    for (int i = 0; i < 32; i++) {
        now[i] = next[i];
        visnow[i] = visnext[i];
    }
}

void RS::clear() {
    for (int i = 0; i < 32; i++) {
        visnow[i] = visnext[i] = 0;
    }
}

bool RS::full() {
    for (int i = 0; i < 32; i++) {
        if (!visnext[i]) {
            return false;
        }
    }
    return true;
}
int RS::addData(const RSData &data) {
    for (int i = 0; i < 32; i++) {
        if (!visnext[i]) {
            next[i] = data;
            return i;
        }
    }
    return -1;
}

void RS::delDep(int32_t idx, uint32_t val) {
    for (int i = 0; i < 32; i++) {
        if (!visnext[i]) continue;
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