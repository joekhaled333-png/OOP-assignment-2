#include "ALU.h"

int ALU::add(int val1, int val2) {
    return val1 + val2;
}
int ALU::sub(int val1, int val2) {
    return val1 - val2;
}
int ALU::mult(int val1, int val2) {
    return val1 * val2;
}
int ALU::divide(int val1, int val2) {
    return val1 / val2;
}

int ALU::OR(int val1, int val2) {
    return val1 | val2;
}

int ALU::AND(int val1, int val2) {
    return val1 & val2;
}
int ALU::XOR(int val1, int val2) {
    return val1 ^ val2;
}
int ALU::floatAdd(int val1, int val2) {

    auto decodeFloat = [](int val) {
        int sign = (val >> 7) & 0x01;
        int exp = (val >> 4) & 0x07;
        int mantissa = val & 0x0F;
        double realVal = mantissa * 0.0625;
        if (exp >= 4) {
            realVal *= (1 << (exp - 4));
        } else {
            realVal /= (1 << (4 - exp));
        }
        if (sign) realVal = -realVal;
        return realVal;
    };

    double d1 = decodeFloat(val1);
    double d2 = decodeFloat(val2);
    double sum = d1 + d2;

    return static_cast<int>(sum);
}
