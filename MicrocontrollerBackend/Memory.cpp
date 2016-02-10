/*
 * Memory.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: Logan Myers
 *
 *		Version: 0.1
 *
 *		Explanation:
 *      access(bool rw, char addrval, char dataval = 0b000000)
 *
 *      rw		:	0	read addrval
 *      			1	write to addrval
 *      addrval	:	Specifies the memory block to read from/write to
 *      dataval	:	Specifies what to write to memory ( may omit if rw = 0 )
 */

#include "Memory.h"

Memory::Memory() {
	// TODO Auto-generated constructor stub
	memarray[255] = {};		//Make sure to clear data in the array during initialization
}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
}

//Functions
char Memory::access(bool rw, char addrval, char dataval){
	int tempaddrval;
	tempaddrval = (int)addrval;
	char output = 0;

	if (rw==0){
		output = memarray[tempaddrval];
	} else if (rw==1) {
		memarray[tempaddrval] = dataval;
	}



	return output;
}

