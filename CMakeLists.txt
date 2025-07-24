cmake_minimum_required(VERSION 3.16)
project(Simulator)

include_directories(include)

add_executable(code src/basic_operator.cpp
                    src/alu.cpp
                    src/basic_cpu.cpp
                    src/decoder.cpp
                    src/main.cpp
                    src/memory.cpp)