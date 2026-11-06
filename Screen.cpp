#include "Screen.h"

void screen::write(uint8_t value) {
    char ch = static_cast<char>(value);
    FF += ch;
    cout << "[screen output]: " << ch << endl;
}
string screen::getoutput() const {
    return FF;
}
void screen::clear() {
    FF.clear();
}