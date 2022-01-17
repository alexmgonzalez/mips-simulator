*READ ME*

This is an instruction-by-instruction simulator for a MIPS Processor. It is faithful to the 5-stage MIPS Processor and includes the main structures of a MIPS processor.


With this simulator, you may input any assembly file and the simulator will provide the final state of the register file and values in data memory. It also gives you a debug option in which it will display the register file state after each instruction, the PC, and the Control Signals for each instruction. 


Build/Run Instructions:

To build this simulator, you will need access to a Linux command line. Use the cd command to get into the MIPS_SIMULATOR folder. Use the line below to compile the simulator.

	g++ main.cpp instruction_memory.cpp register_file.cpp alu.cpp data_memory.cpp 		control_unit.cpp -o simulator

And use this line to run the simulator:
	
	./simulator

Be sure to include the assembly file in the MIPS_SIMULATOR folder or the program will not find the file to read.

assembly.asm is included as a test of each instruction.