#include "basic_operator.hpp"
#include "tomasulo_cpu.hpp"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

TomasuloCPU::TomasuloCPU() : alu(&mem), rob(32), rs(16), 
                            integerunit(&mem, 1), memoryunit(&mem, 3),
                            branchunit(&mem, 1) {
    reset();
}

void TomasuloCPU::reset() {
    pc = 0;
    nextpc = 0;
}
void TomasuloCPU::init() {
    uint32_t pos = 0;
    std::string token;
    while (std::cin >> token) {
        std::stringstream ss;
        if (token[0] == '@') {
            ss << std::hex << token.substr(1);
            ss >> pos;
        } else {
            ss << std::hex << token;
            uint32_t num;
            ss >> num;
            mem.writeByte(pos, num);
            ++pos;
        }
    }
}
void TomasuloCPU::run() {
    
}

void TomasuloCPU::issuestage() {
    Operator op = Operator(mem.getOp(pc));
    bool ismem = op.Getopt() == OpType::S || op.Getopt() == OpType::IM;
    bool isbrach = op.Getopt() == OpType::B;

    auto getval = [&](int idx) -> uint32_t {
        if (idx == 0) return 0;
        int robidx = rnt.get(idx);
        auto p = rob.get(robidx);
        if (p.isready) {
            return p.result;
        }
        return 0;
    };
    auto getdep = [&](int idx) -> uint32_t {
        if (idx == 0) return -1;
        int robidx = rnt.get(idx);
        auto p = rob.get(robidx);
        if (p.isready) {
            return p.result;
        }
        return -1;
    };
}
void TomasuloCPU::execstage() {}
void TomasuloCPU::writestage() {}
void TomasuloCPU::commitstage() {}