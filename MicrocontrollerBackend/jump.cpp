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

int bin2dec3bit(char* bin) {
    int dec = 0;
    if (bin[0] == '1')
        dec = dec + 4;
    if (bin[1] == '1')
        dec = dec + 2;
    if (bin[2] == '1')
        dec = dec + 1;
  return dec;
}

/* inst         : is the jump code in binary char i.e '11cnzuuu'
 * dest         : is the next value for PC if the jump is true
 * C,N, and Z   : boolean values for the current C N Z flags
 * PC           : the current value of PC
 */
void JUMP(char* inst, char* dest, Statusflags& object, char* PC)  {

    //setup boolean values for CNZ from the globals
    bool C = object.getc();
    bool N = object.getn();
    bool Z = object.getz();

    //unconditional jump test
    if (inst == 'À') {
        PC = dest;
        return ;
    }

    // setup conditional bits for
    int dec_condjump = 4*((inst >> 5) & 0x1) + 2*((inst >> 4) & 0x1) + 1*((inst >> 3) & 0x1);

    // get our u terms as boolean
        bool C_test;
        bool temp_bit = (inst >> 2) & 0x1;
        if (temp_bit == '1') {
            C_test = 1; }
        else {
            C_test = 0;
        }
        bool N_test;
        bool temp_bit = (inst >> 1) & 0x1;
        if (temp_bit == '1') {
            N_test = 1; }
        else {
            N_test = 0;
        }
        bool Z_test;
        bool temp_bit = (inst >> 0) & 0x1;
        if (temp_bit == '1') {
            Z_test = 1; }
        else {
            Z_test = 0;
        }

        // Cases to find if a jump should occur
        switch (dec_condjump)
        {
        // 111 jump depends on C,N, and Z
           case 7:
           if ((C==C_test) && (N==N_test) && (Z==Z_test) ){
           PC = dest;
           }
           break;

        // 110 jump depends on C and N
           case 6:
           if ((C==C_test) && (N==N_test) ){
           PC = dest;
           }
           break;

         // 101 jump depends on C and Z
            case 5:
            if ((C==C_test) && (Z==Z_test) ){
            PC = dest;
            }
            break;

            // 011 jump depends on N and Z
            case 3:
            if ((N==N_test) && (Z==Z_test) ){
            PC = dest;
            }
            break;

            // 100 jump depends on C
            case 4:
            if ( (C==C_test) ){
            PC = dest;
            }
            break;

            // 010 jump depends on N
            case 2:
            if ( (N==N_test) ){
            PC = dest;
            }
            break;

            // 001 jump depends on Z
            case 1:
            if ( (Z==Z_test) ){
            PC = dest;
            }
            break;


}
}
#endif /* JUMPFUNCTION_CPP_ */




