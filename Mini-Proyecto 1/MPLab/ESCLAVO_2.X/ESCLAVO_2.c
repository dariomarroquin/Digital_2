/*
 * File:   ESCLAVO_2
 * Author: Dario Marroquin
 * Carne:  18269
 * Created on 29 de enero de 2021, 8:49
 */


//-----------------------------------------------
//Librerias
//-----------------------------------------------


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>
#include "INTERRB.h"
#include "spies.h"


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

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



//-----------------------------------------------------------------------------
//Creacion Variables
//--------------------------------------------

#define _XTAL_FREQ 8000000            //8 MHZ



//-----------------------------------------------------------------------------
//Funciones
//--------------------------------------------
void Setup (void);
void __interrupt() ISR(void); //Interrupciones



//----------------------------------------------------------------------------
//Listas
//----------------------------------------------------------------------------

char contador = 0;
uint8_t valor;

//-----------------------------------------------------------------------------
//CONFIG puertos
//--------------------------------------------
void Setup(void){
    
    ANSELH = 0b00000000;
    //Leds
    TRISD = 0;
    PORTD = 0;
    
    //Botones
    TRISB = 0b00000011;
    PORTB = 0;

}


void __interrupt() ISR(void){
       if (INTCONbits.RBIF == 1 && INTCONbits.RBIE == 1){
           if (PORTBbits.RB0 == 1){
               contador++;
           }
           
           if (PORTBbits.RB1 == 1){
               contador--;
           }    
       } 
       INTCONbits.RBIF = 0; 
       
       if(PIR1bits.SSPIF){
        if(SSPSTATbits.BF){
            valor = SSPBUF;
        }
        SSPBUF = contador;
        PIR1bits.SSPIF = 0;
    }
}
 

void main(void) {
    Setup();
    config_INTB();
    SPI_ES();
    while (1){
        PORTD = contador;
  
}
}