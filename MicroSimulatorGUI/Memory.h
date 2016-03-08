/*
 * Memory.h
 *
 *  Created on: Jan 29, 2016
 *      Author: Logan Myers
 *
 *      Version: 0.1
 *
 *      Explanation:
 *
 *      This class creates a 256 element array object to act as memory for microbaby simulator
 *
 *      access(bool rw, char addrval, char dataval = 0b000000)
 *
 *      rw		:	0	read addrval
 *      			1	write to addrval
 *      addrval	:	Specifies the memory block to read from/write to
 *      dataval	:	Specifies what to write to memory
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <cstdlib>

class Memory {
public:
	Memory();
	Memory(char * data);
	~Memory();
    char memarray[256];
    char access(bool rw, unsigned char addrval, char dataval = 0x00);
	char * getMemory();

protected:
};

#endif /* MEMORY_H_ */
