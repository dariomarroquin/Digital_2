/*
 * File:   ADC.c
 * Author: DARIO MARROQUIN
 * Multiplexor
 *
 * Created on 5 de febrero de 2021, 13:32
 */


//Libreria
#include <stdint.h> 
#include <pic16f887.h>
#include "MTPLX.h"



//Funcion de header

void Timer0 (void) {
    OPTION_REG  = 0x84;
    TMR0        = 100;
    INTCON      = 0b11101000;
}
