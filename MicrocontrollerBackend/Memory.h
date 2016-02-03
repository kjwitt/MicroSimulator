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

class Memory {
public:
	Memory();
	~Memory();
	char access(bool rw, char addrval, char dataval);

protected:
char memarray[255];
};

#endif /* MEMORY_H_ */
