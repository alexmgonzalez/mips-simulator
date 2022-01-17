//
//  data_memory.h
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 5/9/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//
#include <string>

using namespace std;

class data_memory{
private:
    string address;
    string writeData;
    string readData;
public:
    string memory[1000];
    void setAddress(string);
    void setWriteData(string);
    void setReadData(string);
    void storeToMemory(string);
    string loadFromMemory(string);
};

