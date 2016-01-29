/*
 * alu.h
 *
 *  Created on: Jan 27, 2016
 *  Author: logan Myers
 *
 *  Version     :1.0
 */


#ifndef _ALU_H
#define _ALU_H

//Function headers
char alu(int addsuborlogic, char ACC, char Databus, int addsub, int Csel, int logic);
//functions to modify registers
void zcheck(char checkvalue);
void ncheck(char checkvalue);
void ccheck(int addsub, char val1, char val2, int Cin);
void cset(bool checkvalue);

#endif
