/* 
 * File:   hardware.h
 * Author: marcus
 *
 * Created on 23. March 2014, 19:02
 */

#ifndef __HARDWARE_H__
#define	__HARDWARE_H__



// RC6 - TX1 - Pin25

#define OUT_LOWERRAIL  LATAbits.LATA0
#define OUT_UPPERRAIL  LATAbits.LATA1



#define TRIS_LOWERRAIL  TRISAbits.TRISA0
#define TRIS_UPPERRAIL  TRISAbits.TRISA1



// pedalinputpins wired in pedal.c

/*
 *  1 - Input
 */

#define KEY_C    PORTDbits.RD1    // 0
#define KEY_CIS  PORTDbits.RD0    // 1

#define KEY_D    PORTCbits.RC1    // 3
#define KEY_DIS  PORTCbits.RC3    // 4
#define KEY_E    PORTCbits.RC2    // 2



#define KEY_F    PORTCbits.RC0    // 5
#define KEY_FIS  PORTAbits.RA6    // 6 -- Klemmt
#define KEY_G    PORTAbits.RA7    // 7 -- Klemmt
#define KEY_GIS  PORTEbits.RE2    // 8
#define KEY_A    PORTEbits.RE1    // 9
#define KEY_B    PORTEbits.RE0    // A -- Klemmt
#define KEY_H    PORTAbits.RA5    // B -- Klemmt
#define KEY_C2   PORTAbits.RA3    // C




#define TRISAMASK   0b11101000
#define TRISBMASK   0b00111111
#define TRISCMASK   0b00101111
#define TRISDMASK   0b10100011
#define TRISEMASK   0b00100111



extern void initHardware(void);

extern void sleep(void); 



#endif	/* HARDWARE_H */

