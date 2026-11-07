#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdint>
using namespace std;


class screen {
    private:
        string FF;
    public:
        void write(uint8_t value ) {
            char ch = static_cast<char>(value);
            FF += ch;
            cout << "[screen output]: " << ch << endl;
        }
        string getoutput() const {
            return FF;
        }
        void clear() {
            FF.clear();
        }
};
class memory {
    private:
        vector<uint8_t> cells;
    public:
        memory(size_t size = 256) : cells(size, 0) {}

        uint8_t getData(uint8_t address) const {
            return cells[address];
        }
        void setData(uint8_t address, uint8_t value,screen& screen) {
            if (address == 0xFF){
                screen.write(value);
            }
                cells[address] = value;
            
        }
        void clear() {
            fill(cells.begin(), cells.end(), 0);
        }

        size_t size() const {
            return cells.size();
        }
    };
    
class Register{
private:
vector <uint8_t> registers;
public:
void reset() {
        for(size_t i = 0; i < 16; i++) {
            registers[i] = 0;
        }
    }
Register(size_t size =16){registers.resize(16,0);
    reset();
};
bool isValidIndex(uint8_t index)const {
   return (index >= 0 && index < 16);
    }
void setRegister(uint8_t index,uint8_t value){
     if(isValidIndex(index)){
registers[index]=value;
}
    else{cout << "invalid index"<<endl;}
}
uint8_t getRegister(uint8_t index)const{
     if(isValidIndex(index)){
    return registers[index]; 
}    else{cout << "invalid index"<<endl;}
}
};


class cpu {
private :
    int pc;
    int ir;
public :
    cpu() {
        pc = 0;
        ir = 0;
    }
    void setpc(int value){
        pc = value;
    }
    int getpc(){
        return pc;
    }
    void setir(int value){
        ir = value;
    }
    int getir(){
        return ir;
    }
    void run(memory& myMem, Register& myRegs, ALU& myAlu, decoder& myDec, screen& myScreen) {
        setpc(0);
        bool isRunning = true;
        while (isRunning) {
            int currentPc = getpc();
            if (currentPc >= myMem.size() - 1) {
                break;
            }
            uint8_t highByte = myMem.getData(currentPc);
            uint8_t lowByte = myMem.getData(currentPc + 1);

            char hexBuffer[5];
            snprintf(hexBuffer, sizeof(hexBuffer), "%02X%02X", highByte, lowByte);
            string instructionHex(hexBuffer);
            setir(stoul(instructionHex, nullptr, 16));
            decoder::decodedinstruction decoded = myDec.decode(instructionHex);
            if (decoded.opcode == 12 && decoded.reg == 0 && decoded.opr1 == 0 && decoded.opr2 == 0) {
                cout << " Program Halted Successfully (C000)" << endl;
                isRunning = false;
                break;
            }
            switch (decoded.opcode) {
                case 1: {
                    int address = (decoded.opr1 << 4) | decoded.opr2;
                    int value = myMem.getData(address);
                    myRegs.setRegister(decoded.reg, value);
                    break;
                }
                case 2: {
                    int value = (decoded.opr1 << 4) | decoded.opr2;
                    myRegs.setRegister(decoded.reg, value);
                    break;
                }
                case 3: {
                    int address = (decoded.opr1 << 4) | decoded.opr2;
                    int value = myRegs.getRegister(decoded.reg);
                    myMem.setData(address, value, myScreen);
                    break;
                }
                case 4: {
                    int value = myRegs.getRegister(decoded.opr2);
                    myRegs.setRegister(decoded.reg, value);
                    break;
                }
                case 5: {
                    int val1 = myRegs.getRegister(decoded.opr1);
                    int val2 = myRegs.getRegister(decoded.opr2);
                    int res = myAlu.add(val1, val2);
                    myRegs.setRegister(decoded.reg, res);
                    break;
                }
                case 7: {
                    int val1 = myRegs.getRegister(decoded.opr1);
                    int val2 = myRegs.getRegister(decoded.opr2);
                    int res = myAlu.OR(val1, val2);
                    myRegs.setRegister(decoded.reg, res);
                    break;
                }
                case 8: {
                    int val1 = myRegs.getRegister(decoded.opr1);
                    int val2 = myRegs.getRegister(decoded.opr2);
                    int res = myAlu.AND(val1, val2);
                    myRegs.setRegister(decoded.reg, res);
                    break;
                }
                default:
                    cout << "Unknown Opcode: " << decoded.opcode << endl;
                    break;
            }
            setpc(currentPc + 2);
        }
    }
};
class ALU{
public:
    int add(int opr1,int opr2){
        return opr1+ opr2;
    }
    int sub(int opr1,int opr2){
        return opr1- opr2;
    }
    int mult(int opr1,int opr2){
        return opr1* opr2;
    }
    int divide(int opr1,int opr2){
        if(opr2==0){
            return 0;
        }
        return opr1/ opr2;
    }
    int OR (int opr1,int opr2){
        return opr1|| opr2;
    }
    int AND (int opr1,int opr2){
        return opr1&&opr2;
    }
};
class decoder{
public:
    struct decodedinstruction {
        int opcode;
        int reg ;
        int opr1;
        int opr2;
    };
    
    decodedinstruction decode (const string&instructionHex){
        decodedinstruction decoded ;
        if (instructionHex .length()!=4){
            return{0,0,0,0};
        }
        decoded.opcode=hexchar_to_int(instructionHex[0]);
        decoded.reg=hexchar_to_int(instructionHex[1]);
        decoded.opr1=hexchar_to_int(instructionHex[2]);
        decoded.opr2=hexchar_to_int(instructionHex[3]);
            return decoded;
    }
    int hexchar_to_int(char c){
        if(c>='0'&&c<='9')return (c-'0');
        if(c>='A'&&c<='F')return (c-'A'+10);
        if(c>='a'&&c<='f')return (c-'a'+10);
        return 0;
    }    
};  

