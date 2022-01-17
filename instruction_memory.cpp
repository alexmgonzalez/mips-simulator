//
//  instuction_memory.cpp
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 4/19/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "instruction_memory.h"

using namespace std;

void instr_memory::setInstr(string instruction){
    instr = instruction;
}

void instr_memory::setType(){
    if(instr == "j"){
        type = 'J';
    }
    else if(instr == "add" || instr == "sub" || instr == "mul" || instr == "and" || instr == "or"){
        type = 'R';
    }
    else if(instr == "nop"){
        type = 'N';
    }
    else{
        type = 'I';
    }
}

void instr_memory::setRs(string firstSource){
    Rs = firstSource;
}

void instr_memory::setRt(string secondSource){
    Rt = secondSource;
}

void instr_memory::setRd(string destination){
    Rd = destination;
}

void instr_memory::setImm(string num){
    imm = num;
}

void instr_memory::setAddr(string Addr){
    addr = Addr;
}

string instr_memory::getInstr(){
    return instr;
}

char instr_memory::getType(){
    return type;
}

string instr_memory::getRs(){
    return Rs;
}

string instr_memory::getRt(){
    return Rt;
}

string instr_memory::getRd(){
    return Rd;
}

string instr_memory::getImm(){
    return imm;
}

string instr_memory::getAddr(){
    return addr;
}
