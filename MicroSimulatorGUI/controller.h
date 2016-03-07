/*
 * controller.h
 *
 *  Created on: Feb 1, 2016
 *  Author: Zachary Ankenman
 *
 *  Version     : 0.1
 *  Description	: This program is the control unit for MicroBaby
 * 
 *
 */

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "alu.h"
#include "Memory.h"
#include "statusflags.h"

class Controller
{
public:
  Controller(); // DON'T USE THIS CONTSTRUCTOR
  Controller(char * instrMem, char * dataMem);
  ~Controller();
  int runOneCycle();
  char getAccumulator();
  Statusflags getSR();
  char getIstructionRegister();
  char getDataRegister();
  char getProgramCounter();
  char * getInstrMemory();
  char * getDataMemory();
  void setProgramCounter(char _pc);

protected:
  bool C, Z, N;

};

#endif
