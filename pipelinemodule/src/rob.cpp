#include "rob.hpp"

ROB::ROB(int32_t cap_) {
    cap = cap_;
    ops = new ROBData[cap]{};
    head = tail = 0;
}
ROB::~ROB() {
    delete [] ops;
}

bool ROB::full() {
    return (tail + 1) % cap == head;
}
bool ROB::empty() {
    return head == tail;
}

ROBData ROB::get(int32_t idx) {
    return ops[idx];
}
ROBData ROB::front() {
    return ops[head];
}

ROBData ROB::commit() {
    auto p = ops[head];
    head = (head + 1) % cap;
    return p;
}


int32_t ROB::add(uint32_t pc, InsType ins, int32_t dst, bool ismem, bool isjmp) {
    if (full()) return -1;
    ROBData &p = ops[tail];
    p.pc = pc, p.instype = ins, p.destination = dst;
    p.isstore = ismem, p.isjump = isjmp;

    int tmp = tail;
    tail = (tail + 1) % cap;
    return tmp;
}

void ROB::modifyresult(int32_t idx, uint32_t val) {
    ops[idx].result = val;
}
void ROB::modifyadd(int32_t idx, uint32_t val) {
    ops[idx].add = val;
}
void ROB::modifyval(int32_t idx, uint32_t val) {
    ops[idx].val = val;
}
void ROB::modifyready(int32_t idx, bool val) {
    ops[idx].isready = val;
}
void ROB::modifyidx(int32_t idx, int32_t val) {
    ops[idx].rsidx = val;
}