#include "Register.h"
#include <iostream>

using namespace std;

Register::Register(size_t size) {
    registers.resize(16, 0);
    reset();
}

void Register::reset() {
    for (size_t i = 0; i < 16; i++) {
        registers[i] = 0;
    }
}

bool Register::isValidIndex(uint8_t index) const {
    return (index >= 0 && index < 16);
}

void Register::setRegister(uint8_t index, uint8_t value) {
    if (isValidIndex(index)) {
        registers[index] = value;
    } else {
        cout << "invalid index" << endl;
    }
}

uint8_t Register::getRegister(uint8_t index) const {
    if (isValidIndex(index)) {
        return registers[index];
    } else {
        cout << "invalid index" << endl;
        return 0;
    }
}