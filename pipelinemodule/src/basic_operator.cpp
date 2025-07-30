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