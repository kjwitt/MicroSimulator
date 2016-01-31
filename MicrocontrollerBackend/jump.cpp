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
void JUMP(char* inst, char* dest, bool C, bool N, bool Z, char* PC)  {

    //unconditional jump test
    if (inst == "11000000") {
        PC = dest;
        return ;
    }

    // setup conditional bits for
    char condjump[3];
    strncpy(condjump, inst+2, 3);
    condjump[3] = '\0';
    int dec_condjump = bin2dec3bit(condjump);

    // get our u terms as boolean
        bool C_test;
        if (inst[5] == '1') {
            C_test = 1; }
        else {
            C_test = 0;
        }
        bool N_test;
        if (inst[6] == '1') {
            N_test = 1; }
        else {
            N_test = 0;
        }
        bool Z_test;
        if (inst[7] == '1') {
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




