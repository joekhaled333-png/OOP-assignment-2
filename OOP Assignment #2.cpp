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


class cpu{
    private :
    int pc;
    int ir;
    public :
    cpu(){
        pc=0;
        ir=0;
    }
    void setpc(int value){
        pc = value;
    }
    int getpc(){
        return pc;
    }
    void setir(int value){
        ir=value;
    }
    int getir(){
        return ir;
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
        if(c>='0'&&c<=9)return (c-'0');
        if(c>='A'&&c<='F')return (c-'A'+10);
        if(c>='a'&&c<='f')return (c-'a'+10);
        return 0;
    }    
};  

