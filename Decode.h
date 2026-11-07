#ifndef DECODER_H
#define DECODER_H

#include <string>

class decoder {
public:
    struct decodedinstruction {
        int opcode;
        int reg;
        int opr1;
        int opr2;
    };

    decodedinstruction decode(const std::string& instructionHex);

private:
    int hexchar_to_int(char c);
};

#endif
