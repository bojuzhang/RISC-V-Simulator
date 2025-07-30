#include "basic_cpu.hpp"
#include "basic_operator.hpp"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

const char* to_string(InsType type) {
    switch (type) {
        case InsType::ADD: return "ADD";
        case InsType::SUB: return "SUB";
        case InsType::SLL: return "SLL";
        case InsType::SLT: return "SLT";
        case InsType::SLTU: return "SLTU";
        case InsType::XOR: return "XOR";
        case InsType::SRL: return "SRL";
        case InsType::SRA: return "SRA";
        case InsType::OR: return "OR";
        case InsType::AND: return "AND";

        case InsType::LB: return "LB";
        case InsType::LH: return "LH";
        case InsType::LW: return "LW";
        case InsType::LBU: return "LBU";
        case InsType::LHU: return "LHU";
        case InsType::ADDI: return "ADDI";
        case InsType::SLTI: return "SLTI";
        case InsType::SLTIU: return "SLTIU";
        case InsType::XORI: return "XORI";
        case InsType::ORI: return "ORI";
        case InsType::ANDI: return "ANDI";
        case InsType::SLLI: return "SLLI";
        case InsType::SRLI: return "SRLI";
        case InsType::SRAI: return "SRAI";
        case InsType::JALR: return "JALR";

        case InsType::SB: return "SB";
        case InsType::SH: return "SH";
        case InsType::SW: return "SW";

        case InsType::BEQ: return "BEQ";
        case InsType::BNE: return "BNE";
        case InsType::BLT: return "BLT";
        case InsType::BGE: return "BGE";
        case InsType::BLTU: return "BLTU";
        case InsType::BGEU: return "BGEU";

        case InsType::JAL: return "JAL";
        case InsType::LUI: return "LUI";
        case InsType::AUIPC: return "AUIPC";

        default: return "UNKNOWN";
    }
}

BasicCPU::BasicCPU() : alu(&mem) { }

void BasicCPU::init() {
    uint32_t pos = 0;
    std::string token;
    while(std::cin >> token) {
        std::stringstream ss;
        if (token[0] == '@') {
            ss << std::hex << token.substr(1);
            ss >> pos;
        } else {
            ss << std::hex << token;
            uint32_t num;
            ss >> num;
            mem.writeByte(pos, num);
            // std::cerr << std::dec << pos << " " << num << " " << token << "\n";
            ++pos;
        }
    }
}
bool BasicCPU::tick() {
    Operator op = mem.getOp(mem.getPC());
    auto vals = op.Getvals();
    auto ins = op.Getinst();
    // std::cerr << mem.getPC() << " " << to_string(ins) << " " << vals[0] << " " << vals[1] << " " << vals[2] << "\n";
    if (op.Getopt() == OpType::EXIT) {
        return true;
    }
    if (ins == InsType::ADDI && vals[0] == 10 && vals[1] == 0 && vals[2] == 255) {
        uint32_t ans = mem.read(10) & 0xFF;
        std::cout << ans << "\n";
        return true;
    }
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

    mem.write(0, 0);

    // for (int i = 0; i < 32; i++) {
    //     std::cerr << mem.read(i) << " ";
    // }
    // std::cerr << "\n";

    

    if (op.Getopt() != OpType::B && op.Getopt() != OpType::J && ins != InsType::JALR) {
        // std::cerr << "PC puls 4!\n";
        mem.move(mem.getPC() + 4);
    }

    
    return false;
}
void BasicCPU::main() {
    init();
    while(1) {
        // std::ifstream tty("/dev/tty");
        // std::cout << "Press Enter to continue..." << std::flush;
        // tty.get();  // 等待用户从终端输入
        auto flag = tick();
        if (flag) break;
    }
}