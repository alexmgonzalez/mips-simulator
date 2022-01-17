//
//  data_memory.cpp
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 4/19/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "data_memory.h"

using namespace std;

void data_memory::setAddress(string addr){
    address = addr;
}

void data_memory::setWriteData(string wD){
    writeData = wD;
}

void data_memory::setReadData(string rD){
    readData = rD;
}

void data_memory::storeToMemory(string addr){
    
}

string data_memory::loadFromMemory(string addr){
    return memory[0];
}
