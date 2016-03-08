#include "executive.h"
#include "controller.h"
#include <cstdlib>

Controller * ctrl;

void bootstrap(Controller *_ctrl) {
    ctrl = _ctrl;
}

char runCycle() {
	ctrl->runOneCycle();
    return ctrl->getProgramCounter();
}

//void runInstruction() {
//    int numCycle;
//    switch ((unsigned char) ctrl->getIstructionRegister()) {
//    //3 cycle
//    case LDAD:
//    case ADDD:
//    case ADCD:
//    case SUBD:
//    case SBCD:
//    case ANDD:
//    case ORD :
//    case XORD:
//    case CMPD:
//    case STA :
//        numCycle=3;
//        break;
//        //2 cycle
//    case LDAI:
//    case ADDI:
//    case ADCI:
//    case SUBI:
//    case SBCI:
//    case INC :
//    case DEC :
//    case ANDI:
//    case ORI :
//    case INV :
//    case XORI:
//    case CLRA:
//    case CLRC:
//    case CSET:
//    case CMPI:
//        numCycle=2;
//        break;
//    default:
//        //char destinationQuestionMark;
//        //JUMP(&instruction, &destinationQuestionMark, SR, &programCounter);
//        numCycle=3;
//        break;
//    }
//    for(int i =0;i<numCycle;i++)
//    {
//        runCycle();
//    }
//}

void runXCycles(int x) {
	int i;
	for (i = 0; i < x; i++) {
		runCycle();
	}
}

void freeRun() {
    //this doesn't work - if the PC never hits 255, this goes on forever.
    while (ctrl->getProgramCounter() < 255) {
		runCycle();
	}
}

