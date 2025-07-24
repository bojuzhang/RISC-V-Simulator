#include "memory.hpp"
#include <cstdint>

class ALU {
private:
    Memory memory;

public:
    void ADD(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void SUB(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void SLL(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void SLT(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void SLTU(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void XOR(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void SRL(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void SRA(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void OR(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void AND(uint32_t rd, uint32_t rs1, uint32_t rs2);

    void LB(uint32_t rd, uint32_t rs1, uint32_t imm);
    void LH(uint32_t rd, uint32_t rs1, uint32_t imm);
    void LW(uint32_t rd, uint32_t rs1, uint32_t imm);
    void LBU(uint32_t rd, uint32_t rs1, uint32_t imm);
    void LHU(uint32_t rd, uint32_t rs1, uint32_t imm);
    void ADDI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void SLTI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void SLTIU(uint32_t rd, uint32_t rs1, uint32_t imm);
    void XORI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void ORI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void ANDI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void SLLI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void SRLI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void SRAI(uint32_t rd, uint32_t rs1, uint32_t imm);
    void JALR(uint32_t rd, uint32_t rs1, uint32_t imm);

    void SB(uint32_t rs1, uint32_t rs2, uint32_t imm);
    void SH(uint32_t rs1, uint32_t rs2, uint32_t imm);
    void SW(uint32_t rs1, uint32_t rs2, uint32_t imm);

    void JAL(uint32_t rd, uint32_t imm);
    
    void LUI(uint32_t rd, uint32_t imm);
    void AUIPC(uint32_t rd, uint32_t imm);


    void BEQ(uint32_t rs1, uint32_t rs2, uint32_t imm);
    void BNE(uint32_t rs1, uint32_t rs2, uint32_t imm);
    void BLT(uint32_t rs1, uint32_t rs2, uint32_t imm);
    void BGE(uint32_t rs1, uint32_t rs2, uint32_t imm);
    void BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm);
    void BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm);
};