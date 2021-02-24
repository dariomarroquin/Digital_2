/*
 * File:   spies.c
 * Author: crade
 *
 * Created on 23 de febrero de 2021, 20:56
 */


#include "spies.h"

void SPI_ES(void) {
    
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC5 = 0;
    TRISAbits.TRISA5 = 1;
    SSPCON  = 0b00100100;
    SSPSTAT = 0;
    
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
}
    