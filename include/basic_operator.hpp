#pragma once

#include <array>
#include <cstdint>

enum class OpType {
    U, J, IA, IM, IC, B, S, R, EXIT
};

enum class InsType {
    ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,
    LB, LH, LW, LBU, LHU, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, JALR,
    SB, SH, SW,
    BEQ, BNE, BLT, BGE, BLTU, BGEU,
    JAL,
    LUI, AUIPC
};

class Operator {
private:
    /*
        for R, 0: rd; 1: rs1; 2: rs2

        for I, 0: rs; 1: rs1; 2: offset

        for S, 0: rs1; 1: rs2; 2: offset

        for B, 0: rs1; 1: rs2; 2: offset

        for J, 0: rd; 1: none; 2: offset

        for U, 0: rd; 1: none; 2: offset
    */
    std::array<uint32_t, 3> vals; 
    OpType op;
    InsType ins;

public:
    Operator(uint32_t) ;
    OpType Getopt();
    InsType Getinst();
    std::array<uint32_t, 3> Getvals();
};