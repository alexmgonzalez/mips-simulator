

#include <iostream>
#include <fstream>
#include <iomanip>
#include "instruction_memory.h"
#include "register_file.h"
#include "alu.h"
#include "data_memory.h"
#include "control_unit.h"

using namespace std;

const int INSTRUCTION_COUNT = 1000;

int main() {
    
    struct Instruction{
        string instr;
        string rs;
        string rd;
        string rt;
        string imm;
        string addr;
        string label;
        char type;
    };
    
    struct Label{
        string label;
        int index;
        string used;
    };
    
    instr_memory instrMem;
    Register_File regFile;
    ALU alu;
    data_memory dataMem;
    control_unit cu;
    
    Instruction instr_list[INSTRUCTION_COUNT];
    Label label_list[INSTRUCTION_COUNT];
    string Instr;
    string Rs;
    string Rd;
    string Rt;
    string Imm;
    string Addr;
    string Label;
    
    string RegDst[1000];
    string RegWrite[1000];
    string ALUSrc[1000];
    string PCSrc[1000];
    string MemWrite[1000];
    string MemRead[1000];
    string MemtoReg[1000];
    
    string readAddr1[1000];
    string readAddr2[1000];
    string writeAddr[1000];
    string writeData[1000];
    string readData1[1000];
    string readData2[1000];
    string usedInstr[1000];
    
    for(int i = 0; i < 1000; i++){
        dataMem.memory[i] = "Empty";
    }
    
    string file;
    cout << "Please enter assembly file name including extension: ";
    cin >> file;
    
    ifstream fin;                       //text file
    fin.open(file);
    if(!fin){
        cout << "ERROR: file not found" << endl;
        return 0;
    }
    string line;
    int count = 0;
    int amountOfLabels = 0;//stores the amount of items in the file
    if(count < INSTRUCTION_COUNT){
        
        while (fin >> Instr){
            if(Instr == "j"){
                instr_list[count].instr = Instr;
                fin >> Addr;
                
                instr_list[count].addr = Addr;
                instr_list[count].type = 'J';
                count++;
            }
            else if(Instr == "add" || Instr == "sub" || Instr == "mul" || Instr == "and" || Instr == "or"){
                instr_list[count].instr = Instr;
                fin >> Rd >> Rs >> Rt;
                
                instr_list[count].rs = Rs;
                instr_list[count].rs.pop_back();
                instr_list[count].rt = Rt;
                instr_list[count].rd = Rd;
                instr_list[count].rd.pop_back();
                instr_list[count].type = 'R';
                count++;
            }
            else if(Instr == "nop"){
                instr_list[count].instr = Instr;
                instr_list[count].rs = "Empty";
                instr_list[count].rt = "Empty";
                instr_list[count].rd = "Empty";
                instr_list[count].imm = "Empty";
                count++;
            }
            else if(Instr == "addi"|| Instr == "sll" || Instr == "srl"){
                instr_list[count].instr = Instr;
                fin >> Rd >> Rs >> Imm;
                
                instr_list[count].rd = Rd;
                instr_list[count].rd.pop_back();
                instr_list[count].rs = Rs;
                instr_list[count].rs.pop_back();
                instr_list[count].imm = Imm;
                instr_list[count].type = 'I';
                count++;
            }
            else if(Instr == "sw" || Instr == "lw"){
                instr_list[count].instr = Instr;
                fin >> Rt >> Rs;
                
                instr_list[count].rt = Rt;
                instr_list[count].rt.pop_back();
                instr_list[count].rs = Rs.substr(2,2);
                instr_list[count].addr = Rs.substr(0,1);;
                instr_list[count].type = 'I';
                count++;
            }
            else if(Instr == "beq"){
                instr_list[count].instr = Instr;
                fin >> Rs >> Rt >> Addr;
                
                instr_list[count].rs = Rs;
                instr_list[count].rs.pop_back();
                instr_list[count].rt = Rt;
                instr_list[count].rt.pop_back();
                instr_list[count].addr = Addr;
                instr_list[count].type = 'I';
                count++;
            }
            else{
                label_list[amountOfLabels].label = Instr;
                label_list[amountOfLabels].label.pop_back();
                label_list[amountOfLabels].index = count;
                label_list[amountOfLabels].used = "N";
                amountOfLabels++;
            }
        }
    }
    
    fin.close();
    
    int memory_size = 1000;
    int memUsed = 0;
    int PC = 0;
    int i = 0;
    bool equal = true;
    while(i < count){
        regFile.setReadAddr1("X");
        regFile.setReadAddr2("X");
        regFile.setWriteAddr("X");
        regFile.setWriteData("X");
        regFile.setReadData1("X");
        regFile.setReadData2("X");
        
        if(instr_list[i].type == 'R'){
            instrMem.setInstr(instr_list[i].instr);
            instrMem.setRs(instr_list[i].rs);
            instrMem.setRt(instr_list[i].rt);
            instrMem.setRd(instr_list[i].rd);
            
            regFile.setReadAddr1(instr_list[i].rs);
            regFile.setReadAddr2(instr_list[i].rt);
            regFile.setWriteAddr(instr_list[i].rd);
            
            regFile.setReadData1(instr_list[i].rs);
            regFile.setReadData2(instr_list[i].rt);
            
            alu.setReg1(instr_list[i].rs);
            alu.setReg2(instr_list[i].rt);
            
            if(instr_list[i].instr == "add"){
                regFile.setWriteData(instr_list[i].rs + " + " + instr_list[i].rt);
            }
            else if(instr_list[i].instr == "sub"){
                regFile.setWriteData(instr_list[i].rs + " - " + instr_list[i].rt);
            }
            else if(instr_list[i].instr == "mul"){
                regFile.setWriteData(instr_list[i].rs + " * " + instr_list[i].rt);
            }
            else if(instr_list[i].instr == "or"){
                regFile.setWriteData(instr_list[i].rs + " || " + instr_list[i].rt);
            }
            else if(instr_list[i].instr == "and"){
                regFile.setWriteData(instr_list[i].rs + " && " + instr_list[i].rt);
            }
        }
        else if(instr_list[i].type == 'I'){
            if(instr_list[i].instr == "addi"){
                instrMem.setInstr(instr_list[i].instr);
                instrMem.setRd(instr_list[i].rd);
                instrMem.setRs(instr_list[i].rs);
                instrMem.setImm(instr_list[i].imm);
                
                regFile.setReadAddr1(instr_list[i].rs);
                regFile.setWriteAddr(instr_list[i].rd);
                
                regFile.setReadData1(instr_list[i].rs);
                
                alu.setReg1(instr_list[i].rs);
                alu.setReg2(instr_list[i].imm);
                
                regFile.setWriteData(instr_list[i].rs + " + " + instr_list[i].imm);
            }
            else if(instr_list[i].instr == "sw"){
                instrMem.setInstr(instr_list[i].instr);
                instrMem.setRt(instr_list[i].rt);
                instrMem.setRs(instr_list[i].rs);
                instrMem.setAddr(instr_list[i].addr);
                
                regFile.setReadAddr1(instr_list[i].rt);
                regFile.setReadAddr2(instr_list[i].rs);
                
                regFile.setReadData1(instr_list[i].rs);
                regFile.setReadData2(instr_list[i].rt);
                
                alu.setReg1(instr_list[i].rs);
                alu.setReg2(instr_list[i].addr);
                
                int offset;
                try {
                    offset = stoi(instr_list[i].addr) / 4;
                } catch (const exception& e) {
                    cout << "ERROR: Wrong Offset" << endl;
                }
                
                dataMem.memory[offset] = regFile.getReadData2();
                memUsed++;
            }
            else if(instr_list[i].instr == "lw"){
                instrMem.setInstr(instr_list[i].instr);
                instrMem.setRt(instr_list[i].rt);
                instrMem.setRs(instr_list[i].rs);
                instrMem.setAddr(instr_list[i].addr);
                
                regFile.setReadAddr1(instr_list[i].rs);
                regFile.setWriteAddr(instr_list[i].rt);
                
                regFile.setReadData1(instr_list[i].rs);
                
                alu.setReg1(instr_list[i].rs);
                alu.setReg2(instr_list[i].addr);
                
                int offset;
                try {
                    offset = stoi(instr_list[i].addr) / 4;
                } catch (const exception& e) {
                    cout << "ERROR: Wrong Offset" << endl;
                }
                
                regFile.setWriteData(dataMem.memory[offset]);
                
            }
            else if(instr_list[i].instr == "beq"){
                instrMem.setInstr(instr_list[i].instr);
                instrMem.setRs(instr_list[i].rs);
                instrMem.setRt(instr_list[i].rt);
                instrMem.setAddr(instr_list[i].addr);
                
                regFile.setReadAddr1(instr_list[i].rs);
                regFile.setReadAddr2(instr_list[i].rt);
                
                regFile.setReadData1(instr_list[i].rs);
                regFile.setReadData2(instr_list[i].rt);
                
                alu.setReg1(instr_list[i].rs);
                alu.setReg2(instr_list[i].rt);
                
                
                if(equal){
                    for(int j = 0; j < amountOfLabels; j++){
                        if(label_list[j].label == instrMem.getAddr() && label_list[j].used == "N"){
                            i = label_list[j].index-1;
                            equal = false;
                            label_list[j].used = "Y";
                        }
                    }
                }

            }
            else if(instr_list[i].instr == "sll"){
                instrMem.setInstr(instr_list[i].instr);
                instrMem.setRs(instr_list[i].rs);
                instrMem.setImm(instr_list[i].imm);
                
                regFile.setReadAddr1(instr_list[i].rs);
                regFile.setWriteAddr(instr_list[i].rd);
                
                regFile.setReadData1(instr_list[i].rs);
                
                alu.setReg1(instr_list[i].rs);
                alu.setReg2(instr_list[i].imm);
                
                regFile.setWriteData(instr_list[i].rs + " shifted left by " + instr_list[i].imm + "bits");
            }
            else if(instr_list[i].instr == "srl"){
                instrMem.setInstr(instr_list[i].instr);
                instrMem.setRs(instr_list[i].rs);
                instrMem.setImm(instr_list[i].imm);
                
                regFile.setReadAddr1(instr_list[i].rs);
                regFile.setWriteAddr(instr_list[i].rd);
                
                regFile.setReadData1(instr_list[i].rs);
                
                alu.setReg1(instr_list[i].rs);
                alu.setReg2(instr_list[i].imm);
                
                regFile.setWriteData(instr_list[i].rs + " shifted right by " + instr_list[i].imm + "bits");
            }
        }
        else if(instr_list[i].instr == "nop"){
            instrMem.setInstr(instr_list[i].instr);
            instrMem.setRs(instr_list[i].rs);
            instrMem.setRt(instr_list[i].rt);
            instrMem.setRd(instr_list[i].rd);
            instrMem.setRd(instr_list[i].imm);
            
            regFile.setReadAddr1("Empty");
            regFile.setReadAddr2("Empty");
            regFile.setWriteAddr("Empty");
            regFile.setWriteData("Empty");
            regFile.setReadData1("Empty");
            regFile.setReadData2("Empty");
            
            alu.setReg1("Empty");
            alu.setReg2("Empty");
        }
        else{
            instrMem.setInstr(instr_list[i].instr);
            instrMem.setAddr(instr_list[i].addr);
            for(int j = 0; j < amountOfLabels; j++){
                if(label_list[j].label == instrMem.getAddr() && label_list[j].used == "N"){
                    i = label_list[j].index-1;
                    label_list[j].used = "Y";
                }
            }
        }
        
        cu.RegDstOnOff(instrMem.getInstr());
        cu.RegWriteOnOff(instrMem.getInstr());
        cu.ALUSrcOnOff(instrMem.getInstr());
        cu.PCSrcOnOff(instrMem.getInstr());
        cu.MemWriteOnOff(instrMem.getInstr());
        cu.MemReadOnOff(instrMem.getInstr());
        cu.MemtoRegOnOff(instrMem.getInstr());
        
        RegDst[PC] = cu.RegDstState();
        RegWrite[PC] = cu.RegWriteState();
        ALUSrc[PC] = cu.ALUSrcState();
        PCSrc[PC] = cu.PCSrcState();
        MemWrite[PC] = cu.MemWriteState();
        MemRead[PC] = cu.MemReadState();
        MemtoReg[PC] = cu.MemtoRegState();
        
        readAddr1[PC] = regFile.getReadAddr1();
        readAddr2[PC] = regFile.getReadAddr2();
        writeAddr[PC] = regFile.getWriteAddr();
        writeData[PC] = regFile.getWriteData();
        readData1[PC] = regFile.getReadData1();
        readData2[PC] = regFile.getReadData2();
        
        usedInstr[PC] = instrMem.getInstr();
        
        i++;
        PC++;
    }

    cout << "-------------------------" << endl
         << "|Register File:         |" << endl
         << "-------------------------" << endl
         << "|Read Reg 1: " << regFile.getReadAddr1() << endl
         << "|Read Reg 2: " << regFile.getReadAddr2() << endl
         << "|Write Reg: " << regFile.getWriteAddr() << endl
         << "|Read Data 1: " << regFile.getReadData1() << endl
         << "|Read Data 2: " << regFile.getReadData2() << endl
         << "|Write Data: " << regFile.getWriteData() << endl
         << "-------------------------" << endl
         << "|Memory:                |" << endl
         << "-------------------------" << endl;
    for(int i = 0; i < memory_size; i++){
        if(dataMem.memory[i] != "Empty"){
            cout << "| " << i * 4 << "       " << dataMem.memory[i] << endl;
        }
    }
    cout << "-------------------------" << endl << endl;
    
    char input;
    cout << "Would you like to access the debug mode? (Y/N): ";
    cin >> input;
    
    if(input == 'Y' || input =='y'){
        for(int x = 0; x < PC; x++){
            cout << "******INSTRUCTION " << usedInstr[x] << " ******" << endl;
            cout << "-------------------------" << endl
                 << "|Register File:         |" << endl
                 << "-------------------------" << endl
                 << "|Read Reg 1: " << readAddr1[x] << endl
                 << "|Read Reg 2: " << readAddr2[x] << endl
                 << "|Write Reg: " << writeAddr[x] << endl
                 << "|Read Data 1: " << readData1[x] << endl
                 << "|Read Data 2: " << readData2[x] << endl
                 << "|Write Data: " << writeData[x] << endl
                 << "-------------------------" << endl
                 << "|State Regesters:       |" << endl
                 << "-------------------------" << endl
                 << "|PC: " << x * 4 << endl
                 << "-------------------------" << endl
                 << "|Control Signals:       |" << endl
                 << "-------------------------" << endl;
            cout << "|RegDst: " << RegDst[x] << endl
                 << "|RegWrite: " << RegWrite[x] << endl
                 << "|ALUSrc: " << ALUSrc[x] << endl
                 << "|PCSrc: " << PCSrc[x] << endl
                 << "|MemWrite: " << MemWrite[x] << endl
                 << "|MemRead: " << MemRead[x] << endl
                 << "|MemtoReg: " << MemtoReg[x] << endl
                 << "-------------------------" << endl << endl;
        }
             
    }
    else{
        return 0;
    }
}
