#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Memory.h"
#include "Register.h"
#include "ALU.h"
#include "Decode.h"
#include "Screen.h"
#include "cpu.h"

using namespace std;

void runInteractiveVoleMachine() {
    memory myMem(256);
    Register myRegs(16);
    ALU myAlu;
    decoder myDec;
    screen myScreen;
    cpu myCpu;

    cout << "=================================================" << endl;
    cout << "       VOLE MACHINE SIMULATION        " << endl;
    cout << "=================================================" << endl;
    cout << "Enter instructions in HEX (e.g., 215B 4012 A202 ...)." << endl;
    cout << "Type 'RUN' on a new line when you are done to execute." << endl;
    cout << "Type 'EXIT' to close the simulator." << endl;
    cout << "-------------------------------------------------" << endl;

    while (true) {

        myMem.clear();
        myRegs.reset();
        myScreen.clear();

        cout << "\n[New Test Case] Enter your program code:" << endl;
        
        vector<string> instructions;
        string input;

        while (true) {
            cout << "> ";
            cin >> input;


            for (auto &c : input) c = toupper(c);

            if (input == "RUN") {
                break;
            }
            if (input == "EXIT") {
                cout << "Exiting simulator" << endl;
                return;
            }


            if (input.length() == 4) {
                instructions.push_back(input);
            } else {
                cout << "  Invalid instruction length ('" << input << "'). Instructions must be 4 HEX characters!" << endl;
            }
        }

        if (instructions.empty()) {
            cout << "No instructions entered!" << endl;
            continue;
        }


        uint8_t currentAddress = 0x00;
        for (const string& inst : instructions) {
            string highByteStr = inst.substr(0, 2);
            string lowByteStr  = inst.substr(2, 2);

            uint8_t highByte = static_cast<uint8_t>(stoul(highByteStr, nullptr, 16));
            uint8_t lowByte  = static_cast<uint8_t>(stoul(lowByteStr, nullptr, 16));

            myMem.setData(currentAddress++, highByte, myScreen);
            myMem.setData(currentAddress++, lowByte, myScreen);
        }

        cout << "\n--- Executing Program (" << instructions.size() << " instructions loaded) ---" << endl;
        

        myCpu.run(myMem, myRegs, myAlu, myDec, myScreen);

        cout << "--- Execution Complete ---" << endl;
        cout << "=================================================" << endl;
    }
}

int main() {
    runInteractiveVoleMachine();
    return 0;
}