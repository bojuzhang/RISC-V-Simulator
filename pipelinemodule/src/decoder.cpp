#include "basic_operator.hpp"
#include "decoder.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>

OpType GetOpType(uint32_t val) {
    auto tp = (val << 25) >> 25;
    // std::cerr << tp << "\n";
    if (tp == 0b0110011) {
        return OpType::R;
    } else if (tp == 0b0010011) {
        return OpType::IA;
    } else if(tp == 0b0000011) {
        return OpType::IM;
    } else if(tp == 0b1100111) {
        return OpType::IC;
    } else if (tp == 0b0100011) {
        return OpType::S;
    } else if (tp == 0b0010111 || tp == 0b0110111) {
        return OpType::U;
    } else if (tp == 0b1101111) {
        return OpType::J;
    } else if (tp == 0b1100011) {
        return OpType::B;
    }
    return OpType::EXIT;
}

InsType GetInsTypeR(uint32_t val) {
    auto func3 = (val << 17) >> 29, func7 = val >> 25;
    if (func3 == 0b000) {
        if (func7 == 0b0000000) {
            return InsType::ADD;
        } else if (func7 == 0b0100000) {
            return InsType::SUB;
        }
    } else if (func3 == 0b111) {
        return InsType::AND;
    } else if (func3 == 0b110) {
        return InsType::OR;
    } else if (func3 == 0b100) {
        return InsType::XOR;
    } else if (func3 == 0b001) {
        return InsType::SLL;
    } else if (func3 == 0b101) {
        if (func7 == 0b0000000) {
            return InsType::SRL;
        } else if (func7 == 0b0100000) {
            return InsType::SRA;
        }
    } else if (func3 == 0b010) {
        return InsType::SLT;
    } else if (func3 == 0b011) {
        return InsType::SLTU;
    }
    throw std::runtime_error("invalid instype");
}
InsType GetInsTypeS(uint32_t val) {
    auto func3 = (val << 17) >> 29;
    if (func3 == 0b000) {
        return InsType::SB;
    } else if (func3 == 0b001) {
        return InsType::SH;
    } else if (func3 == 0b010) {
        return InsType::SW;
    }
    throw std::runtime_error("invalid instype");
}
InsType GetInsTypeB(uint32_t val) {
    auto func3 = (val << 17) >> 29;
    if (func3 == 0b000) {
        return InsType::BEQ;
    } else if (func3 == 0b111) {
        return InsType::BGEU;
    } else if (func3 == 0b110) {
        return InsType::BLTU;
    } else if (func3 == 0b100) {
        return InsType::BLT;
    } else if (func3 == 0b001) {
        return InsType::BNE;
    } else if (func3 == 0b101) {
        return InsType::BGE;
    }
    throw std::runtime_error("invalid instype");
}
InsType GetInsTypeIA(uint32_t val) {
    auto func3 = (val << 17) >> 29, func7 = val >> 25;
    if (func3 == 0b000) {
        return InsType::ADDI;
    } else if (func3 == 0b111) {
        return InsType::ANDI;
    } else if (func3 == 0b110) {
        return InsType::ORI;
    } else if (func3 == 0b100) {
        return InsType::XORI;
    } else if (func3 == 0b001) {
        return InsType::SLLI;
    } else if (func3 == 0b101) {
        if (func7 == 0b0000000) {
            return InsType::SRLI;
        } else if (func7 == 0b0100000) {
            return InsType::SRAI;
        }
    } else if (func3 == 0b010) {
        return InsType::SLTI;
    } else if (func3 == 0b011) {
        return InsType::SLTIU;
    }
    throw std::runtime_error("invalid instype");
}
InsType GetInsTypeIM(uint32_t val) {
    auto func3 = (val << 17) >> 29, func7 = val >> 25;
    if (func3 == 0b000) {
        return InsType::LB;
    }else if (func3 == 0b100) {
        return InsType::LBU;
    } else if (func3 == 0b001) {
        return InsType::LH;
    } else if (func3 == 0b101) {
        return InsType::LHU;
    } else if (func3 == 0b010) {
        return InsType::LW;
    }
    throw std::runtime_error("invalid instype");
}
InsType GetInsTypeIC(uint32_t val) {
    return InsType::JALR;
}
InsType GetInsTypeJ(uint32_t val) {
    return InsType::JAL;
}
InsType GetInsTypeU(uint32_t val) {
    auto tp = (val << 25) >> 25;
    if (tp == 0b0110111) {
        return InsType::LUI;
    } else if (tp == 0b0010111) {
        return InsType::AUIPC;
    }
    throw std::runtime_error("invalid instype");
}

std::array<uint32_t, 3> GetValR(uint32_t val) {
    std::array<uint32_t, 3> res;
    res[0] = (val << 20) >> 27;
    res[1] = (val << 12) >> 27;
    res[2] = (val << 7) >> 27;
    return res;
}
std::array<uint32_t, 3> GetValS(uint32_t val) {
    std::array<uint32_t, 3> res;
    res[0] = (val << 12) >> 27;
    res[1] = (val << 7) >> 27;
    res[2] = ((val << 20) >> 27) + ((val & 0xFE000000) >> 20);
    // std::cerr << "test ooooooooooops! " << res[2] << " " << ((val << 20) >> 27) << " " << ((val & 0xFE000000) >> 20) << "\n";
    return res;
}
std::array<uint32_t, 3> GetValB(uint32_t val) {
    std::array<uint32_t, 3> res;
    res[0] = (val << 12) >> 27;
    res[1] = (val << 7) >> 27;
    res[2] = (((val >> 7) & 1) << 11) + (((val >> 8) & 0xF) << 1) + (((val >> 25) & 0x3F) << 5) + (((val >> 31) & 1) << 12);
    // std::cerr << res[0] << " " << res[1] << "\n";
    // std::cerr << "testB ooooooooooop! " << res[2] << " " << (((val >> 8) & 0xF) << 1) << "\n";
    return res;
}
std::array<uint32_t, 3> GetValI(uint32_t val) {
    std::array<uint32_t, 3> res;
    res[0] = (val << 20) >> 27;
    res[1] = (val << 12) >> 27;
    res[2] = val >> 20;
    return res;
}
std::array<uint32_t, 3> GetValJ(uint32_t val) {
    std::array<uint32_t, 3> res;
    res[0] = (val << 20) >> 27;
    res[1] = 0;
    res[2] = (val & 0xFF000) + (((val >> 20 & 1)) << 11) + (((val << 1) >> 22) << 1) + ((val >> 31) << 20);
    return res;
}
std::array<uint32_t, 3> GetValU(uint32_t val) {
    std::array<uint32_t, 3> res;
    res[0] = (val << 20) >> 27;
    res[1] = 0;
    res[2] = (val >> 12) << 12;
    return res;
}