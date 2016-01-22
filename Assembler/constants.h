/*
 * This file defines constants for the assembly language. 
 *
 * Note about commented code: The preferred method for defining global constants is to use:
 *	"extern const xxx yyy = zzz;"
 * I instead used #define, at least for now, because gcc will give an erroneous warning for each of
 * the constants. Because I did not want anyone to be alarmed by the warnings, I commented them out.
 * In the future, we may decide against using #define, so I left the option there.
 *
 * author: Zachary Ankenman
 * version 0.1
 */

#ifndef _CONSTANTS_H
#define _CONSTANTS_H


/*
extern const char LDAD = 0b10000010, // Load Direct
		  LDAI = 0b10000001, // Load Immediate
		  STA  = 0b10100010, // Store
		  ADDD = 0b01000010, // Add Direct
		  ADDI = 0b01000001, // Add Immediate
		  ADCD = 0b01001010, // Add with Carry Direct
		  ADCI = 0b01001001, // Add with Carry Immediate
		  SUBD = 0b01010010, // Subtract Direct
		  SUBI = 0b01010001, // Subtract Immediate
		  SBCD = 0b01110010, // Subtract with Carry Direct
		  SBCI = 0b01110001, // Subtract with Carry Immediate
		  INC  = 0b01001100, // Increment
		  DEC  = 0b01000100, // Decrement
		  ANDD = 0b01011010, // And Direct
		  ANDI = 0b01011001, // And Immediate
		  ORD  = 0b01011110, // Or Direct
		  ORI  = 0b01011101, // Or Immediate
		  INV  = 0b01011000, // Invert
		  XORD = 0b01010110, // XOR Direct
		  XORI = 0b01010101, // XOR Immediate
		  CLRA = 0b01001111, // Clear Accumulator
		  CLRC = 0b01000000, // Clear Carry Bit
		  CSET = 0b01001000, // Set Carry Bit
		  CMPD = 0b01001010, // Compare Direct
		  CMPI = 0b01001001, // Compare Immediate
		  // Jump instructions are used differently than other instructions
		  J    = 0b11000000, // Unconditional Jump
		  JC   = 0b11100100, // Jump on carry
		  JNC  = 0b11100000, // Jump on not carry
		  JN   = 0b11010010, // Jump negative
		  JNN  = 0b11010000, // Jump on not negative
		  JZ   = 0b11001001, // Jump on zero
		  JNZ  = 0b11001000; // Jump on not zero

extern const int MEMSIZE = 256; // Size of instruction and data memory
*/


#define LDAD 0b10000010
#define LDAI 0b10000001
#define STA  0b10100010
#define ADDD 0b01000010
#define ADDI 0b01000001
#define ADCD 0b01001010
#define ADCI 0b01001001
#define SUBD 0b01010010
#define SUBI 0b01010001
#define SBCD 0b01110010
#define SBCI 0b01110001
#define INC  0b01001100
#define DEC  0b01000100
#define ANDD 0b01011010
#define ANDI 0b01011001
#define ORD  0b01011110
#define ORI  0b01011101
#define INV  0b01011000
#define XORD 0b01010110
#define XORI 0b01010101
#define CLRA 0b01001111
#define CLRC 0b01000000
#define CSET 0b01001000
#define CMPD 0b01001010
#define CMPI 0b01001001
#define J    0b11000000
#define JC   0b11100100
#define JNC  0b11100000
#define JN   0b11010010
#define JNN  0b11010000
#define JZ   0b11001001
#define JNZ  0b11001000

#define MEMSIZE 256


#endif
