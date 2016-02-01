/*
 * Memory.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: logan
 */

#include "Memory.h"

Memory::Memory() {
	// TODO Auto-generated constructor stub
	instruction[255] = {};
	data[255] = {};
}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
}

//Functions
char Memory::memmod(char addrval, char dataval, bool rw, bool memset){
	char output = 0;

	if (memset==0){

		if (rw==0){
			output = instruction[addrval];
		} else if (rw==1) {
			instruction[addrval] = dataval;
		}
	} else if (memset==1){
		if (rw==0){
			output = data[addrval];
		} else if (rw==1) {
			data[addrval] = dataval;
		}
	}

	return output;
}

