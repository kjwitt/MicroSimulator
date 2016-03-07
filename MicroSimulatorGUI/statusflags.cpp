/*
 * statusflags.cpp
 *
 *  Created on: Jan 27, 2016
 *  Author: logan Myers
 *
 *  Version     :1.0
 *  Description	:This file contains the functions to C, N, Z status flags
 * 
 *
 */

#ifndef _STATUSFLAGS_CPP
#define _STATUSFLAGS_CPP

#include "statusflags.h"

Statusflags::Statusflags()
{
	C = 0;
	Z = 0;
	N = 0;
}

Statusflags::~Statusflags()
{
  //Destructors do not accept arguments
}

bool Statusflags::getz(){
	return Z;
}
bool Statusflags::getn(){
	return N;
}
bool Statusflags::getc(){
	return C;
}

void Statusflags::checkz(char checkvalue){
	if (checkvalue == 0){ //Check if need to set Z flag
			Z = 1;
		} else {
			Z = 0;
		}
}

void Statusflags::checkn(char checkvalue){
	if (checkvalue < 0){ //Check if need to set N flag
			N = 1;
		} else {
			N = 0;
		}
}

void Statusflags::setc(bool checkvalue){
	switch(checkvalue){
	case 0:
		C = 0;
		break;
	case 1:
		C = 1;
		break;
	}
}

void Statusflags::setn(bool checkvalue){
    switch(checkvalue){
    case 0:
        N = 0;
        break;
    case 1:
        N = 1;
        break;
    }
}

void Statusflags::setz(bool checkvalue){
    switch(checkvalue){
    case 0:
        Z = 0;
        break;
    case 1:
        Z = 1;
        break;
    }
}

void Statusflags::checkc(int addsub = 0, char val1 = 0x00, char val2 = 0x00, int Cin=0){
	int tempval1, tempval2, tempoutput;
	tempval1 = (int)val1;
	tempval2 = (int)val2;

	switch (addsub){
	case 0:
		tempoutput = tempval1 + tempval2 + Cin;
		break;
	case 1:
		tempoutput = tempval1 - tempval2 - Cin;
		break;
	}
	tempoutput=tempoutput & 0x0100;
	if (tempoutput != 0){
		setc(1);
	} else {
		setc(0);
	}
}

#endif
