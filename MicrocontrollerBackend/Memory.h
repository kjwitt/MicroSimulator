/*
 * Memory.h
 *
 *  Created on: Jan 29, 2016
 *      Author: logan
 */

#ifndef MEMORY_H_
#define MEMORY_H_

class Memory {
public:
	Memory();
	~Memory();
	char memmod(char addrval, char dataval, bool rw, bool memset);
	void writeinstructionmemory(char addrval, char dataval);
	void writedatamemory(char addrval, char dataval);
	char readinstructionmemory(char addrval);
	char writedatamemory(char addrval);

protected:
char instruction[255], data[255];
};

#endif /* MEMORY_H_ */
