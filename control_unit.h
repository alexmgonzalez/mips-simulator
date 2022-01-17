//
//  control_unit.h
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 5/10/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//

#include <string>

using namespace std;

class control_unit{
private:
    string RegDst;
    string RegWrite;
    string ALUSrc;
    string PCSrc;
    string MemWrite;
    string MemRead;
    string MemtoReg;
public:
    void RegDstOnOff(string);
    void RegWriteOnOff(string);
    void ALUSrcOnOff(string);
    void PCSrcOnOff(string);
    void MemWriteOnOff(string);
    void MemReadOnOff(string);
    void MemtoRegOnOff(string);
    string RegDstState();
    string RegWriteState();
    string ALUSrcState();
    string PCSrcState();
    string MemWriteState();
    string MemReadState();
    string MemtoRegState();
};
