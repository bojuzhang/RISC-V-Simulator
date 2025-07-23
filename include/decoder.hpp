#pragma once

#include "basic_operator.hpp"
#include <array>
#include <cstdint>

OpType GetOpType(uint32_t val);

InsType GetInsTypeR(uint32_t val);
InsType GetInsTypeS(uint32_t val);
InsType GetInsTypeB(uint32_t val);
InsType GetInsTypeI(uint32_t val);
InsType GetInsTypeJ(uint32_t val);
InsType GetInsTypeU(uint32_t val);

std::array<uint32_t, 3> GetValR(uint32_t val);
std::array<uint32_t, 3> GetValS(uint32_t val);
std::array<uint32_t, 3> GetValB(uint32_t val);
std::array<uint32_t, 3> GetValI(uint32_t val);
std::array<uint32_t, 3> GetValJ(uint32_t val);
std::array<uint32_t, 3> GetValU(uint32_t val);