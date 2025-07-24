#include "alu.hpp"
#include <cstdint>


void ALU::ADD(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    auto val = memory.read(rs1) + memory.read(rs2);
    memory.write(rd, val);
}
void ALU::SUB(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    auto val = memory.read(rs1) - memory.read(rs2);
    memory.write(rd, val);
}
void ALU::SLL(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    auto val = memory.read(rs1) << memory.read(rs2);
    memory.write(rd, val);
}
void ALU::SLT(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    int32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    memory.write(rd, (v1 < v2) ? 1 : 0);
}
void ALU::SLTU(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    memory.write(rd, (v1 < v2) ? 1 : 0);
}
void ALU::XOR(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    auto val = memory.read(rs1) ^ memory.read(rs2);
    memory.write(rd, val);
}
void ALU::SRL(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    uint32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    memory.write(rd, v1 >> v2);
}
void ALU::SRA(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    int32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    memory.write(rd, v1 >> v2);
}
void ALU::OR(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    auto val = memory.read(rs1) | memory.read(rs2);
    memory.write(rd, val);
}
void ALU::AND(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    auto val = memory.read(rs1) & memory.read(rs2);
    memory.write(rd, val);
}

void ALU::LB(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    int8_t val = memory.getByte(pos);
    memory.write(rd, val);
}
void ALU::LH(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    int16_t val = (memory.getByte(pos) << 8) + memory.getByte(pos + 1);
    memory.write(rd, val);
}
void ALU::LW(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    uint32_t val = (memory.getByte(pos) << 24) + (memory.getByte(pos + 1) << 16)
                    + (memory.getByte(pos + 2) << 8) + memory.getByte(pos + 3);
    memory.write(rd, val);
}
void ALU::LBU(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    uint8_t val = memory.getByte(pos);
    memory.write(rd, val);
}
void ALU::LHU(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    uint16_t val = (memory.getByte(pos) << 8) + memory.getByte(pos + 1);
    memory.write(rd, val);
}
void ALU::ADDI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    auto val = memory.read(rs1) + imm;
    memory.write(rd, val);
}
void ALU::SLTI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t v1 = memory.read(rs1), v2 = imm;
    memory.write(rd, (v1 < v2) ? 1 : 0);
}
void ALU::SLTIU(uint32_t rd, uint32_t rs1, uint32_t imm) {
    uint32_t v1 = memory.read(rs1), v2 = imm;
    memory.write(rd, (v1 < v2) ? 1 : 0);
}
void ALU::XORI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    auto val = memory.read(rs1) ^ imm;
    memory.write(rd, val);
}
void ALU::ORI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    auto val = memory.read(rs1) | imm;
    memory.write(rd, val);
}
void ALU::ANDI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    auto val = memory.read(rs1) & imm;
    memory.write(rd, val);
}
void ALU::SLLI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    auto val = memory.read(rs1) << imm;
    memory.write(rd, val);
}
void ALU::SRLI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    uint32_t v1 = memory.read(rs1);
    auto val = v1 >> imm;
    memory.write(rd, val);
}
void ALU::SRAI(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t v1 = memory.read(rs1);
    auto val = v1 >> imm;
    memory.write(rd, val);
}
void ALU::JALR(uint32_t rd, uint32_t rs1, uint32_t imm) {
    int32_t pc = memory.getPC(), offset = static_cast<int32_t>(imm);
    memory.write(rd, pc + 4);
    memory.move(memory.read(rs1) + offset);
}

void ALU::SB(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    uint8_t val = (memory.read(rs2) << 24) >> 24;
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    memory.writeByte(pos, val);
}
void ALU::SH(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    uint16_t val = (memory.read(rs2) << 16) >> 16;
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    memory.writeByte(pos, val >> 8);
    memory.writeByte(pos + 1, (val << 8) >> 8);
}
void ALU::SW(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    uint32_t val = memory.read(rs2);
    int32_t pos = memory.read(rs1) + static_cast<int32_t>(imm);
    memory.writeByte(pos, val >> 24);
    memory.writeByte(pos + 1, (val << 8) >> 24);
    memory.writeByte(pos + 2, (val << 16) >> 24);
    memory.writeByte(pos + 3, (val << 24) >> 24);
}

void ALU::JAL(uint32_t rd, uint32_t imm) {
    int32_t pc = memory.getPC(), offset = static_cast<int32_t>(imm);
    memory.write(rd, pc + 4);
    memory.move(pc + offset);
}
    
void ALU::LUI(uint32_t rd, uint32_t imm) {
    int32_t offset = static_cast<int32_t>(imm);
    memory.write(rd, offset);
}
void ALU::AUIPC(uint32_t rd, uint32_t imm) {
    int32_t pc = memory.getPC(), offset = static_cast<int32_t>(imm);
    memory.write(rd, pc + offset);
}


void ALU::BEQ(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = static_cast<int32_t>(imm);
    if (memory.read(rs1) == memory.read(rs2)) {
        memory.move(memory.getPC() + offset);
    }
}
void ALU::BNE(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = static_cast<int32_t>(imm);
    if (memory.read(rs1) != memory.read(rs2)) {
        memory.move(memory.getPC() + offset);
    }
}
void ALU::BLT(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = static_cast<int32_t>(imm);
    int32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    if (v1 < v2) {
        memory.move(memory.getPC() + offset);
    }
}
void ALU::BGE(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = static_cast<int32_t>(imm);
    int32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    if (v1 >= v2) {
        memory.move(memory.getPC() + offset);
    }
}
void ALU::BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = static_cast<int32_t>(imm);
    uint32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    if (v1 < v2) {
        memory.move(memory.getPC() + offset);
    }
}
void ALU::BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm) {
    int32_t offset = static_cast<int32_t>(imm);
    uint32_t v1 = memory.read(rs1), v2 = memory.read(rs2);
    if (v1 >= v2) {
        memory.move(memory.getPC() + offset);
    }
}