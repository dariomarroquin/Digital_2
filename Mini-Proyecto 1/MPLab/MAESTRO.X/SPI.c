/*
 * File:   SPI.c
 * Author: crade
 *
 * Created on 23 de febrero de 2021, 20:21
 */


#include "spi.h"

void SPIMas(void){
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC5 = 0;
    SSPCON  = 0b00100000;
    SSPSTAT = 0; 
    
    TRISCbits.TRISC0 = 0;
    PORTCbits.RC0 = 0;
    
    TRISCbits.TRISC1 = 0;
    PORTCbits.RC1 = 1;
    
    TRISCbits.TRISC2 = 0;
    PORTCbits.RC2 = 1;
}

