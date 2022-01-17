//
//  register_file.h
//  MIPS_Simulator
//
//  Created by Alex Gonzalez on 5/9/20.
//  Copyright © 2020 Alex Gonzalez. All rights reserved.
//

#include <string>

using namespace std;

class Register_File{
    private:
        string readAddr1;
        string readAddr2;
        string writeAddr;
        string writeData;
        string readData1;
        string readData2;
public:
    void setReadAddr1(string);
    void setReadAddr2(string);
    void setWriteAddr(string);
    void setWriteData(string);
    void setReadData1(string);
    void setReadData2(string);
    string getReadAddr1();
    string getReadAddr2();
    string getWriteAddr();
    string getWriteData();
    string getReadData1();
    string getReadData2();
};


