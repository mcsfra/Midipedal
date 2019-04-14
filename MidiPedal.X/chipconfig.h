/* 
 * File:   chipconfig.h
 * Author: marcus
 *
 * Created on 7. August 2013, 19:46
 */

#ifndef __CHIPCONFIG_H__
#define __CHIPCONFIG_H__


#pragma config FOSC     = INTIO67    // Internal Oscillator RA6,7 used as IO-Ports
#pragma config PLLCFG   = ON         // PLL Ein

#pragma config PRICLKEN = ON         // Primary Clock Enabled


#pragma config FCMEN   = OFF        // Fail-Safe Clock Monitor
#pragma config IESO    = OFF        // OScillator Switchover
#pragma config PWRTEN  = ON         // Power on timer
#pragma config BOREN   = ON         // Brownout reset on
#pragma config BORV    = 285        // 2.85 V
#pragma config WDTEN   = OFF        // watchdog off
#pragma config WDTPS   = 1          // irrelevant  watchdog-postscale

#pragma config MCLRE   = EXTMCLR     // internal reset; pin is I/O

#pragma config PBADEN  = OFF        // portb -digital io and not ad
#pragma config CCP2MX  = PORTB3     // irrelevant
#pragma config CCP3MX  = PORTB5     // irrelevant

#pragma config P2BMX   = PORTD2

#pragma config T3CMX   = PORTB5     // irrelevant

#pragma config STVREN  = ON         // stack over/underflow --> reset
#pragma config LVP     = OFF        //
#pragma config XINST   = ON        // extended instructionset


#pragma config DEBUG   = ON       //




/*
** Code Protection
*/
// achtung, falschrum!
#ifdef __DEBUG
#pragma config   CP0 = OFF // code-protection
#pragma config   CP1 = OFF
#pragma config   CPB = OFF
#pragma config   CPD = OFF  // EEPROM
#pragma config  WRT0 = OFF    // write-protection
#pragma config  WRT1 = OFF
#pragma config  WRTB = OFF
#pragma config  WRTC = OFF
#pragma config  WRTD = OFF
#pragma config EBTR0 = OFF  // table read protection
#pragma config EBTR1 = OFF
#pragma config EBTRB = OFF
#else
#pragma config   CP0 = ON // code-protection
#pragma config   CP1 = ON
#pragma config   CPB = ON
#pragma config   CPD = OFF  // EEPROM immer beschreiben koennen
#pragma config  WRT0 = ON    // write-protection
#pragma config  WRT1 = ON
#pragma config  WRTB = ON
#pragma config  WRTC = ON
#pragma config  WRTD = OFF  // EEPROM
#pragma config EBTR0 = ON  // table read protection
#pragma config EBTR1 = ON
#pragma config EBTRB = ON
#endif


#endif	/* CHIPCONFIG_H */

