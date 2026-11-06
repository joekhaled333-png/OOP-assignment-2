#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <cstdint>
#include <iostream>

using namespace std;

class screen {
private:
    string FF;
public:
    void write(uint8_t value);
    string getoutput() const;
    void clear();
};

#endif