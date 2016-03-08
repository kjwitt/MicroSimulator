/*
 * jumpfunction.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: Stephen Scheramic scheramic.1
 *
 *      This JUMP fuction simulates what happens when the instruction code is 11cnzuuu
 *      which corisponds a jump. this function does not return any value and internally
 *      the only thing that may change is PC vlaue which is passed as a pointer. All
 *      other function inputs are used as refrences
 *
 *      Version     :1.0
 */
#ifndef JUMPFUNCTION_CPP_
#define JUMPFUNCTION_CPP_

using namespace std;
#include "statusflags.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
/* inst         : is the jump code in binary char i.e '11cnzuuu'
 * dest         : is the next value for PC if the jump is true
 * C,N, and Z   : boolean values for the current C N Z flags
 * PC           : the current value of PC
 */
void JUMP(char inst, unsigned char dest, Statusflags& object, char* PC)  {
   //setup boolean values for CNZ from the globals
    bool C = object.getc();
    bool N = object.getn();
    bool Z = object.getz();


    // switch case for all jump types
   switch ((unsigned char) inst) {

    case J: // unconditional jump
        *PC = dest;
        break;
//Single conditions
    case JC: // jump on c=1
        if (C == 1) {
            *PC = dest;}
        break;
    case JNC: //jump on c=0
       if (C == 0) {
           *PC = dest;}
       break;

   case JN: // jump on n=1
       if (N == 1) {
           *PC = dest;}
       break;
   case JNN: //jump on n=0
      if (N == 0) {
          *PC = dest;}
      break;

   case JZ: // jump on z=1
       if (Z == 1) {
           *PC = dest;}
       break;
   case JNZ: //jump on z=0
      if (Z == 0) {
          *PC = dest;}
      break;
//Double Conditions

    case (JN | JZ): //jump on N = 1 or Z = 1
       if (N == 1 || Z==1) {
           *PC = dest;}
       break;
    case (JN | JNZ): //jump on N = 1 or Z = 0
      if (N == 1 || Z==0) {
          *PC = dest;}
      break;
   case (JNN | JZ): //jump on N = 0 or Z = 1
      if (N == 0 || Z==1) {
          *PC = dest;}
      break;
   case (JNN | JNZ): //jump on N = 0 or Z = 0
     if (N == 0 || Z==0) {
         *PC = dest;}
     break;

   case (JC | JZ): //jump on C = 1 or Z = 1
      if (C == 1 || Z==1) {
          *PC = dest;}
      break;
   case (JC | JNZ): //jump on C = 1 or Z = 0
      if (C == 1 || Z==0) {
          *PC = dest;}
      break;
   case (JNC | JZ): //jump on C =0 or Z = 1
      if (C == 0 || Z==1) {
          *PC = dest;}
      break;
   case (JNC | JNZ): //jump on C = 0 or Z = 0
      if (C == 0 || Z==0) {
          *PC = dest;}
      break;

   case (JC | JN): //jump on C = 1 or N = 1
      if (C == 1 || N==1) {
          *PC = dest;}
      break;
   case (JC | JNN): //jump on C = 1 or N = 0
      if (C == 1 || N==0) {
          *PC = dest;}
      break;
   case (JNC | JN): //jump on C = 0 or N = 1
      if (C == 0 || N==1) {
          *PC = dest;}
      break;
   case (JNC | JNN): //jump on C = 0 or N = 0
      if (C == 0 || N==0) {
          *PC = dest;}
      break;


//Triple Conditions
    case (JC | JN | JZ): // jump on C=1 N=1 Z=1
       if (C==1 || N==1 || Z==1){
           *PC = dest;}
       break;
    case (JC | JNN | JZ): // jump on C=1 N=0 Z=1
      if (C==1 || N==0 || Z==1){
          *PC = dest;}
      break;
    case (JC | JN | JNZ): // jump on C=1 N=1 Z=0
      if (C==1 || N==1 || Z==0){
          *PC = dest;}
      break;
   case (JNC | JN | JZ): // jump on C=0 N=1 Z=1
      if (C==0 || N==1 || Z==1){
          *PC = dest;}
      break;
   case (JC | JNN | JNZ): // jump on C=1 N=0 Z=0
      if (C==1 || N==0|| Z==0){
          *PC = dest;}
      break;
   case (JNC | JN | JNZ): // jump on C=0 N=1 Z=0
      if (C==0 || N==1|| Z==0){
          *PC = dest;}
      break;
   case (JNC | JNN | JZ): // jump on C=0 N=0 Z=1
      if (C==0 || N==0|| Z==1){
          *PC = dest;}
      break;
   case (JNC | JNN | JNZ): // jump on C=0 N=0 Z=0
      if (C==0 || N==0|| Z==0){
          *PC = dest;}
      break;

}
}

#endif /* JUMPFUNCTION_CPP_ */
