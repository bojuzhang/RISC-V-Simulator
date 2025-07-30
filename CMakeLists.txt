cmake_minimum_required(VERSION 3.16)
project(Simulator)

include_directories(include)

add_executable(code src/basic_operator.cpp
                    src/decoder.cpp
                    src/register.cpp
                    src/alu.cpp
                    src/lsb.cpp
                    src/main.cpp
                    src/memory.cpp
                    src/predictor.cpp
                    src/rob.cpp
                    src/rs.cpp
                    src/tomasulo.cpp)