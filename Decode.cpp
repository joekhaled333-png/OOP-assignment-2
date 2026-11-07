#include "Decoder.h"

decoder::decodedinstruction decoder::decode(const std::string& instructionHex) {
    decodedinstruction decoded;
    if (instructionHex.length() != 4) {
        return {0, 0, 0, 0};
    }
    decoded.opcode = hexchar_to_int(instructionHex[0]);
    decoded.reg    = hexchar_to_int(instructionHex[1]);
    decoded.opr1   = hexchar_to_int(instructionHex[2]);
    decoded.opr2   = hexchar_to_int(instructionHex[3]);
    return decoded;
}

int decoder::hexchar_to_int(char c) {
    if (c >= '0' && c <= '9') return (c - '0');
    if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
    return 0;
}
