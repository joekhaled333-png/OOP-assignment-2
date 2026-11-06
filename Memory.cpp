#include "Memory.h"

memory::memory(size_t size) : cells(size, 0) {}

uint8_t memory::getData(uint8_t address) const {
    return cells[address];
}

void memory::setData(uint8_t address, uint8_t value, screen& scr) {
    if (address == 0xFF) {
        scr.write(value);
    }
    cells[address] = value;
}

void memory::clear() {
    fill(cells.begin(), cells.end(), 0);
}

size_t memory::size() const {
    return cells.size();
}