#include "calc.hpp"
#include "memory.hpp"
#include <cstdint>

int32_t sext(uint32_t offset, int32_t bits) {
    if (offset >> (bits - 1)) {
        offset |= (~0u << bits);
    }
    return static_cast<int32_t>(offset);
}

Calc::Calc(Memory *mem) {
    memory = mem;
}

uint32_t Calc::ADD(uint32_t rs1, uint32_t rs2) {
    auto val = memory->read(rs1) + memory->read(rs2);
    return val;
}
uint32_t Calc::SUB(uint32_t rs1, uint32_t rs2) {
    auto val = memory->read(rs1) - memory->read(rs2);
    return val;
}
uint32_t Calc::SLL(uint32_t rs1, uint32_t rs2) {
    auto val = memory->read(rs1) << memory->read(rs2);
    return val;
}
uint32_t Calc::SLT(uint32_t rs1, uint32_t rs2) {
    int32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    return (v1 < v2) ? 1 : 0;
}
uint32_t Calc::SLTU(uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    return (v1 < v2) ? 1 : 0;
}
uint32_t Calc::XOR(uint32_t rs1, uint32_t rs2) {
    auto val = memory->read(rs1) ^ memory->read(rs2);
    return val;
}
uint32_t Calc::SRL(uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    return v1 >> v2;
}
uint32_t Calc::SRA(uint32_t rs1, uint32_t rs2) {
    int32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    return v1 >> v2;
}
uint32_t Calc::OR(uint32_t rs1, uint32_t rs2) {
    auto val = memory->read(rs1) | memory->read(rs2);
    return val;
}
uint32_t Calc::AND(uint32_t rs1, uint32_t rs2) {
    auto val = memory->read(rs1) & memory->read(rs2);
    return val;
}

uint32_t Calc::LB(uint32_t rs1, uint32_t imm) {
    int32_t pos = memory->read(rs1) + sext(imm, 12);
    int8_t val = sext(memory->getByte(pos), 8);
    return val;
}
uint32_t Calc::LH(uint32_t rs1, uint32_t imm) {
    int32_t pos = memory->read(rs1) + sext(imm, 12);
    int16_t val = sext((memory->getByte(pos + 1) << 8) + memory->getByte(pos), 16);
    return val;
}
uint32_t Calc::LW(uint32_t rs1, uint32_t imm) {
    int32_t pos = memory->read(rs1) + sext(imm, 12);
    uint32_t val = (memory->getByte(pos + 3) << 24) + (memory->getByte(pos + 2) << 16)
                    + (memory->getByte(pos + 1) << 8) + memory->getByte(pos);
    return val;
}
uint32_t Calc::LBU(uint32_t rs1, uint32_t imm) {
    int32_t pos = memory->read(rs1) + sext(imm, 12);
    uint8_t val = memory->getByte(pos);
    return val;
}
uint32_t Calc::LHU(uint32_t rs1, uint32_t imm) {
    int32_t pos = memory->read(rs1) + sext(imm, 12);
    uint16_t val = (memory->getByte(pos + 1) << 8) + memory->getByte(pos);
    return val;
}
uint32_t Calc::ADDI(uint32_t rs1, uint32_t imm) {
    auto val = memory->read(rs1) + sext(imm, 12);
    return val;
}
uint32_t Calc::SLTI(uint32_t rs1, uint32_t imm) {
    int32_t v1 = memory->read(rs1), v2 = sext(imm, 12);
    return (v1 < v2) ? 1 : 0;
}
uint32_t Calc::SLTIU(uint32_t rs1, uint32_t imm) {
    uint32_t v1 = memory->read(rs1), v2 = sext(imm, 12);
    return (v1 < v2) ? 1 : 0;
}
uint32_t Calc::XORI(uint32_t rs1, uint32_t imm) {
    auto val = memory->read(rs1) ^ sext(imm, 12);
    return val;
}
uint32_t Calc::ORI(uint32_t rs1, uint32_t imm) {
    auto val = memory->read(rs1) | sext(imm, 12);
    return val;
}
uint32_t Calc::ANDI(uint32_t rs1, uint32_t imm) {
    auto val = memory->read(rs1) & sext(imm, 12);
    return val;
}
uint32_t Calc::SLLI(uint32_t rs1, uint32_t imm) {
    imm &= 0x1F;
    auto val = memory->read(rs1) << imm;
    return val;
}
uint32_t Calc::SRLI(uint32_t rs1, uint32_t imm) {
    imm &= 0x1F;
    uint32_t v1 = memory->read(rs1);
    auto val = v1 >> imm;
    return val;
}
uint32_t Calc::SRAI(uint32_t rs1, uint32_t imm) {
    imm &= 0x1F;
    int32_t v1 = memory->read(rs1);
    auto val = v1 >> imm;
    return val;
}

