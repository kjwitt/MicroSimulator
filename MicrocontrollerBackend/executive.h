/*
 *
 * This file defines the executive function which will be the interface between the GUI
 * and the back-end software. As of right now, the functions are only loosely defined and
 * will need to be specified further as the GUI and back-end reach completion.
 *
 * author: Zachary Ankenman
 * version 0.1
 */

#ifndef _EXECUTIVE_H
#define _EXECUTIVE_H

#include <stdbool.h>
#include "controller.h"

/*
 * 
 */
void bootstrap(char * instrMem, char * dataMem);

/*
 * Runs program for one cycle
 */
void runCycle();

/*
 * Run program for up to 3 cycles to either run one whole instruction or
 * to finish the instruction in progress.
 */
void runInstruction();

/*
 * Runs program for specified number of cycles
 *
 * x: number of cycles to run.
 */
void runXCycles(int x);

/*
 * Runs program until reset
 */
void freeRun();

Controller * getController();
#endif
