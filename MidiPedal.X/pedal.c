#include "includes.h"
#include "velocities.h"

/*
** Anzahl Keys
*/

#define MAX_KEYS 13

unsigned char pedalState[MAX_KEYS];

unsigned int  pedalCount[MAX_KEYS];


#define PEDALSTATE_OFF         1
#define PEDALSTATE_OFFTOON     2
#define PEDALSTATE_DEBOUNCEON  3
#define PEDALSTATE_ON          4
#define PEDALSTATE_ONTOOFF     5
#define PEDALSTATE_DEBOUNCEOFF 6

#define DEBOUNCESPAN 400  // das sieht gut aus
//#define DEBOUNCESPAN 100  // das sieht gut aus



unsigned int  captureTics[16];
unsigned char captureValue[16];

unsigned char captureCounter = 0;


unsigned char callCounter = 0;

unsigned char pedalFailure[MAX_KEYS];

unsigned int z0 = 0;
unsigned int z1 = 0;
unsigned int z2 = 0;
unsigned int z3 = 0;
unsigned int zg = 0;

/*
 *    flankenanalyse
 */

unsigned char lastStateOben = 1;
unsigned char lastStateUnten = 0;

unsigned char lastState = 1;
unsigned char captureStates[16];
unsigned char lastStateCounter = 0;


unsigned int scOben[16];
unsigned int scUnten[16];

unsigned char ccu = 0;
unsigned char cco = 0;

unsigned int rundenzaehler = 0;

unsigned int timerwert;

unsigned char  keyStates[MAX_KEYS];

#define UPPER_ON  0x01
#define LOWER_ON  0x02

#define RAIL_ON  1
#define RAIL_OFF 0

#define OLDVERSION 1
//#define NEWVERSION 1
//#define NEWESTVERSION 1

#define DEBUG_SWITICHNG 1


#ifdef NEWESTVERSION

#define DEBUG_SWITCHING 1


void probePedal(void)  {

    unsigned char i;
    unsigned char velocity;

    if (rundenzaehler > 0)
        rundenzaehler++; 


  //  TRIS_UPPERRAIL = 0;
    OUT_UPPERRAIL  = RAIL_ON;

    for ( i = 0; i < MAX_KEYS; i++)  {
       keyStates[i] = 0;
    }

    i = getState(12);
    i = getState(11); 

 //   for(i = 0; i < 20; i++)  {
 //        Nop();
 //   }

    for ( i = 0; i < MAX_KEYS; i++)  {
       if (getState(i) )  {
          keyStates[i] |= UPPER_ON;
       }
       else  {
          if ( pedalState[i] == PEDALSTATE_OFF)   {
              pedalState[i] = PEDALSTATE_OFFTOON;
              pedalCount[i] = getTimer();
              rundenzaehler = 1;
          }
       }

#ifdef DEBUG_SWITCHING
       if ( lastStateOben != getState(0) )  {
         lastStateOben = lastStateOben == 1 ? 0 : 1;
         scOben[cco] = getTimer();
         cco++;
       }
#endif
   }

   // TRIS_UPPERRAIL = 1;
  //  TRIS_LOWERRAIL = 0;

    OUT_UPPERRAIL = RAIL_OFF;
    OUT_LOWERRAIL = RAIL_ON;

    for(i = 0; i < 20; i++)  {
        Nop();
    }

    for ( i = 0; i < MAX_KEYS; i++)  {

       if (getState(i))  {
          keyStates[i] |= LOWER_ON;

          if ( pedalState[i] == PEDALSTATE_OFFTOON )  {

              velocity      = calculateVelocity(i);  // mach das schöner: calculateVelocity(starttime, endtime)
              pedalState[i] = PEDALSTATE_DEBOUNCEON;
              noteOn(i, velocity);
          }
       }
#ifdef DEBUG_SWITCHING
       if ( lastStateUnten != getState(0) )  {
          lastStateUnten =  lastStateUnten == 1 ? 0 : 1;
          scUnten[ccu] = getTimer();
          ccu++;
       }
#endif
    }

    OUT_LOWERRAIL = RAIL_OFF;

    zg++;

    switch ( keyStates[0])  {

        case 0: z0++; break;
        case 1: z1++; break;
        case 2: z2++; break;
        case 3: z3++; break;
    }

}

