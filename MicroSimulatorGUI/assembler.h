/*
 * This program is an assembler for MicroBaby. The two command line arguments are for an assembly 
 * program input, and binary output file.
 * This assembler does not check if the program is too long, it will just truncate it.
 * Usage example, if running from command line:
 * $ gcc assembler.c -o assem
 * $ ./assem input.asm output.bin
 *
 * author: Zachary Ankenman
 * version 0.4
 */

#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

/*
 * This function will fill instrMem with 8-bit values based on program text file
 * located in inputFile
 *
 * instrMem is a char array 256 elements long
 * inputFile is a string containing location of plaintext assembly program
 */
void assemble (char * instrMem, char * inputFile);

/*
 * This function will read up to 256 values from a text file and fill char array dataMem.
 * The values in the text file should be both
 * a) two's complement, 8-bit values. [-128, 127]
 * and 
 * b) separated by whitespace, e.g. 34 -13 6 -4 -127
 * 
 * If fewer than 256 values are in the file, the remaining values will be 0.
 *
 * dataMem is a char array 256 elements long
 * inputFile is a string containing the location of plaintext data memory.
 */
void fillDataMemory (char * dataMem, char * inputFile);

#endif
