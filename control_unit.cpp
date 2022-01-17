//
//  Control_Unit.cpp
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 5/10/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//

#include <stdio.h>
#include "control_unit.h"

using namespace std;

void control_unit::RegDstOnOff(string regdst){
    if(regdst == "add" || regdst == "sub" || regdst == "mul"|| regdst == "and"|| regdst == "or"){
        RegDst = "1";
    }
    else if(regdst == "sw" || regdst == "beq" || regdst == "j"){
        RegDst = "X";
    }
    else{
        RegDst = "0";
    }
}

void control_unit::RegWriteOnOff(string regwrite){
    if(regwrite == "add" || regwrite == "sub"|| regwrite == "mul"|| regwrite == "and"|| regwrite == "or" || regwrite == "lw" || regwrite == "addi" || regwrite == "sll"|| regwrite == "srl"){
        RegWrite = "1";
    }
    else{
        RegWrite = "0";
    }
}

void control_unit::ALUSrcOnOff(string alusrc){
    if(alusrc == "addi" || alusrc == "sll"|| alusrc == "srl" || alusrc == "lw" || alusrc == "sw"){
        ALUSrc = "1";
    }
    else if(alusrc == "j"){
        ALUSrc = "X";
    }
    else{
        ALUSrc = "0";
    }
}

void control_unit::PCSrcOnOff(string pcsrc){
    if(pcsrc == "beq"){
        PCSrc = "1";
    }
    else{
        PCSrc = "0";
    }
}

void control_unit::MemWriteOnOff(string memwrite){
    if(memwrite == "sw"){
        MemWrite = "1";
    }
    else{
        MemWrite = "0";
    }
}

void control_unit::MemReadOnOff(string memread){
    if(memread == "lw"){
        MemRead = "1";
    }
    else{
        MemRead = "0";
    }
}

void control_unit::MemtoRegOnOff(string memtoreg){
    if(memtoreg == "lw"){
        MemtoReg = "0";
    }
    else if(memtoreg == "j" || memtoreg == "sw" || memtoreg == "beq" ){
        MemtoReg = "X";
    }
    else{
        MemtoReg = "1";
    }
}

string control_unit::RegDstState(){
    return RegDst;
}

string control_unit::RegWriteState(){
    return RegWrite;
}

string control_unit::ALUSrcState(){
    return ALUSrc;
}

string control_unit::PCSrcState(){
    return PCSrc;
}

string control_unit::MemWriteState(){
    return MemWrite;
}

string control_unit::MemReadState(){
    return MemRead;
}

string control_unit::MemtoRegState(){
    return MemtoReg;
}
