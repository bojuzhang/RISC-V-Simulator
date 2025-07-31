#include "tomasulo.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

TomasuloCPU::TomasuloCPU() {
    rob.link(&reg, &rs, &lsb, &mem);
    rs.link(&rob, &mem);
    lsb.link(&rob, &mem);
}

void TomasuloCPU::init() {
    uint32_t pos = 0;
    std::string token;
    while(std::cin >> token) {
        std::stringstream ss;
        if (token[0] == '@') {
            ss << std::hex << token.substr(1);
            ss >> pos;
        } else {
            ss << std::hex << token;
            uint32_t num;
            ss >> num;
            mem.writeByte(pos, num);
            // std::cerr << std::dec << pos << " " << num << " " << token << "\n";
            ++pos;
        }
    }
}
void TomasuloCPU::run() {
    while (1) {
        // std::cerr << "pc: " << rob.pc << "\n";
        // std::ifstream tty("/dev/tty");
        // std::cout << "Press Enter to continue..." << std::flush;
        // tty.get();  // 等待用户从终端输入
        if (mem.load(rob.pc, 4) == 0x0ff00513) {
            std::cout << (reg.read(10) & 0xFF) << "\n";
            break;
        }

        rob.run();
        rs.run();
        lsb.run();

        rob.update();
        rs.update();
        lsb.update();
        reg.update();
    }
}