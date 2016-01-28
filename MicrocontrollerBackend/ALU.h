/*  Assuming the C, Z, and N flags are all global variables
 *  In this file is:
 *        function for ALU
 *        function for checking Z flag
 *        function for checking N flag
 *        * I am putting together a function to check for C overflow/underflow but it still needs to be created
 *
 *addsuborlogic: 0 use adder unit to compute values
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
 *
 * Example: ALU(0, num1, num2, 0, 2, 0);
 */

char ALU(int addsuborlogic=0, char ACC = 0b00000000, char Databus = 0b00000000, int addsub = 0, int Csel = 0, int logic = 0){
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
			//* Here we will check if addition forced overflow and put that in C
			break;
		case 1:
			output = ACC - Databus - Cin;
			// * Here we will check if subtraction forced overflow and put that in C
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

	zflagcheck(output);
	nflagcheck(output);

	return output;
}

void zflagcheck(char checkvalue){ //Check if need to set Z flag
	if (checkvalue == 0){ 
			Z = 1;
		} else {
			Z = 0;
		}
}

void nflagcheck(char checkvalue){ //Check if need to set N flag
	if (checkvalue < 0){ 
			N = 1;
		} else {
			N = 0;
		}
}
