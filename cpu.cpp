#include "cpu.h"

cpu::cpu() {
    pc = 0;
    ir = 0;
}

void cpu::setpc(uint8_t value) {
    pc = value;
}

uint8_t cpu::getpc() {
    return pc;
}

void cpu::setir(uint16_t value) {
    ir = value;
}

uint16_t cpu::getir() {
    return ir;
}