/*
** Statemachine zur tastenauswertung
*/

void evalKeyStates(void)  {

    unsigned char i;
    unsigned char velocity;

    return;

    for ( i = 0; i < MAX_KEYS; i++)  {

     //   if (i != 4 && i != 6)
     //       continue;


        if (lastState != pedalState[i] && lastStateCounter < 16)  {
            lastState = pedalState[i];
            captureStates[lastStateCounter] =  pedalState[i];
            lastStateCounter++;
        }

        switch (pedalState[i])  {

            case PEDALSTATE_OFF:
                 if ( (keyStates[i] != UPPER_ON) )  {
                 //if ( !(keyStates[i] & UPPER_ON) )  {
                    pedalState[i] = PEDALSTATE_OFFTOON;
                    pedalCount[i] = getTimer();
                 }
                 break;

            case PEDALSTATE_ON:
                 if ( (keyStates[i] != LOWER_ON) )  {
                 //if ( !(keyStates[i] & LOWER_ON) )  {
                    pedalState[i] = PEDALSTATE_ONTOOFF;
                    pedalCount[i] = getTimer();
                 }
                 break;

            case PEDALSTATE_OFFTOON:
                 if ( keyStates[i] == LOWER_ON )  { // jawoll, pedal ist unten
                 //if ( keyStates[i] & LOWER_ON )  { // jawoll, pedal ist unten
                     velocity      = calculateVelocity(i);
                     pedalState[i] = PEDALSTATE_DEBOUNCEON;
                     noteOn(i, velocity);
                 }
                 break;

            case PEDALSTATE_ONTOOFF:
                 if ( keyStates[i] == UPPER_ON)  { // jawoll, pedal ist unten
                // if ( keyStates[i] & UPPER_ON)  { // jawoll, pedal ist unten
                    velocity = 0;
                   // velocity =  calculateVelocity(i);
                    pedalState[i] = PEDALSTATE_DEBOUNCEOFF;
                    noteOff(i, velocity);
                 }
                 break;

            case PEDALSTATE_DEBOUNCEON:
                 debounce(i,PEDALSTATE_ON);
                 break;

            case PEDALSTATE_DEBOUNCEOFF:
                 debounce(i,PEDALSTATE_OFF);
                 break;
        }
    }
}


unsigned char getState(unsigned char key)  {

 

    switch (key)  {
        case  0: return KEY_C;
        case  1: return KEY_CIS;
        case  2: return KEY_D;
        case  3: return KEY_DIS;
        case  4: return KEY_E;
        case  5: return KEY_F;
        case  6: return KEY_FIS;
        case  7: return KEY_G;
        case  8: return KEY_GIS;
        case  9: return KEY_A;
        case 10: return KEY_B;
        case 11: return KEY_H;
        case 12: return KEY_C2;
    }
    return 0;
}

void debounce(unsigned char key, unsigned char nextState)  {

/*
    unsigned int newTime = getTimer();
    unsigned int oldTime = pedalCount[key];
    unsigned int result;

    if (newTime > oldTime)
        result = newTime - oldTime;
    else
        result = (0xFFFF - oldTime) + newTime;

      if ( result > 4000)
         pedalState[key] = nextState;
*/
         pedalState[key] = nextState;


}

#endif




/*
 **
 */

