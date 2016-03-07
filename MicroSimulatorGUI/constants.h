/*
 * This file defines constants for the assembly language. 
 *
 * author: Zachary Ankenman
 * version 0.3
 */

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define LDAD  	0x82 // Load Direct
#define LDAI  	0x81 // Load Immediate
#define STA   	0xA2 // Store
#define ADDD  	0x42 // Add Direct
#define ADDI  	0x41 // Add Immediate
#define ADCD  	0x46 // Add with Carry Direct
#define ADCI  	0x45 // Add with Carry Immediate
#define SUBD  	0x52 // Subtract Direct
#define SUBI  	0x51 // Subtract Immediate
#define SBCD  	0x7A // Subtract with Carry Direct
#define SBCI  	0x79 // Subtract with Carry Immediate
#define INC   	0x4C // Increment
#define DEC   	0x44 // Decrement
#define ANDD  	0x5A // And Direct
#define ANDI  	0x59 // And Immediate
#define ORD   	0x5E // Or Direct
#define ORI   	0x5D // Or Immediate
#define INV   	0x58 // Invert
#define XORD  	0x56 // XOR Direct
#define XORI  	0x55 // XOR Immediate
#define CLRA  	0x4F // Clear Accumulator
#define CLRC  	0x40 // Clear Carry Bit
#define CSET  	0x48 // Set Carry Bit
#define CMPD  	0x4A // Compare Direct
#define CMPI  	0x49 // Compare Immediate
// Jump instructions are used differently than other instructions
#define J 	0xC0 // Unconditional Jump
#define JC	0xE4 // Jump on carry
#define JNC   	0xE0 // Jump on not carry
#define JN    	0xD2 // Jump negative
#define JNN   	0xD0 // Jump on not negative
#define JZ    	0xC9 // Jump on zero
#define JNZ   	0xC8 // Jump on not zero

#define MEMSIZE 256 // Size of instruction and data memory



#endif
