#include "executive.h"
#include "controller.h"
#include <cstdlib>

static Controller * ctrl;
static int cycles; // number of cycles that have been run

void bootstrap(char * instrMem, char * dataMem, char pc) {
    //ctrl = (Controller *) malloc(sizeof(Controller));
	ctrl = new Controller(instrMem, dataMem);
    ctrl->setProgramCounter(pc);
	cycles = 0;
}

char runCycle() {
	cycles++;
	ctrl->runOneCycle();
    return ctrl->getProgramCounter();
}

void runInstruction() {
	int i;
	for (i = 0; i < (cycles % 3); i++) {
		runCycle();
	}
}

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

Controller * getController() {
	return ctrl;
}
