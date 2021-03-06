/*
 * This program is an assembler for MicroBaby. The two command line arguments are for an assembly 
 * program input, and binary output file.
 * This assembler does not check if the program is too long, it will just truncate it.
 * Usage example:
 * $ gcc assembler.c -o assem
 * $ ./assem program_in.asm program_out.bin memory_out.bin
 *
 * author: Zachary Ankenman
 * version 0.4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hexconstants.h"
#include "assembler.h"

/*
// The main is mainly here for testing.
int main (int argc, char *argv[]) {
	// Check input arguments
	if (argc != 4) {
		printf("Incorrect number of arguments. Example:\n\n");
		printf("$ ./assem program_in.asm program_out.bin memory_out.bin\n\n");
		printf("Exiting.\n");
		return(1);
	}

	// Open Input and Output files
        //FILE *input = fopen( argv[1], "r" );
        FILE *output = fopen( argv[2], "wb" );
        FILE *memory_output = fopen( argv[3], "wb" );
//        if ( input == 0 || output == 0 )
//        {
//		printf( "Could not open a file. Exiting.\ninput: %ld, output %ld\n", (long)&input, (long)&output);
//		return(2);	
//        }

	// Create memory arrays for instruction and data memory
	char instrMem[MEMSIZE];
	char dataMem[MEMSIZE];

	// Fill memory
	assemble(instrMem, dataMem, argv[1]);
	//fillDataMemory(dataMem, argv[2]);

	// Write binary file
	fwrite(instrMem, sizeof(char), sizeof(instrMem), output);
	fwrite(dataMem, sizeof(char), sizeof(dataMem), memory_output);

	// Close files
	fclose(output);
}
*/


void assemble (char * instrMem, char * dataMem, char * inputFile) {
        FILE *input = fopen(inputFile, "r" );
	char instr[5], operand[10]; // Buffers for instruction and operand
	int counter = 0; // Count number of instructions
	while (fscanf(input, "%s", instr) == 1 && (strcmp(instr, ".data") != 0) && counter < MEMSIZE) {
		char temp[9];

		// Switch-like if-else block because C doesn't switch on strings
		// LDA
		if ((strcmp(instr, "LDA") == 0) || (strcmp(instr, "lda") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = LDAI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
                instrMem[counter++] = LDAD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);;
			}
		}
		// STA
		else if ((strcmp(instr, "STA") == 0) || (strcmp(instr, "sta") == 0)) {
			fscanf(input, "%s", operand);
			instrMem[counter++] = STA;
			instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
		}
		// ADD
		else if ((strcmp(instr, "ADD") == 0) || (strcmp(instr, "add") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ADDI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = ADDD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// ADDC
		else if ((strcmp(instr, "ADDC") == 0) || (strcmp(instr, "addc") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ADCI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = ADCD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// SUB
		else if ((strcmp(instr, "SUB") == 0) || (strcmp(instr, "sub") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = SUBI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = SUBD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// SUBC
		else if ((strcmp(instr, "SUBC") == 0) || (strcmp(instr, "subc") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = SBCI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = SBCD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// INC
		else if ((strcmp(instr, "INC") == 0) || (strcmp(instr, "inc") == 0)) {
			instrMem[counter++] = INC;
			instrMem[counter++] = 0;
		}
		// DEC
		else if ((strcmp(instr, "DEC") == 0) || (strcmp(instr, "dec") == 0)) {
			instrMem[counter++] = DEC;
			instrMem[counter++] = 0;
		}
		// AND
		else if ((strcmp(instr, "AND") == 0) || (strcmp(instr, "and") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ANDI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = ANDD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// OR
		else if ((strcmp(instr, "OR") == 0) || (strcmp(instr, "or") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = ORI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = ORD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// INV
		else if ((strcmp(instr, "INV") == 0) || (strcmp(instr, "inv") == 0)) {
			instrMem[counter++] = INV;
			instrMem[counter++] = 0;
		}
		// XOR
		else if ((strcmp(instr, "XOR") == 0) || (strcmp(instr, "xor") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = XORI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = XORD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// CLRA
		else if ((strcmp(instr, "CLRA") == 0) || (strcmp(instr, "clra") == 0)) {
			instrMem[counter++] = CLRA;
			instrMem[counter++] = 0;
		}
		// CLRC
		else if ((strcmp(instr, "CLRC") == 0) || (strcmp(instr, "clrc") == 0)) {
			instrMem[counter++] = CLRC;
			instrMem[counter++] = 0;
		}
		// CSET
		else if ((strcmp(instr, "CSET") == 0) || (strcmp(instr, "cset") == 0)) {
			instrMem[counter++] = CSET;
			instrMem[counter++] = 0;
		}
		// CMP
		else if ((strcmp(instr, "CMP") == 0) || (strcmp(instr, "cmp") == 0)) {
			fscanf(input, "%s", operand);
			if (operand[0] == '#') {
				instrMem[counter++] = CMPI;
				instrMem[counter++] = (unsigned char) strtol(operand + 1, NULL, 0);
			} else {
				instrMem[counter++] = CMPD;
				instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
			}
		}
		// Jump Block
		else if (instr[0] == 'J' || instr[0] == 'j') {
			char jumpType = J;
			if (instr[1] == 'c') jumpType |= JNC;
			if (instr[1] == 'C') jumpType |= JC;
			if (instr[2] == 'n') jumpType |= JNN;
			if (instr[2] == 'N') jumpType |= JN;
			if (instr[3] == 'z') jumpType |= JNZ;
			if (instr[3] == 'Z') jumpType |= JZ;
			fscanf(input, "%s", operand);
			instrMem[counter++] = jumpType;
			instrMem[counter++] = (unsigned char) strtol(operand, NULL, 0);
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

	// Fill data memory with zeros
	for (counter = 0; counter < MEMSIZE; counter++) {
        dataMem[counter] = 0;
	}

	int address;
	char * ptr;
	while (fscanf(input, "%s", operand) == 1) {
		address = (unsigned char) strtol(operand, &ptr, 0);
		fscanf(input, "%s", operand);
        dataMem[address] = (char) strtol(operand, &ptr, 0);
	}

	// Close file
	fclose(input);
}


void fillDataMemory (char * dataMem, char * inputFile) {
        FILE *input = fopen(inputFile, "r" );
	int tempOp;
	int counter = 0; // Count number of operands
	while (fscanf(input, "%d", &tempOp) == 1 && counter < MEMSIZE) {
		dataMem[counter] = (char) tempOp;
		counter++;
	}

	// Pad remaining memory with zeros
	for (; counter < MEMSIZE; counter++) {
		dataMem[counter] = 0;
	}
}
