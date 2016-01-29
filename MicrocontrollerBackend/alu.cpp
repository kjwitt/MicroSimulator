/*
 * alufunction.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Logan Myers, myers.1277
 *
 *      The ALU function replicates the ALU within the Microbaby
 *      architecture. Please see the comments above the function
 *      parameters for an explanation of said parameters.
 *
 *      Version     :1.0
 */
#ifndef ALUFUNCTION_CPP_
#define ALUFUNCTION_CPP_

using namespace std;

extern bool C=0, N=0, Z=0;

void zcheck(char checkvalue){
	if (checkvalue == 0){ //Check if need to set Z flag
			Z = 1;
		} else {
			Z = 0;
		}
}

void ncheck(char checkvalue){
	if (checkvalue < 0){ //Check if need to set N flag
			N = 1;
		} else {
			N = 0;
		}
}

void cset(bool checkvalue){
	switch(checkvalue){
	case 0:
		C = 0;
	case 1:
		C = 1;
	}
}

void ccheck(int addsub = 0, char val1 = 0b00000000, char val2 = 0b00000000, int Cin=0){
	int tempval1, tempval2, tempoutput;
	tempval1 = (int)val1;
	tempval2 = (int)val2;

	switch (addsub){
	case 0:
		tempoutput = tempval1 + tempval2 + Cin;
		break;
	case 1:
		tempoutput = tempval1 - tempval2 - Cin;
		break;
	}
	tempoutput=tempoutput & 0x0100;
	if (tempoutput != 0){
		cset(1);
	} else {
		cset(0);
	}
}

/* addsuborlogic: 0 use adder unit to compute values
 * 				  1 use logic unit to compute values
 * ACC          : Input ACC value
 * Databus      : Input Databus value
 * addsub       : 0 use for addition
 *                1 use for subtraction
 * Csel         : 0 use C
 * (for add or    1 use C' (C not)
 *  subtract)     2 use '0'
 *                3 use '1'
 * logic        : 0 use AND bitwise operation
 *                1 use OR bitwise operation
 *                2 use INV bitwise operation
 *                3 use XOR bitwise operation
 */
char alu(int addsuborlogic=0, char ACC = 0b00000000, char Databus = 0b00000000, int addsub = 0, int Csel = 0, int logic = 0){
	int output=0b00000000; // output will be the value that gets returned
	char Cin = 0;

	switch (addsuborlogic){
	case 0: // Using adder unit to compute values

		switch(Csel){ // Determining which C value to use in addition/subtraction
		case 0:
			Cin = C;  // Cin will be equal to global Carry flag variable
			break;
		case 1:
			Cin = ~C; // Cin will be equal to inversion of global Carry Flag variable
			break;
		case 2:
			Cin = 0; // Cin will be equal to 0
			break;
		case 3:
			Cin = 1; // Cin will be equal to 1
			break;
		}

		switch(addsub){ // Use addition or subtraction?
		case 0:

			output = ACC + Databus + Cin;
			ccheck(0, ACC, Databus, Cin);
			break;
		case 1:
			output = ACC - Databus - Cin;
			ccheck(1, ACC, Databus, Cin);
			break;
		}

		break;

	case 1: // Using logic unit to compute values
		switch(logic){
		case 0: // AND bitwise operation
			output = ACC & Databus;
			break;
		case 1: // OR bitwise operation
			output = ACC | Databus;
			break;
		case 2: // INV bitwise operation
			output = ~ACC;
			break;
		case 3: // XOR bitwise operation
			output = ACC ^ Databus;
			break;
		}
		break;
	}

	zcheck(output);
	ncheck(output);

	return output;
}

#endif /* ALUFUNCTION_CPP_ */




