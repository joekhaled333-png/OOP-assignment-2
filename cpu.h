#ifndef CPU_H
#define CPU_H

#include <cstdint>

class cpu {
private:
    uint8_t pc;
    uint16_t ir;
public:
    cpu();
    void setpc(uint8_t value);
    uint8_t getpc();
    void setir(uint16_t value);
    uint16_t getir();
};

#endif