void initPedal(void)  {

    unsigned char i;

    T0CONbits.TMR0ON = 0;

    TMR0H = 0;
    TMR0L = 0;
    INTCONbits.TMR0IF = 0;

    T0CONbits.T08BIT = 0;    // 16 Bit
    T0CONbits.T0CS   = 0;    // INput Source: FOSC/4
    T0CONbits.PSA    = 0;    // Use Prescaler (nagative logik. grrr)

    T0CONbits.T0PS   = 7;    // Prescaler 1:16
 //   T0CONbits.T0PS   = 3;    // Prescaler 1:16
 //   T0CONbits.T0PS   = 0;    // Prescaler 1:16

    /*
    ** Timer Interupt einschalten
    */
    RCONbits.IPEN      = 1;   //
    INTCONbits.PEIE    = 1;   // das sollte garnicht nötig sein, oder?
    INTCON2bits.TMR0IP = 0;
    INTCONbits.TMR0IE  = 1;
    INTCONbits.GIEL    = 1;
    INTCONbits.GIE     = 1;

    /*
    ** und nun einschalten
    */
    T0CONbits.TMR0ON = 1;

    //   TRISA       |= 0x03;
    OUT_UPPERRAIL = 0;
    OUT_LOWERRAIL = 0;

    for (i = 0; i < MAX_KEYS; i++)  {
        pedalState[i]   = PEDALSTATE_OFF;
        pedalCount[i]   = 0;
        pedalFailure[i] = 0x00;
    }

    /*
    ** Debugstuff
    */
    for (i = 0; i < 16; i++)  {
        captureTics[i]   = 0;
        captureValue[i]  = 0;
        captureStates[i] = 0;
        scOben[i]  = 0;
        scUnten[i] = 0;
    }

}


unsigned int zaehler = 0;




#ifdef OLDVERSION
void probePedal(void)  {

    unsigned char i;
    unsigned char velocity;

    unsigned char r;

    if ( lastStateOben != getOffState(0) )  {
        lastStateOben = (lastStateOben == 0 ? 1 : 0);
        scOben[cco] = getTimer();
        cco++;
    }

    if ( lastStateUnten != getOnState(0) )  {
       lastStateUnten = (lastStateUnten == 0 ? 1 : 0);
       scUnten[ccu] = getTimer();
       ccu++;
    }


    for ( i = 0; i < MAX_KEYS; i++)  {

        /*
        ** Test for Pedalswitch errors
        */
        if ( getOnState(i) && getOffState(i) ) { // beide an !
            pedalFailure[i] |= 0x02;
        }

        if ( !getOnState(i) && !getOffState(i) && pedalState[i] != PEDALSTATE_ONTOOFF && pedalState[i] != PEDALSTATE_OFFTOON)  { // beide aus und taste nicht unterwegs
            pedalFailure[i] |= 0x04;
        }

        switch (pedalState[i])  {

            case PEDALSTATE_OFF:
                 if ( !getOffState(i) )  {
                    pedalState[i] = PEDALSTATE_OFFTOON;
                    pedalCount[i] = getTimer();
                 }
                 break;

            case PEDALSTATE_ON:
                 if ( !getOnState(i)  )  {
                    pedalState[i] = PEDALSTATE_ONTOOFF;
                    pedalCount[i] = getTimer();
                 }
                 break;

            case PEDALSTATE_OFFTOON:
               
                 if ( getOnState(i))  { // jawoll, pedal ist unten
                     velocity      = calculateVelocity(i);
                     pedalState[i] = PEDALSTATE_DEBOUNCEON;
                     noteOn(i, velocity); // immer hundert.
                 }
        //         else
        //             zaehler++;
                 break;
            case PEDALSTATE_ONTOOFF:
                 if ( getOffState(i))  { // jawoll, pedal ist unten
                    velocity = 0; 
                   // velocity =  calculateVelocity(i);
                    pedalState[i] = PEDALSTATE_DEBOUNCEOFF;
                    noteOff(i, velocity);
                 }
                 break;

            case PEDALSTATE_DEBOUNCEON:
                 debounce(i,PEDALSTATE_ON);
                 break;

            case PEDALSTATE_DEBOUNCEOFF:
                 debounce(i,PEDALSTATE_OFF);
                 break;
        }
    }
}

