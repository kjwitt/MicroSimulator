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

int numCycle;
int currentCycle;


Controller::Controller(char * instrMem, char * dataMem, char _pc, char _ir, char _ac ,char _data, char _addr, Statusflags _sr){
    // Create instruction and data memory
    instrMemory = new Memory(instrMem);
    dataMemory = new Memory(dataMem);

    programCounter = _pc;
    instruction = _ir;
    ACC = _ac;
    data = _data;
    addr = _addr;
    SR = _sr;
}

Controller::~Controller()
{
    delete instrMemory;
    delete dataMemory;
}

int Controller::runOneCycle() {
    int result = -1; // Result will be 0 when program completes

    if (programCounter > 255) { //Error checking as not to exceed instruction memory
        return(-1);
    }
    if(programCounter==0 || programCounter%2==0)
    {
        instruction = instrMemory->access(0, programCounter, 0);
        switch ((unsigned char) instruction) {
        //3 cycle
        case LDAD:
        case ADDD:
        case ADCD:
        case SUBD:
        case SBCD:
        case ANDD:
        case ORD :
        case XORD:
        case CMPD:
        case STA :
            numCycle=3;
            break;
            //2 cycle
        case LDAI:
        case ADDI:
        case ADCI:
        case SUBI:
        case SBCI:
        case INC :
        case DEC :
        case ANDI:
        case ORI :
        case INV :
        case XORI:
        case CLRA:
        case CLRC:
        case CSET:
        case CMPI:
            numCycle=2;
            break;
        default:
            //char destinationQuestionMark;
            //JUMP(&instruction, &destinationQuestionMark, SR, &programCounter);
            numCycle=3;
            break;
        }
        currentCycle = 1;
        programCounter++;
        result = -1;
    }
    else
    {
        if(currentCycle==1)
        {
            if(numCycle==2)
            {
                //inherent/immediate 2nd (last) cycle
                //activate the data bus & execute
                data = instrMemory->access(0, programCounter, 0);
                programCounter++;
                execute(instruction, data);
                result = 0;
                currentCycle=0;
            }
            else
            {
                //direct 2nd cycle
                //activate address bus
                addr = instrMemory->access(0, programCounter, 0);
                result = -1;
                currentCycle=2;
            }
        }
        else
        {
            //direct 3rd (last) cycle
            //activate data bus & execute
            programCounter++;
            data = dataMemory->access(0, addr, 0);
            execute(instruction, data);
            result = 0;
            currentCycle=0;
        }
    }
    return result;
}

void Controller::execute(char instruction, char arg) {
    switch ((unsigned char) instruction) {
    case LDAD:
    case LDAI:
        ACC = arg;
        break;

    case STA :
        dataMemory->access(1, addr, ACC);
        data = addr;
        break;

    case ADDD:
    case ADDI:
        ACC = alu(SR, 0, ACC, arg, 0, 2, 0);
        break;

    case ADCD:
    case ADCI:
        ACC = alu(SR, 0, ACC, arg, 0, 0, 0);
        break;

    case SUBD:
    case SUBI:
        ACC = alu(SR, 0, ACC, arg, 1, 2, 0);
        break;

    case SBCD:
    case SBCI:
        ACC = alu(SR, 0, ACC, arg, 1, 0, 0);
        break;

    case INC :
        ACC = alu(SR, 0, ACC, 1, 0, 2, 0);
        break;

    case DEC :
        ACC = alu(SR, 0, ACC, 1, 1, 2, 0);
        break;

    case ANDD:
    case ANDI:
        ACC = alu(SR, 1, ACC, arg, 0, 0, 0);
        break;

    case ORD :
    case ORI :
        ACC = alu(SR, 1, ACC, arg, 0, 0, 1);
        break;

    case INV :
        ACC = alu(SR, 1, ACC, arg, 0, 0, 2);
        break;

    case XORD:
    case XORI:
        ACC = alu(SR, 1, ACC, arg, 0, 0, 3);
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
    case CMPI:
        alu(SR, 0, ACC, arg, 1, 2, 0);
        break;

    default:
        JUMP(instruction, addr, SR, &programCounter);
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

char Controller::getAddrRegister() {
    return addr;
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
