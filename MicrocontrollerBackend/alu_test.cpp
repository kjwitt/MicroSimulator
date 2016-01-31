/*
* Name        : ALU.cpp
* Author      : Logan Myers
* Version     :1.0
*
* Description : This is a Test file for the ALU.
*
*
*/

#include <iostream>
#include <bitset>
#include "statusflags.h"
#include "Memory.h"
#include "alu.h"

using namespace std;

//Status Flags

//Registers
//char pc, ir, acc, databus, addrbus;

//Main Program
int main() {
	//Variables
	Statusflags sf;
	Memory mem;
	char num1, num2, output;
	char pc0 = 0;
	char pc1 = 1;

	mem.memmod(pc0, num1, 1, 1);
	mem.memmod(pc1, num2, 1, 1);

	num1 = -1;
	num2 = -1;

	cout << "num1 = " << std::bitset<8>(num1) << endl;
	cout << "num2 = " << std::bitset<8>(num2) << endl;

	output = alu(sf, 0, num1, num2, 0, 2, 0);

	cout << std::bitset<8>(output) << endl;
	cout << "C: " << sf.getc() << endl;
	cout << "N: " << sf.getn() << endl;
	cout << "z: " << sf.getz() << endl;

	sf.~Statusflags();
	mem.~Memory();
	return 0;
}
