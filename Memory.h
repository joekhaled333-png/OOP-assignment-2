#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <cstdint>
#include <algorithm>
#include "Screen.h"

using namespace std;

class memory {
private:
    vector<uint8_t> cells;
public:
    memory(size_t size = 256);
    uint8_t getData(uint8_t address) const;
    void setData(uint8_t address, uint8_t value, screen& scr);
    void clear();
    size_t size() const;
};

#endif