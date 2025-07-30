#pragma once

#include <cstdint>
class ALU {
private:
    int32_t sext(uint32_t offset, int32_t bits);
public:
    uint32_t ADD(uint32_t rs1, uint32_t rs2);
    uint32_t SUB(uint32_t rs1, uint32_t rs2);
    uint32_t SLL(uint32_t rs1, uint32_t rs2);
    uint32_t SLT(uint32_t rs1, uint32_t rs2);
    uint32_t SLTU(uint32_t rs1, uint32_t rs2);
    uint32_t XOR(uint32_t rs1, uint32_t rs2);
    uint32_t SRL(uint32_t rs1, uint32_t rs2);
    uint32_t SRA(uint32_t rs1, uint32_t rs2);
    uint32_t OR(uint32_t rs1, uint32_t rs2);
    uint32_t AND(uint32_t rs1, uint32_t rs2);

    uint32_t LB(uint32_t rs1, uint32_t imm);
    uint32_t LH(uint32_t rs1, uint32_t imm);
    uint32_t LW(uint32_t rs1, uint32_t imm);
    uint32_t LBU(uint32_t rs1, uint32_t imm);
    uint32_t LHU(uint32_t rs1, uint32_t imm);

    uint32_t ADDI(uint32_t rs1, uint32_t imm);
    uint32_t SLTI(uint32_t rs1, uint32_t imm);
    uint32_t SLTIU(uint32_t rs1, uint32_t imm);
    uint32_t XORI(uint32_t rs1, uint32_t imm);
    uint32_t ORI(uint32_t rs1, uint32_t imm);
    uint32_t ANDI(uint32_t rs1, uint32_t imm);
    uint32_t SLLI(uint32_t rs1, uint32_t imm);
    uint32_t SRLI(uint32_t rs1, uint32_t imm);
    uint32_t SRAI(uint32_t rs1, uint32_t imm);

    uint32_t BEQ(uint32_t rs1, uint32_t rs2, uint32_t imm);
    uint32_t BNE(uint32_t rs1, uint32_t rs2, uint32_t imm);
    uint32_t BLT(uint32_t rs1, uint32_t rs2, uint32_t imm);
    uint32_t BGE(uint32_t rs1, uint32_t rs2, uint32_t imm);
    uint32_t BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm);
    uint32_t BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm);
};