void evalKeyStates(void)  {
    
}

unsigned char getOnState(unsigned char key)  {

    unsigned char state;
    OUT_LOWERRAIL = 1;
    state = getState(key);
    OUT_LOWERRAIL = 0;
    return state;

}

unsigned char getOffState(unsigned char key)  {

    unsigned char state;
    OUT_UPPERRAIL = 1;
    state = getState(key);
    OUT_UPPERRAIL = 0;
    return state;
}


unsigned char getState(unsigned char key)  {
 
    unsigned char i;

    for (i = 0; i < 20; i++)  {
        Nop();
    }

    switch (key)  {
        case  0: return KEY_C;
        case  1: return KEY_CIS;
        case  2: return KEY_D;
        case  3: return KEY_DIS;
        case  4: return KEY_E;
        case  5: return KEY_F;
        case  6: return KEY_FIS;
        case  7: return KEY_G;
        case  8: return KEY_GIS;
        case  9: return KEY_A;
        case 10: return KEY_B;
        case 11: return KEY_H;
        case 12: return KEY_C2;
    }
    return 0;
}

void debounce(unsigned char key, unsigned char nextState)  {
/*
    unsigned int newTime = getTimer();
    unsigned int oldTime =  pedalCount[key];
    unsigned int result;

    if (newTime > oldTime)
        result = newTime - oldTime;
    else
        result = (0xFFFF - oldTime) + newTime;

      if ( result > 400)
         pedalState[key] = nextState;
*/
         pedalState[key] = nextState;


}

#endif

union aTimerValue {
    unsigned int val;
    char     frac[2];
} ;

unsigned int getTimer()  {

    union aTimerValue v;

    v.frac[0] = TMR0L;
    v.frac[1] = TMR0H;

    return v.val;
 }

/*
** Berechnet den Velocity-Wert auf Basis der gemessenen Timerwerte beim loslassen und runterdrücken der Taste
** Je höher die geschwindigkeit (kleiner die timerdifferenz) ums höher der wert
 */



// ich scheine die abstände zwischen den betätigungen zu messen...
// wie kommt denn das zustande?



unsigned char calculateVelocity(unsigned char key)  {

    unsigned int tics;
    float result = INFACTOR;
    float h1, h2, h3;



    unsigned int newTime = getTimer();
    unsigned int oldTime = pedalCount[key];

    if (newTime > oldTime) 
        tics = newTime - oldTime;
    else 
        tics = (0xFFFF - oldTime) + newTime;

    /*
     * Grenzprüfung
     */
    if ( tics > (unsigned int)IN_MAX)  {
        result = OUTOFBOUNDS_LOW;
    }
    else if ( tics < (unsigned int) IN_MIN)  {
        result = OUTOFBOUNDS_HIGH;
    }
    else  {
       /*
       **  rohen timerwert zum velocitywert verrechnen
       */
//      h1 = (float)IN_MAX - (float)IN_MIN;
//      h2 = (float)OUT_MAX - (float)OUT_MIN;
//      h3 = ((float)tics) - (float)IN_MIN;
//       result =  ((h3) / (h1)) * ((h2) + (float)OUT_MIN);

        
        
        
      h1 = (float)6000 - (float)80;
      h2 = (float)125 - (float)5;
      h3 = ((float)tics) - (float)80;
       result =  127- (((h3) / (h1)) * ((h2) + (float)5));
    }
    
    
    /**/

    if ( captureCounter < 16)  {
       captureTics[captureCounter]  = tics;
       captureValue[captureCounter] = result;
    }
    captureCounter++;

    /**/

    return (unsigned char) result;
}




unsigned int timerOverflow = 0;


#pragma interrupt handleTimerOverflow

void handleTimerOverflow(void)  {

   if (INTCONbits.TMR0IF && INTCONbits.TMR0IE )   {
      INTCONbits.TMR0IF = 0;
      timerOverflow++;
   }
}