//
//  Registers.cpp
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 4/19/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//

#include <stdio.h>
#include "register_file.h"

void Register_File::setReadAddr1(string rA1){
    readAddr1 = rA1;
}

void Register_File::setReadAddr2(string rA2){
    readAddr2 = rA2;
}

void Register_File::setWriteAddr(string wA){
    writeAddr = wA;
}

void Register_File::setWriteData(string wD){
    writeData = wD;
}

void Register_File::setReadData1(string rD1){
    readData1 = rD1;
}

void Register_File::setReadData2(string rD2){
    readData2 = rD2;
}

string Register_File::getReadAddr1(){
    return readAddr1;
}

string Register_File::getReadAddr2(){
    return readAddr2;
}

string Register_File::getWriteAddr(){
    return writeAddr;
}

string Register_File::getWriteData(){
    return writeData;
}

string Register_File::getReadData1(){
    return readData1;
}

string Register_File::getReadData2(){
    return readData2;
}
