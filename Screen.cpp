#include "Screen.h"
#include <iostream>
#include <iomanip>


void screen::write(uint8_t value) {
    char ch = static_cast<char>(value);
    FF += ch;
    cout << "[screen output] (Hex): 0x" 
         << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(value) 
         << dec << endl;
}
string screen::getoutput() const {
    return FF;
}
void screen::clear() {
    FF.clear();
}