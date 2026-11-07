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
