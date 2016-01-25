/*
 * This file defines constants for the assembly language. 
 *
 * author: Zachary Ankenman
 * version 0.2
 */

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define LDAD (unsigned char) 0b10000010 // Load Direct
#define LDAI (unsigned char) 0b10000001 // Load Immediate
#define STA  (unsigned char) 0b10100010 // Store
#define ADDD (unsigned char) 0b01000010 // Add Direct
#define ADDI (unsigned char) 0b01000001 // Add Immediate
#define ADCD (unsigned char) 0b01000110 // Add with Carry Direct
#define ADCI (unsigned char) 0b01000101 // Add with Carry Immediate
#define SUBD (unsigned char) 0b01010010 // Subtract Direct
#define SUBI (unsigned char) 0b01010001 // Subtract Immediate
#define SBCD (unsigned char) 0b01110010 // Subtract with Carry Direct
#define SBCI (unsigned char) 0b01110001 // Subtract with Carry Immediate
#define INC  (unsigned char) 0b01001100 // Increment
#define DEC  (unsigned char) 0b01000100 // Decrement
#define ANDD (unsigned char) 0b01011010 // And Direct
#define ANDI (unsigned char) 0b01011001 // And Immediate
#define ORD  (unsigned char) 0b01011110 // Or Direct
#define ORI  (unsigned char) 0b01011101 // Or Immediate
#define INV  (unsigned char) 0b01011000 // Invert
#define XORD (unsigned char) 0b01010110 // XOR Direct
#define XORI (unsigned char) 0b01010101 // XOR Immediate
#define CLRA (unsigned char) 0b01001111 // Clear Accumulator
#define CLRC (unsigned char) 0b01000000 // Clear Carry Bit
#define CSET (unsigned char) 0b01001000 // Set Carry Bit
#define CMPD (unsigned char) 0b01001010 // Compare Direct
#define CMPI (unsigned char) 0b01001001 // Compare Immediate
// Jump instructions are used differently than other instructions
#define J    (unsigned char) 0b11000000 // Unconditional Jump
#define JC   (unsigned char) 0b11100100 // Jump on carry
#define JNC  (unsigned char) 0b11100000 // Jump on not carry
#define JN   (unsigned char) 0b11010010 // Jump negative
#define JNN  (unsigned char) 0b11010000 // Jump on not negative
#define JZ   (unsigned char) 0b11001001 // Jump on zero
#define JNZ  (unsigned char) 0b11001000 // Jump on not zero

#define MEMSIZE 256 // Size of instruction and data memory


#endif
