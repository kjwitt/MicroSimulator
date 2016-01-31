/*
 * memmod.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: Logan Myers
 *
 *      This is the function that will change a
 *      char array used as instruction memory and
 *      data memory of the Microbaby
 *
 *      char memmod(char addrval, char dataval, bool rw, char* memarry)
 *
 *      addrval	:char value of address to be accessed
 *      dataval	:char value of data to put in address (used when rw=0, don't care otherwise)
 *      rw		: 0 = read
 *      		: 1 = write
 *      memarry	: pointer to char array of memory to be changed
 *
 *      Example(s)reading: IR = memmod(addr,0,0, &datamemoryarray);
 *      		  writing: memmod(addr,data,1, &datamemoryarray);
 */
#ifndef _MEMMOD_CPP
#define _MEMMOD_CPP

//Functions
char memmod(char addrval, char dataval, bool rw, char *memarray){
	char output = 0;

	memarray = memarray + addrval;

	if (rw==0){
		output = *memarray;
	} else if (rw==1) {
		*memarray
		= dataval;
	}

	return output;
}

#endif
