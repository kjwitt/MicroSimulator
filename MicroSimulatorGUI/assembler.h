/*
 * This program is an assembler for MicroBaby. The two command line arguments are for an assembly 
 * program input, and binary output file.
 * This assembler does not check if the program is too long, it will just truncate it.
 * Usage example, if running from command line:
 * $ gcc assembler.c -o assem
 * $ ./assem input.asm output.bin
 *
 * author: Zachary Ankenman
 * version 0.3
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
void fillMem (char * instrMem, char * inputFile);

#endif
