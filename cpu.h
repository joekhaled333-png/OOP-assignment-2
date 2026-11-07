#ifndef CPU_H
#define CPU_H

#include <string>
#include <cstdint>
#include <iostream>
#include "memory.h"
#include "Register.h"
#include "ALU.h"
#include "decoder.h"
#include "screen.h"

using namespace std;

class cpu {
private:
    uint8_t pc;
    uint16_t ir;

public:
    cpu();

    void setpc(uint8_t value);
    uint8_t getpc() const;

    void setir(uint16_t value);
    uint16_t getir() const;

    string fetch(memory& myMem);
    bool execute(decoder::decodedinstruction decoded, memory& myMem, Register& myRegs, ALU& myAlu, screen& myScreen);
    void run(memory& myMem, Register& myRegs, ALU& myAlu, decoder& myDec, screen& myScreen);
};

#endif