#ifndef REGISTER_H
#define REGISTER_H

#include <vector>
#include <cstdint>

class Register {
private:
    std::vector<uint8_t> registers;

public:
    Register(size_t size = 16);
    void reset();
    bool isValidIndex(uint8_t index) const;
    void setRegister(uint8_t index, uint8_t value);
    uint8_t getRegister(uint8_t index) const;
};

#endif 