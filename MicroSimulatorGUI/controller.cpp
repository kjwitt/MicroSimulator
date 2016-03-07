/*
 * controller.h
 *
 *  Created on: Feb 1, 2016
 *  Author: Liz Koontz & Zachary Ankenman
 *
 *  Version     : 1.1
 *  Description	: This program is the control unit for MicroBaby
 * 
 *
 */

#include "constants.h"
#include "alu.h"
#include "jump.h"
#include "Memory.h"
#include "statusflags.h"
#include "controller.h"

char load();
void execute(char instruction, char data);

static char ACC = 0;
static Statusflags SR;
static int cycles = 0; 
static char instruction = 0;
static char data = 0;
static char programCounter;

static Memory * instrMemory;
static Memory * dataMemory;

void Controller::setProgramCounter(char _pc)
{
    programCounter = _pc;
}

Controller::Controller(char * instrMem, char * dataMem) {
	// Create instruction and data memory
	instrMemory = new Memory(instrMem);
	dataMemory = new Memory(dataMem);
	programCounter = 0;
}

int Controller::runOneCycle() {
	int result = -1; // Result will be 0 when program completes
	
	if (programCounter > 255) { //Error checking as not to exceed instruction memory
		return(-1);
	}
	
	if (cycles%3 == 0) {
		instruction = instrMemory->access(0, programCounter, 0);
		programCounter++;
	}
	
	if (cycles%3 == 1) {
		data = instrMemory->access(0, programCounter, 0);
		programCounter++;
	}

	if (cycles%3 == 2) {
		execute(instruction, data);
		result = 0;
	}

	cycles++;
	
	return result;
}

void execute(char instruction, char data) {	
	char dataBus = 0;
	switch ((unsigned char) instruction) {
		case LDAD: 
			ACC = dataMemory->access(0, data);
			break;

		case LDAI:
			ACC = data;
			break;

		case STA :
			dataMemory->access(1, data, ACC);
			break;

		case ADDD:
			dataBus = dataMemory->access(0, data);
			ACC = alu(SR, 0, ACC, dataBus, 0, 2, 0);
			break;

		case ADDI:
			ACC = alu(SR, 0, ACC, data, 0, 2, 0);
			break;

		case ADCD:
			dataBus = dataMemory->access(0, data);
			ACC = alu(SR, 0, ACC, dataBus, 0, 0, 0);
			break;

		case ADCI:
			ACC = alu(SR, 0, ACC, data, 0, 0, 0);
			break;

		case SUBD:
			dataBus = dataMemory->access(0, data);
			ACC = alu(SR, 0, ACC, dataBus, 1, 2, 0);
			break;

		case SUBI:
			ACC = alu(SR, 0, ACC, data, 1, 2, 0);
			break;

		case SBCD:
			dataBus = dataMemory->access(0, data);
			ACC = alu(SR, 0, ACC, dataBus, 1, 0, 0);
			break;

		case SBCI:
			ACC = alu(SR, 0, ACC, data, 1, 0, 0);
			break;

		case INC :
			ACC = alu(SR, 0, ACC, '1', 0, 2, 0);
			break;

		case DEC :
			ACC = alu(SR, 0, ACC, '1', 1, 2, 0);
			break;

		case ANDD:
			dataBus = dataMemory->access(0, data);
			ACC = alu(SR, 1, ACC, dataBus, 0, 0, 0);
			break;

		case ANDI:
			ACC = alu(SR, 1, ACC, data, 0, 0, 0);
			break;

		case ORD :
			dataBus = dataMemory->access(0, data);
			ACC = alu(SR, 1, ACC, dataBus, 0, 0, 1);
			break;

		case ORI :
			ACC = alu(SR, 1, ACC, data, 0, 0, 1);
			break;

		case INV :
			ACC = alu(SR, 1, ACC, data, 0, 0, 2);
			break;

		case XORD:
			dataBus = dataMemory->access(0, data);
			ACC = alu(SR, 1, ACC, dataBus, 0, 0, 3);
			break;

		case XORI:
			ACC = alu(SR, 1, ACC, data, 0, 0, 3);
			break;

		case CLRA:
			ACC = '0';
			break;

		case CLRC:
			SR.setc(0);
			break;

		case CSET:
			SR.setc(1);
			break;

		case CMPD: 
			dataBus = dataMemory->access(0, data);
			alu(SR, 0, ACC, dataBus, 1, 2, 0);
			break;

		case CMPI:
			alu(SR, 0, ACC, data, 1, 2, 0);
			break;

		default:
			char destinationQuestionMark; 
			//JUMP(&instruction, &destinationQuestionMark, SR, &programCounter);
			break;
		}
}


char Controller::getAccumulator() {
	return ACC;
}

Statusflags Controller::getSR() {
	return SR;
}

char Controller::getIstructionRegister() {
	return instruction;
}

char Controller::getDataRegister() {
	return data;
}

char Controller::getProgramCounter() {
	return programCounter;
}

char * Controller::getInstrMemory() {
	return instrMemory->getMemory();
}
char * Controller::getDataMemory() {
	return dataMemory->getMemory();
}
