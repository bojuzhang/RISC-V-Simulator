#include "basic_cpu.hpp"
#include "basic_operator.hpp"
#include <cstdint>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

BasicCPU::BasicCPU() : alu(&mem) { }

void BasicCPU::init() {
    uint32_t pos = 0;
    while(1) {
        std::string token;
        std::cin >> token;
        std::stringstream ss;
        if (token[0] == '@') {
            ss << std::hex << token.substr(1);
            ss >> pos;
        } else {
            ss << std::hex << token;
            uint8_t num;
            ss >> num;
            mem.writeByte(pos, num);
            ++pos;
        }
    }
}
bool BasicCPU::tick() {
    Operator op = mem.getOp(mem.getPC());
    if (op.Getopt() == OpType::EXIT) {
        return true;
    }
    auto vals = op.Getvals();
    auto ins = op.Getinst();
    if (ins == InsType::ADD) {
        alu.ADD(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SUB) {
        alu.SUB(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::AND) {
        alu.AND(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::OR) {
        alu.OR(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::XOR) {
        alu.XOR(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SLL) {
        alu.SLL(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SRL) {
        alu.SRL(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SRA) {
        alu.SRA(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SLT) {
        alu.SLT(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SLTU) {
        alu.SLTU(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::ADDI) {
        alu.ADDI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::ANDI) {
        alu.ANDI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::ORI) {
        alu.ORI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::XORI) {
        alu.XORI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SLLI) {
        alu.SLLI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SRLI) {
        alu.SRLI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SRAI) {
        alu.SRAI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SLTI) {
        alu.SLTI(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SLTIU) {
        alu.SLTIU(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::LB) {
        alu.LB(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::LBU) {
        alu.LBU(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::LH) {
        alu.LH(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::LHU) {
        alu.LHU(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::LW) {
        alu.LW(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SB) {
        alu.SB(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SH) {
        alu.SH(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::SW) {
        alu.SW(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::BEQ) {
        alu.BEQ(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::BGE) {
        alu.BGE(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::BGEU) {
        alu.BGEU(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::BLT) {
        alu.BLT(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::BLTU) {
        alu.BLTU(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::BNE) {
        alu.BNE(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::JAL) {
        alu.JAL(vals[0], vals[2]);
    } else if (ins == InsType::JALR) {
        alu.JALR(vals[0], vals[1], vals[2]);
    } else if (ins == InsType::AUIPC) {
        alu.AUIPC(vals[0], vals[2]);
    } else if (ins == InsType::LUI) {
        alu.LUI(vals[0], vals[2]);
    } 

    if (ins == InsType::ADDI && vals[0] == 10 && vals[1] == 0 && vals[2] == 255) {
        uint8_t ans = mem.read(10) & 0xFFF0;
        std::cout << ans << "\n";
    }

    if (op.Getopt() != OpType::B && op.Getopt() != OpType::J && ins != InsType::JALR) {
        mem.move(mem.getPC() + 4);
    }
    return false;
}
void BasicCPU::main() {
    init();
    while (1) {
        auto flag = tick();
        if (flag) break;
    }
}