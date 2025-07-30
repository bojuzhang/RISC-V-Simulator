#include <cstdint>
#include "alu.hpp"
#include "basic_operator.hpp"

uint32_t ADD(uint32_t rs1, uint32_t rs2) {
    auto val = rs1 + rs2;
    return val;
}
uint32_t SUB(uint32_t rs1, uint32_t rs2) {
    auto val = rs1 - rs2;
    return val;
}
uint32_t SLL(uint32_t rs1, uint32_t rs2) {
    auto val = rs1 << rs2;
    return val;
}
uint32_t SLT(uint32_t rs1, uint32_t rs2) {
    int32_t v1 = rs1, v2 = rs2;
    return (v1 < v2) ? 1 : 0;
}
uint32_t SLTU(uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = rs1, v2 = rs2;
    return (v1 < v2) ? 1 : 0;
}
uint32_t XOR(uint32_t rs1, uint32_t rs2) {
    auto val = rs1 ^ rs2;
    return val;
}
uint32_t SRL(uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = rs1, v2 = rs2;
    return v1 >> v2;
}
uint32_t SRA(uint32_t rs1, uint32_t rs2) {
    int32_t v1 = rs1, v2 = rs2;
    return v1 >> v2;
}
uint32_t OR(uint32_t rs1, uint32_t rs2) {
    auto val = rs1 | rs2;
    return val;
}
uint32_t AND(uint32_t rs1, uint32_t rs2) {
    auto val = rs1 & rs2;
    return val;
}

uint32_t ADDI(uint32_t rs1, uint32_t imm) {
    auto val = rs1 + sext(imm, 12);
    return val;
}
uint32_t SLTI(uint32_t rs1, uint32_t imm) {
    int32_t v1 = rs1, v2 = sext(imm, 12);
    return (v1 < v2) ? 1 : 0;
}
uint32_t SLTIU(uint32_t rs1, uint32_t imm) {
    uint32_t v1 = rs1, v2 = sext(imm, 12);
    return (v1 < v2) ? 1 : 0;
}
uint32_t XORI(uint32_t rs1, uint32_t imm) {
    auto val = rs1 ^ sext(imm, 12);
    return val;
}
uint32_t ORI(uint32_t rs1, uint32_t imm) {
    auto val = rs1 | sext(imm, 12);
    return val;
}
uint32_t ANDI(uint32_t rs1, uint32_t imm) {
    auto val = rs1 & sext(imm, 12);
    return val;
}
uint32_t SLLI(uint32_t rs1, uint32_t imm) {
    imm &= 0x1F;
    auto val = rs1 << imm;
    return val;
}
uint32_t SRLI(uint32_t rs1, uint32_t imm) {
    imm &= 0x1F;
    uint32_t v1 = rs1;
    auto val = v1 >> imm;
    return val;
}
uint32_t SRAI(uint32_t rs1, uint32_t imm) {
    imm &= 0x1F;
    int32_t v1 = rs1;
    auto val = v1 >> imm;
    return val;
}

uint32_t JALR(uint32_t rs1, uint32_t imm) {
    int32_t offset = sext(imm, 12);
    return rs1 + offset;
}

uint32_t JAL(uint32_t rs1, uint32_t imm) {
    int32_t offset = sext(imm, 21);
    return rs1 + offset;
}
uint32_t AUIPC(uint32_t rs1, uint32_t imm) {
    int32_t offset = sext(imm, 32);
    return rs1 + offset;
}


uint32_t BEQ(uint32_t rs1, uint32_t rs2) {
    if (rs1 == rs2) {
        return 1;
    } else {
        return 0;
    }
}
uint32_t BNE(uint32_t rs1, uint32_t rs2) {
    if (rs1 != rs2) {
        return 1;
    } else {
        return 0;
    }
}
uint32_t BLT(uint32_t rs1, uint32_t rs2) {
    int32_t v1 = rs1, v2 = rs2;
    if (v1 < v2) {
        return 1;
    } else {
        return 0;
    }
}
uint32_t BGE(uint32_t rs1, uint32_t rs2) {
    int32_t v1 = rs1, v2 = rs2;
    if (v1 >= v2) {
        return 1;
    } else {
        return 0;
    }
}
uint32_t BLTU(uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = rs1, v2 = rs2;
    if (v1 < v2) {
        return 1;
    } else {
        return 0;
    }
}
uint32_t BGEU(uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = rs1, v2 = rs2;
    if (v1 >= v2) {
        return 1;
    } else {
        return 0;
    }
}