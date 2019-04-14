/*
 * File:   main.c
 * Author: marcus
 *
 * Created on March 2014
 */
#include "chipconfig.h"
#include "includes.h"



/*
#pragma code _RESET_INTERRUPT_VECTOR
void _reset (void)  {
    _asm goto _startup _endasm
}
*/

#pragma code _HIGH_INTERRUPT_VECTOR  = 0x0008

//#pragma interrupt _high_ISR
//#pragma interrupt _low_ISR


void _high_ISR (void)  {
   //
}

#pragma code _LOW_INTERRUPT_VECTOR   = 0x0018
void _low_ISR (void)  {
    _asm GOTO handleTimerOverflow _endasm
}



void main(void)  {

    initHardware();   // I/Os

  //  initSetup();
    initPedal();
    initMidi();

    sendMidiStream();

    for(;;)  {
     
       probePedal();   // Pedalzustände testen
       evalKeyStates(); 
       sendMidi();     // wenn was zu versenden ist

      }
}

