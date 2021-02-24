/*
 * File:   ADC.c
 * Author: Dario Marroquin
 *Libreria ADC
 * Created on 8 de febrero de 2021, 18:13
 */

//Libreria
#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000


void config_ADC () {
    ADCON0bits.ADCS = 1;
    ADCON1 = 0;  
}

uint8_t ValorADC (uint8_t x){
    switch (x){
        case 0: TRISAbits.TRISA0 = 1; ANSELbits.ANS0 = 1; ADCON0bits.CHS = 0;   break; //Aqui se definen los puertos que cuentan con ADC para poder realizar la conversion al pic
        case 1: TRISAbits.TRISA1 = 1; ANSELbits.ANS1 = 1; ADCON0bits.CHS = 1;   break;
        case 2: TRISAbits.TRISA2 = 1; ANSELbits.ANS2 = 1; ADCON0bits.CHS = 2;   break;
        case 3: TRISAbits.TRISA3 = 1; ANSELbits.ANS3 = 1; ADCON0bits.CHS = 3;   break;
        case 4: TRISAbits.TRISA5 = 1; ANSELbits.ANS4 = 1; ADCON0bits.CHS = 4;   break;
        case 5: TRISEbits.TRISE0 = 1; ANSELbits.ANS5 = 1; ADCON0bits.CHS = 5;   break;
        case 6: TRISEbits.TRISE2 = 1; ANSELbits.ANS6 = 1; ADCON0bits.CHS = 6;   break;
        case 7: TRISEbits.TRISE3 = 1; ANSELbits.ANS7 = 1; ADCON0bits.CHS = 7;   break;
        case 8: TRISBbits.TRISB2 = 1; ANSELHbits.ANS8 = 1; ADCON0bits.CHS = 8;   break;
        case 9: TRISBbits.TRISB3 = 1; ANSELHbits.ANS9 = 1; ADCON0bits.CHS = 9;   break;
        case 10: TRISBbits.TRISB1 = 1; ANSELHbits.ANS10 = 1; ADCON0bits.CHS = 10;  break;
        case 11: TRISBbits.TRISB4 = 1; ANSELHbits.ANS11= 1; ADCON0bits.CHS = 11;  break;
        case 12: TRISBbits.TRISB0 = 1; ANSELHbits.ANS12 = 1; ADCON0bits.CHS = 12;  break;
        case 13: TRISBbits.TRISB5 = 1; ANSELHbits.ANS13 = 1; ADCON0bits.CHS = 13;  break;
        default: return 0;
    }
    ADCON0bits.ADON = 1;
    __delay_us(35);
    ADCON0bits.GO = 1;
    resultado:
    if   (ADCON0bits.GO_DONE ==1){goto resultado;}
    else {ADCON0bits.ADON=0; return ADRESH;}
    
}
