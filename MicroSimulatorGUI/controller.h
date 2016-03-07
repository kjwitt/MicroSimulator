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
   char ACC;
   Statusflags SR;
   int cycles;
   char instruction;
   char data;
   char programCounter;
   char addr;

   Memory * instrMemory;
   Memory * dataMemory;

  void execute(char instruction, char data);

  Controller(); // DON'T USE THIS CONTSTRUCTOR
  Controller(char * instrMem, char * dataMem, char _pc, char _ir, char _ac ,char _data, char _addr);
  ~Controller();
  int runOneCycle();
  char getAccumulator();
  Statusflags getSR();
  char getIstructionRegister();
  char getDataRegister();
  char getAddrRegister();
  char getProgramCounter();
  char * getInstrMemory();
  char * getDataMemory();

protected:
  bool C, Z, N;

};

#endif
