#include "basic_operator.hpp"
#include <cstdint>
#include "decoder.hpp"

Operator::Operator(uint32_t val) {
    op = GetOpType(val);
    if (op == OpType::R) {
        ins = GetInsTypeR(val);
        vals = GetValR(val);
    } else if (op == OpType::S) {
        ins = GetInsTypeS(val);
        vals = GetValS(val);
    } else if (op == OpType::IA) {
        ins = GetInsTypeIA(val);
        vals = GetValI(val);
    } else if (op == OpType::IC) {
        ins = GetInsTypeIC(val);
        vals = GetValI(val);
    } else if (op == OpType::IM) {
        ins = GetInsTypeIM(val);
        vals = GetValI(val);
    } else if (op == OpType::B) {
        ins = GetInsTypeB(val);
        vals = GetValB(val);
    } else if (op == OpType::U) {
        ins = GetInsTypeU(val);
        vals = GetValU(val);
    } else if (op == OpType::J) {
        ins = GetInsTypeJ(val);
        vals = GetValJ(val);
    }
}

OpType Operator::Getopt() {
    return op;
}
InsType Operator::Getinst() {
    return ins;
}
std::array<uint32_t, 3> Operator::Getvals() {
    return vals;
}

int32_t sext(uint32_t offset, int32_t bits) {
    if (offset >> (bits - 1)) {
        offset |= (~0u << bits);
    }
    return static_cast<int32_t>(offset);
}

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