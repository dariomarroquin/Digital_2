/*
 * File:   ESCLAVO_1
 * Author: Dario Marroquin
 * Carne:  18269
 * Created on 29 de enero de 2021, 8:49
 */

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#define _XTAL_FREQ 8000000

//-----------------------------------------------------------------------------
//Librerias
//-----------------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "ADC.h"
#include "spies.h"


//-----------------------------------------------------------------------------
//Creacion Variables
//-----------------------------------------------------------------------------
int vADC=0;
int  V1= 0;

//-----------------------------------------------------------------------------
//Funciones
//--------------------------------------------
void Setup (void);
float conversion(uint8_t b);
void __interrupt() ISR();

//-----------------------------------------------------------------------------
//CONFIG puertos
//-----------------------------------------------------------------------------
void Setup(void){
    TRISB=0;
    PORTB=0;
    ANSEL=0;
    ANSELH=0;
    TRISD= 0; 
    PORTD= 0; 
    config_ADC();
    SPI_ES();
       
}



//-----------------------------------------------------------------------------
//Interrupcion
//-----------------------------------------------------------------------------
void interr (void){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

//-----------------------------------------------------------------------------
//Conversion
//-----------------------------------------------------------------------------
float conversion(uint8_t b){
    return b*0.0196;        //Convertir voltaje a binario
}

void __interrupt() ISR(){

    
    if(PIR1bits.SSPIF){
        if(!SSPSTATbits.BF){
            PORTD = SSPBUF;
        }
        SSPBUF = vADC;
        PIR1bits.SSPIF = 0;
    }
    
}


void main(void) {
    Setup();        //Config puertos
    interr();
    while (1) {
        vADC= ValorADC(0);
        //V1 = conversion(vADC);
        PORTB=vADC;
    
    }
}
