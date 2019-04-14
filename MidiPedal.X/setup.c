
#include "includes.h"

unsigned char transpose;
unsigned char midiChannel;

#define TRANSPOSE_OFFSET 17


#define SETUP_CHANNEL_PORT0     LATBbits.LATB0
#define SETUP_CHANNEL_PORT1     LATBbits.LATB0
#define SETUP_CHANNEL_PORT2     LATBbits.LATB0
#define SETUP_CHANNEL_PORT3     LATBbits.LATB0

#define SETUP_TRANSPOSE_PORT0   LATBbits.LATB0
#define SETUP_TRANSPOSE_PORT1   LATBbits.LATB0
#define SETUP_TRANSPOSE_PORT2   LATBbits.LATB0
#define SETUP_TRANSPOSE_PORT3   LATBbits.LATB0



void initSetup(void)  {

    transpose   = 0x20;
    midiChannel = 0x01;

}

void probeSetup(void)  {

    transpose    = SETUP_TRANSPOSE_PORT0 & 0x01;
    transpose   |= SETUP_TRANSPOSE_PORT1 & 0x02;
    transpose   |= SETUP_TRANSPOSE_PORT2 & 0x04;
    transpose   |= SETUP_TRANSPOSE_PORT3 & 0x08;

    transpose = (transpose * 12) + TRANSPOSE_OFFSET;


    midiChannel  = SETUP_CHANNEL_PORT0 & 0x01;
    midiChannel |= SETUP_CHANNEL_PORT1 & 0x02;
    midiChannel |= SETUP_CHANNEL_PORT2 & 0x04;
    midiChannel |= SETUP_CHANNEL_PORT3 & 0x08;

}
