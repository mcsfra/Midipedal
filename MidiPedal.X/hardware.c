#include "includes.h"

void initHardware(void)  {

                       // 8MHz internal OscillatorBlock

  OSCCONbits.IDLEN = 0;

  OSCCONbits.IRCF2 = 1;
  OSCCONbits.IRCF1 = 1;
  OSCCONbits.IRCF0 = 0;

  OSCCONbits.SCS1  = 1;
  OSCCONbits.SCS0  = 0;

  /*
  ** I/O
  */

  CM1CON0  = 0;
  CM2CON0  = 0;
  SSP1CON1 = 0;


  LATA    = 0x00;
  PORTA   = 0x00;
  ANSELA  = 0x00;
  TRISA   = TRISAMASK;              // 8 Mal Ausgang



 // CCP1CON = 0;                       // Comparators OFF
 // ADCON1  = 0x7F;
 // hat das bei diesem chip ne funktion???

  TRISB   = TRISBMASK;              
  PORTB   = 0x00;
  LATB    = 0x00;
  ANSELB  = 0x00;
  TRISB   = TRISBMASK;

  LATC    = 0x00;
  PORTC   = 0x00;
  ANSELC  = 0x00; 
  TRISC   = TRISCMASK;              
 


  LATD    = 0x00;
  PORTD   = 0x00;
  ANSELD  = 0x00;
  TRISD   = TRISDMASK;              

  PORTE   = 0x00;
  LATE    = 0x00;
  ANSELE  = 0x00;                   // Datasheet page 151
  TRISE   = TRISEMASK;              

 

  /*
   * Zum Aufwecken des uC aus dem Sleep-Mode.
   */
 // INTCON2bits.RBIP = 0;     // Prioritaet: Low
 // INTCONbits.RBIE  = 1;     // Interupt on Change RB4:7

}
/*
void sleep()  {

  INTCONbits.RBIE  = 1;

  OSCCONbits.IDLEN = 0;
  OSCCONbits.SCS1  = 0;
  OSCCONbits.SCS0  = 0;

    _asm
          sleep
    _endasm

}
*/