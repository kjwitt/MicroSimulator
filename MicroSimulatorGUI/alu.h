/*
 * alu.h
 *
 *  Created on: Jan 27, 2016
 *  Author: logan Myers
 *
 *  Version     :1.0
 * 
 *      The ALU function replicates the ALU within the Microbaby
 *      architecture. Please see the comments above the function
 *      parameters for an explanation of said parameters.
 * 
 * addsuborlogic: 0 use adder unit to compute values
 * 		  1 use logic unit to compute values
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


#ifndef _ALU_H
#define _ALU_H

#include "statusflags.h"

//Function headers
char alu(Statusflags& object, int addsuborlogic, char ACC, char Databus, int addsub, int Csel, int logic);

#endif
