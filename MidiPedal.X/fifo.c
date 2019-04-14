
/******************************************************************************************
** 32 Channel PWM
** Marcus Schmidt 2009
** Version 2.0
**
** Fifo zur Pufferung eingehener Kommandos
** [[ ToDo: BufferOverflows werden nicht geblockt und auch niocht erkannt.
******************************************************************************************/

#include "includes.h"

/*
** Ringpuffer
*/
unsigned char fifo[FIFO_SIZE];

/*
** Index der schreibposition
*/
unsigned char fifoIn;

/*
** index der Leseposition
*/
unsigned char fifoOut;

/******************************************************************************************
** Fifo initialisieren.
** Schreib und lesepointer auf 0
*/
void fifoInit()  {

   fifoIn  = 0;
   fifoOut = 0;
}


/******************************************************************************************
** Ein zeichen aus dem Ringpuffer holen.
** Achtung ! Vorher prüfen, ( mit fifoEmpty() )
** ob es zeichen zur Abholung gibt.
*/
unsigned char fifoGet()  {

    unsigned char v = fifo[fifoOut];


    return fifo[fifoOut++ & FIFO_MASK];
}

/******************************************************************************************
** Ein zeichen in dem Ringpuffer legen.
** es wird nicht geprüft, ob der Puffer voll ist; ggf. wird
** das Älteste Zeichen überschrieben
*/
void fifoPut(unsigned char in)  {
/*
    if ( ((fifoIn + 1) & 0x0F) == (fifoOut & 0x0F) )  {
     //   SET_DEBUG5;
    }
*/
    fifo[fifoIn++ & FIFO_MASK] = in;
}

/******************************************************************************************
** testet, ob der Ringbuffer leer ist.
*/
unsigned char fifoEmpty()  {

  return (fifoIn & FIFO_MASK) == (fifoOut & FIFO_MASK);

}