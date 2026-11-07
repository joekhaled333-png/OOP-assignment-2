#include "cpu.h"

cpu::cpu() {
    pc = 0;
    ir = 0;
}

void cpu::setpc(uint8_t value) {
    pc = value;
}

uint8_t cpu::getpc() const {
    return pc;
}

void cpu::setir(uint16_t value) {
    ir = value;
}

uint16_t cpu::getir() const {
    return ir;
}

string cpu::fetch(memory& myMem) {
    uint8_t currentPc = getpc();
    uint8_t highByte = myMem.getData(currentPc);
    uint8_t lowByte = myMem.getData(currentPc + 1);

    char hexBuffer[5];
    snprintf(hexBuffer, sizeof(hexBuffer), "%02X%02X", highByte, lowByte);
    string instructionHex(hexBuffer);

    setir(stoul(instructionHex, nullptr, 16));
    return instructionHex;
}

bool cpu::execute(decoder::decodedinstruction decoded, memory& myMem, Register& myRegs, ALU& myAlu, screen& myScreen) {
    if (decoded.opcode == 12 && decoded.reg == 0 && decoded.opr1 == 0 && decoded.opr2 == 0) {
        cout << "Program Halted Successfully (C000)" << endl;
        return false;
    }

    switch (decoded.opcode) {
        case 1: {
            int address = (decoded.opr1 << 4) | decoded.opr2;
            int value = myMem.getData(address);
            myRegs.setRegister(decoded.reg, value);
            break;
        }
        case 2: {
            int value = (decoded.opr1 << 4) | decoded.opr2;
            myRegs.setRegister(decoded.reg, value);
            break;
        }
        case 3: {
            int address = (decoded.opr1 << 4) | decoded.opr2;
            int value = myRegs.getRegister(decoded.reg);
            myMem.setData(address, value, myScreen);
            break;
        }
        case 4: {
            int value = myRegs.getRegister(decoded.opr2);
            myRegs.setRegister(decoded.reg, value);
            break;
        }
        case 5: {
            int val1 = myRegs.getRegister(decoded.opr1);
            int val2 = myRegs.getRegister(decoded.opr2);
            int res = myAlu.add(val1, val2);
            myRegs.setRegister(decoded.reg, res);
            break;
        }
        case 7: {
            int val1 = myRegs.getRegister(decoded.opr1);
            int val2 = myRegs.getRegister(decoded.opr2);
            int res = myAlu.OR(val1, val2);
            myRegs.setRegister(decoded.reg, res);
            break;
        }
        case 8: {
            int val1 = myRegs.getRegister(decoded.opr1);
            int val2 = myRegs.getRegister(decoded.opr2);
            int res = myAlu.AND(val1, val2);
            myRegs.setRegister(decoded.reg, res);
            break;
        }
        default:
            cout << "Unknown Opcode: " << decoded.opcode << endl;
            break;
    }
    return true;
}

void cpu::run(memory& myMem, Register& myRegs, ALU& myAlu, decoder& myDec, screen& myScreen) {
    setpc(0);
    bool isRunning = true;
    while (isRunning) {
        if (getpc() >= myMem.size() - 1) {
            break;
        }
        string instructionHex = fetch(myMem);
        decoder::decodedinstruction decoded = myDec.decode(instructionHex);
        isRunning = execute(decoded, myMem, myRegs, myAlu, myScreen);
        setpc(getpc() + 2);
    }
}