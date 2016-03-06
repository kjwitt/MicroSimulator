#include "executive.h"
#include "controller.h"
#include <cstdlib>

static Controller * ctrl;
static int cycles; // number of cycles that have been run

void bootstrap(char * instrMem, char * dataMem) {
	ctrl = (Controller *) malloc(sizeof(Controller));
	ctrl = new Controller(instrMem, dataMem);
	cycles = 0;
}

void runCycle() {
	cycles++;
	ctrl->runOneCycle();
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
	while (ctrl->getProgramCounter() > 255) {
		runCycle();
	}
}

Controller * getController() {
	return ctrl;
}
