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
//	int i;
//	for (i = 0; i < (cycles % 3); i++) {
//		runCycle();
//	}
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

