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
}

