//
//  instruction_memory.h
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 5/9/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//
#include <string>

using namespace std;

class instr_memory{
private:
    string instr;
    char type;
    string Rs;
    string Rt;
    string Rd;
    string imm;
    string addr;
public:
    void setInstr(string);
    void setType();
    void setRs(string);
    void setRt(string);
    void setRd(string);
    void setImm(string);
    void setAddr(string);
    string getInstr();
    char getType();
    string getRs();
    string getRt();
    string getRd();
    string getImm();
    string getAddr();
};


