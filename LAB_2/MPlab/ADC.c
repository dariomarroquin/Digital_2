/*
 * File:   ADC.c
 * Author: DARIO MARROQUIN
 * ADC
 *
 * Created on 5 de febrero de 2021, 13:32
 */


//Libreria
#include <stdint.h> 
#include <pic16f887.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000


//Funcion de header

void config_ADC(uint8_t f) {
    INTCON  = 0b11101000; //Activa interrupciones y timer
    PIR1bits.ADIF   = 0;   //Activa 1 al terminar conversion
    PIE1bits.ADIE   = 1;   //Interrupcion Activada
    ADCON1bits.ADFM = 0;   //Bits izquierda mas significativos
    if (f == 1){
        __delay_us(10);
        f = 0;
        ADCON0bits.GO = 1;
    }
}
