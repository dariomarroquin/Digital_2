/*
 * File:   LAB2.c
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
#include "ADC.h"
#include "MTPLX.h"


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

#define T1 PORTEbits.RE0                //Transistor Display 1
#define T2  PORTEbits.RE1              //Transistor display 2
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
char vadc;
char masadc;
char menadc;
char mtplx1;
char mtplx2;
char f = 1;


//----------------------------------------------------------------------------
//Tabla 7 segmentos
//----------------------------------------------------------------------------
char tabla [16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};


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
    
    
    //ADC
    ADCON0 = 0b01010101;
    
    //Pot
    ANSEL = 0b00000001;
    TRISA = 0b00000001;
    
    //7 SEG
    TRISC = 0;
    PORTC = 0;
    
    //TRANSISTORES
    TRISE = 0;
    PORTE = 0;
    
    
    
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
       
       if (PIR1bits.ADIF == 1){
           f=1;
  
           //Insteramos Assembler
           asm("MOVF  ADRESH,W"); //ADC  a W
           asm("MOVWF _vadc");    //Meto valor W a mi variable del adc
           asm("MOVWF  _menadc"); // Muevo 4 bits menos significativo
           asm("SWAPF ADRESH,W"); // Muevo ADC a w
           asm("ANDLW 0b00001111"); //Con and rellenar bit
           asm("MOVWF _masadc");    //Muevo bits mas significativos
           asm("MOVF _menadc, W");  //Muevo ADC a W
           asm("ANDLW 0b00001111"); //Se rellenan bits
           asm("MOVWF    _menadc"); //Muevo adc menos significativos a 2do display
           PIR1bits.ADIF = 0;
       }
       
       if(INTCONbits.T0IF == 1){   //Interrupcion Timer0
           TMR0= 100;
           if(T1 == 1){
               T1= 0;
               T2 = 1;
               PORTC = mtplx2;
           }
           else{
               T1 = 1;
               T2 = 0;
               PORTC = mtplx1;
           }
          INTCONbits.T0IF = 0; 
       }
    }




void main(void) {
    Setup();
    config_INTB();
    Timer0();
    
    while (1){
        PORTD = contador;
        config_ADC(f);
        mtplx1 = tabla[menadc];
        mtplx2 = tabla[masadc];
        
        //Comparacion
        if (vadc > contador){
            PORTCbits.RC7 = 1;
        }
        else {
            PORTCbits.RC7 = 0;
        }
    }
    
   
}