// uint32_t Calc::JALR(uint32_t rs1, uint32_t imm) {
//     int32_t pc = memory->getPC(), offset = sext(imm, 12);
//     memory->write(rd, pc + 4);
//     memory->move(memory->read(rs1) + offset);
// }

// uint32_t Calc::SB(uint32_t rs2, uint32_t imm) {
//     uint8_t val = (memory->read(rs2) << 24) >> 24;
//     int32_t pos = memory->read(rs1) + sext(imm, 12);
//     memory->writeByte(pos, val);
// }
// uint32_t Calc::SH(uint32_t rs2, uint32_t imm) {
//     uint16_t val = (memory->read(rs2) << 16) >> 16;
//     int32_t pos = memory->read(rs1) + sext(imm, 12);
//     memory->writeByte(pos + 1, val >> 8);
//     memory->writeByte(pos, (val << 8) >> 8);
// }
// uint32_t Calc::SW(uint32_t rs2, uint32_t imm) {
//     uint32_t val = memory->read(rs2);
//     int32_t pos = memory->read(rs1) + sext(imm, 12);
//     memory->writeByte(pos + 3, val >> 24);
//     memory->writeByte(pos + 2, (val << 8) >> 24);
//     memory->writeByte(pos + 1, (val << 16) >> 24);
//     memory->writeByte(pos, (val << 24) >> 24);
// }

// uint32_t Calc::JAL(uint32_t imm) {
//     int32_t pc = memory->getPC(), offset = sext(imm, 21);
//     memory->write(rd, pc + 4);
//     memory->move(pc + offset);
// }
    
// uint32_t Calc::LUI(uint32_t imm) {
//     // int32_t offset = sext(imm, 32);
//     memory->write(rd, imm);
// }
// uint32_t Calc::AUIPC(uint32_t imm) {
//     int32_t pc = memory->getPC(), offset = sext(imm, 32);
//     memory->write(rd, pc + offset);
// }


uint32_t Calc::BEQ(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = sext(imm, 13);
    if (memory->read(rs1) == memory->read(rs2)) {
        return offset;
    } else {
        return 4;
    }
}
uint32_t Calc::BNE(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = sext(imm, 13);
    if (memory->read(rs1) != memory->read(rs2)) {
        return offset;
    } else {
        return 4;
    }
}
uint32_t Calc::BLT(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = sext(imm, 13);
    int32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    if (v1 < v2) {
        return offset;
    } else {
        return 4;
    }
}
uint32_t Calc::BGE(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = sext(imm, 13);
    int32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    if (v1 >= v2) {
        return offset;
    } else {
        return 4;
    }
}
uint32_t Calc::BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = sext(imm, 13);
    uint32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    if (v1 < v2) {
        return offset;
    } else {
        return 4;
    }
}
uint32_t Calc::BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = sext(imm, 13);
    uint32_t v1 = memory->read(rs1), v2 = memory->read(rs2);
    if (v1 >= v2) {
        return offset;
    } else {
        return 4;
    }
}