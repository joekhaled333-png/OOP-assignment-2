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

