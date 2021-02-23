/*
 * File:   INTERRB.c
 * Author: Dario Marroquin
 *InterrucĄpciones Puerto B
 * Created on 4 de febrero de 2021, 18:50
 */

//Libreria
#include <stdint.h> 
#include <pic16f887.h>
#include "INTERRB.h"


//Funcion de header

void config_INTB(void) {
    INTCON  = 0b11101000; //Activa interrupciones y timer
    IOCB = 0b00000011;
}
