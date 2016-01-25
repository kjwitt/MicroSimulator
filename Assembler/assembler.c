/*
 * This program is an assembler for MicroBaby. The two command line arguments are for an assembly 
 * program input, and binary output file.
 * This assembler does not check if the program is too long, it will just truncate it.
 * Usage example:
 * $ gcc assembler.c -o assem
 * $ ./assem input.asm output.bin
 *
 * author: Zachary Ankenman
 * version 0.3
 */

#include <stdio.h>
#include "constants.h"
#include "assembler.h"

// The main is mainly here for testing.
int main (int argc, char *argv[]) {
	// Check input arguments
	if (argc != 3) {
		printf("Incorrect number of arguments. Example:\n\n$ ./assem in.asm out.bin\n\n");
		printf("Exiting.\n");
		return(1);
	}

	// Open Input and Output files
        //FILE *input = fopen( argv[1], "r" );
        FILE *output = fopen( argv[2], "wb" );
       /* if ( input == 0 || output == 0 )
        {
		printf( "Could not open a file. Exiting.\ninput: %ld, output %ld\n", (long)&input, (long)&output);
		return(2);	
        }*/

	// Create memory array for instruction memory
	char instrMem[MEMSIZE];

	// Fill memory
	fillMem(instrMem, argv[1]);

	// Write binary file
	fwrite(instrMem, sizeof(char), sizeof(instrMem), output);

	// Close files
	fclose(output);
}

void fillMem (char * instrMem, char * inputFile) {
        FILE *input = fopen(inputFile, "r" );
	char instr[5], operand[10]; // Buffers for instruction and operand
	int counter = 0; // Count number of instructions
	while (fscanf(input, "%s", instr) == 1 && counter < MEMSIZE) {
		char temp[9];

		// Switch-like if-else block because C doesn't switch on strings
		// LDA
		if (strcmp(instr, "LDA") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = LDAI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = LDAD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// STA
		else if (strcmp(instr, "STA") == 0) {
			fscanf(input, "%s", operand);
			instrMem[counter++] = STA;
			instrMem[counter++] = atoi(operand);
		}
		// ADD
		else if (strcmp(instr, "ADD") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ADDI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = ADDD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// ADDC
		else if (strcmp(instr, "ADDC") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ADCI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = ADCD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// SUB
		else if (strcmp(instr, "SUB") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = SUBI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = SUBD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// SUBC
		else if (strcmp(instr, "SUBC") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = SBCI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = SBCD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// INC
		else if (strcmp(instr, "INC") == 0) {
			instrMem[counter++] = INC;
			instrMem[counter++] = 0;
		}
		// DEC
		else if (strcmp(instr, "DEC") == 0) {
			instrMem[counter++] = DEC;
			instrMem[counter++] = 0;
		}
		// AND
		else if (strcmp(instr, "AND") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ANDI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = ANDD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// OR
		else if (strcmp(instr, "OR") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ORI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = ORD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// INV
		else if (strcmp(instr, "INV") == 0) {
			instrMem[counter++] = INV;
			instrMem[counter++] = 0;
		}
		// XOR
		else if (strcmp(instr, "XOR") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = XORI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = XORD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// CLRA
		else if (strcmp(instr, "CLRA") == 0) {
			instrMem[counter++] = CLRA;
			instrMem[counter++] = 0;
		}
		// CLRC
		else if (strcmp(instr, "CLRC") == 0) {
			instrMem[counter++] = CLRC;
			instrMem[counter++] = 0;
		}
		// CSET
		else if (strcmp(instr, "CSET") == 0) {
			instrMem[counter++] = CSET;
			instrMem[counter++] = 0;
		}
		// CMP
		else if (strcmp(instr, "CMP") == 0) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = CMPI;
				instrMem[counter++] = atoi(operand + 1);
			} else {
				instrMem[counter++] = CMPD;
				instrMem[counter++] = atoi(operand);
			}
		}
		// Jump Block
		else if (instr[0] == 'J') {
			char jumpType = J;
			if (instr[1] == 'c') jumpType |= JNC;
			if (instr[1] == 'C') jumpType |= JC;
			if (instr[2] == 'n') jumpType |= JNN;
			if (instr[2] == 'N') jumpType |= JN;
			if (instr[3] == 'z') jumpType |= JNZ;
			if (instr[3] == 'Z') jumpType |= JZ;
			fscanf(input, "%s", operand);
			instrMem[counter++] = jumpType;
			instrMem[counter++] = atoi(operand);
		}
		// DEFAULT
		else {
			printf("Assembly error on line %d\n", counter / 2);
		}
	}

	// Pad remaining memory with zeros
	for (; counter < MEMSIZE; counter++) {
		instrMem[counter] = 0;
	}
	// Close file
	fclose(input);
}
