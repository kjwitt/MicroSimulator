//============================================================================
// Name        : ALU.cpp
// Author      : Logan Myers
// Version     :1.0
//
// Description : This is a Test file for the ALU.

// V1.0 1/28/15 :when ALu_Test is compined with alu.cpp in the same file and run
//				everything runs fine; however, when split into different functions
//				alu.cpp is having difficulty with the global variables C, Z, N. Need
//				to fix.
//
//============================================================================

#include <iostream>
#include <bitset>
#include "alu.h"

using namespace std;

//Status Flags
bool C=0, N=0, Z=0;
//Registers
char pc, ir, acc, databus, addrbus;

//Main Program
int main() {
	//Variables
	char num1, num2, output;

	num1 = 1;
	num2 = 1;

	cout << "num1 = " << std::bitset<8>(num1) << endl;
	cout << "num2 = " << std::bitset<8>(num2) << endl;

	output = alu(0, num1, num2, 0, 2, 0);

	cout << std::bitset<8>(output) << endl;
	cout << "C: " << C << endl;
	cout << "N: " << N << endl;
	cout << "z: " << Z << endl;
	return 0;
}
