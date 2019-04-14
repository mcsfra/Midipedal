#include "includes.h"

/*
**
*/


#define NOTE_ON    0x90
#define NOTE_OFF   0x80

/*
** Baudrate
** Datasheet Page 280
*/

#define MEGAHERTZ 1000000
#define FOSC (8 * MEGAHERTZ)


/*
** Sendet Bufferinhalt
*/

void initMidi(void)  {

    ANSELCbits.ANSC6   = 0;     // Analog abschalten  (Seite 269)

    BAUDCON1bits.BRG16 = 0;     // Baudratengenerator 8-Bit
   // BAUDCON1bits.CKTXP = 1;     // polaritaet verdrehen
    TXSTA1bits.BRGH    = 0;     //
    SPBRG1             = 3;     // Baudrate einstellen
    SPBRGH1            = 0;     //
   
    TXSTA1bits.TXEN    = 1;     // transmit enablen
    TXSTA1bits.SYNC    = 0;     // asynchron

    RCSTA1bits.SPEN    = 1;     // serialport enable

}

void sendMidi(void)  {

   // wenn der fifo etwas enthält UND das senderegister leer ist
   // ein byte entnehmen und senden

   if ( !fifoEmpty() && PIR1bits.TX1IF == 1)  {
       TXREG1 = fifoGet();
   }
}


void noteOn(unsigned char note, unsigned char velocity)  {

   fifoPut(NOTE_ON | getMidiChannel());
   fifoPut(note + getTranspose());
   fifoPut(velocity);
  
}


void noteOff(unsigned char note, unsigned char velocity)  {


   fifoPut(NOTE_OFF | getMidiChannel());
   fifoPut(note + getTranspose());
   fifoPut(velocity);

}

unsigned char getMidiChannel()  {

    unsigned char pb = PORTB;

    pb = pb >> 2;
    pb = pb & 0x0F;

    return pb;
    //return ((PORTB >> 2) & 0x0F);

}

unsigned char getTranspose() {

    unsigned char pb = PORTB;
    unsigned char pd = PORTD;
    unsigned char r;

    pb = pb << 1;
    pb = pb & 0b00000110;

    pd = pd >> 7;
    pd = pd & 0x01;

    r = pb | pd;
    r = r *12;

    return r;

    //return ((((PORTB << 1 ) & 0b00000110 ) | ((PORTD >> 7) & 0x01)) * 12);


}

void sendMidiStream(void)  {

    return;

    for (;;)  {


        if (fifoEmpty())  {
            noteOn(0x22,0x33);
        }

        while(!fifoEmpty())  {
            sendMidi();
        }


    }



}