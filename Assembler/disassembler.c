/*
 * This program is an assembler for MicroBaby. The two command line arguments are for a binary input file
 * an assembly program output.
 * Usage example:
 * $ gcc disassembler.c -o disassem
 * $ ./disassem input.bin output.asm
 *
 * author: Zachary Ankenman
 * version 0.1
 */

#include <stdio.h>
#include "constants.h"

#define MAX_STRING_SIZE 10

int main (int argc, char *argv[]) {
	// Check input arguments
	if (argc != 3) {
		printf("Incorrect number of arguments. Example:\n\n$ ./disassem input.bin output.asm\n\n");
		printf("Exiting.\n");
		return(1);
	}

	// Open Input and Output files
        FILE *input = fopen( argv[1], "rb" );
        FILE *output = fopen( argv[2], "w" );
        if ( input == 0 || output == 0 )
        {
		printf( "Could not open a file. Exiting.\ninput: %ld, output %ld\n", (long)&input, (long)&output);
		return(2);	
        }

	// Create memory array for instruction memory
	char instrMem[MEMSIZE];

	// Create array of strings for assembly code output
	char outputCode[MEMSIZE][MAX_STRING_SIZE];

	// Read binary file
	fread(instrMem, sizeof(char), sizeof(instrMem), input);

	int counter = 0;
	char c;
	while (counter < MEMSIZE) {
		switch ((unsigned char) instrMem[counter]) {
			case LDAD: 
				fprintf(output, "LDA %u\n", instrMem[++counter]);
				break;

			case LDAI:
				fprintf(output, "LDA #%i\n", instrMem[++counter]);
				break;

			case STA :
				fprintf(output, "STA %u\n", instrMem[++counter]);
				break;

			case ADDD:
				fprintf(output, "ADD %u\n", instrMem[++counter]);
				break;

			case ADDI:
				fprintf(output, "ADD #%i\n", instrMem[++counter]);
				break;

			case ADCD:
				fprintf(output, "ADDC %u\n", instrMem[++counter]);
				break;

			case ADCI:
				fprintf(output, "ADDC #%i\n", instrMem[++counter]);
				break;

			case SUBD:
				fprintf(output, "SUB %u\n", instrMem[++counter]);
				break;

			case SUBI:
				fprintf(output, "SUB #%i\n", instrMem[++counter]);
				break;

			case SBCD:
				fprintf(output, "SUBC %u\n", instrMem[++counter]);
				break;

			case SBCI:
				fprintf(output, "SUBC #%i\n", instrMem[++counter]);
				break;

			case INC :
				fprintf(output, "INC\n");
				++counter;
				break;

			case DEC :
				fprintf(output, "DEC\n");
				++counter;
				break;

			case ANDD:
				fprintf(output, "AND %u\n", instrMem[++counter]);
				break;

			case ANDI:
				fprintf(output, "AND #%i\n", instrMem[++counter]);
				break;

			case ORD :
				fprintf(output, "OR %u\n", instrMem[++counter]);
				break;

			case ORI :
				fprintf(output, "OR #%i\n", instrMem[++counter]);
				break;

			case INV :
				fprintf(output, "INV\n");
				++counter;
				break;

			case XORD:
				fprintf(output, "XOR %u\n", instrMem[++counter]);
				break;

			case XORI:
				fprintf(output, "XOR #%i\n", instrMem[++counter]);
				break;

			case CLRA:
				fprintf(output, "CLRA\n");
				++counter;
				break;

			case CLRC:
				fprintf(output, "CLRC\n");
				++counter;
				break;

			case CSET:
				fprintf(output, "CSET\n");
				++counter;
				break;

			case CMPD:
				fprintf(output, "CMP %u\n", instrMem[++counter]);
				break;

			case CMPI:
				fprintf(output, "CMP #%i\n", instrMem[++counter]);
				break;

			default:
				if ((instrMem[counter] & J) == J) {
					char jump[5];
					jump[0] = 'J';
					jump[1] = '-';
					jump[2] = '-';
					jump[3] = '-';
					jump[4] = '\0';
					if ((instrMem[counter] & JNC) == JNC) jump[1] = 'c';
					if ((instrMem[counter] & JC) == JC) jump[1] = 'C';
					if ((instrMem[counter] & JNN) == JNN) jump[2] = 'n';
					if ((instrMem[counter] & JN) == JN) jump[2] = 'N';
					if ((instrMem[counter] & JNZ) == JNZ) jump[3] = 'z';
					if ((instrMem[counter] & JZ) == JZ) jump[3] = 'Z';
					fprintf(output, "%s ", jump);
					fprintf(output, "%d\n", instrMem[++counter]);
				}

				break;
		}
		counter++;
	}

	// Close files
	fclose(input);
	fclose(output);

}
