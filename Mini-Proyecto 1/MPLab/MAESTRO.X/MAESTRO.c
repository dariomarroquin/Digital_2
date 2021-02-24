/*
 * File:   MAESTRO.c
 * Author: crade
 *
 * Created on 23 de febrero de 2021, 19:06
 */

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



#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "lcd.h"
#include "spi.h"
#include "usart.h"



//-----------------------------------------------------------------------------
//Creacion Variables
//--------------------------------------------
#define CS PORTCbits.RC0 
#define CS1 PORTCbits.RC1 
#define CS2 PORTCbits.RC2 

#define _XTAL_FREQ 8000000            //8 MHZ
uint8_t v=0;
uint8_t c1=0;
uint8_t c2=0;
uint8_t temp=0;
uint16_t vint=0;
float V1 = 0.00;
char valores[3];
char buff[20];
//-----------------------------------------------------------------------------
//Funciones
//--------------------------------------------
void Setup (void);



//-----------------------------------------------------------------------------
//CONFIG puertos
//-----------------------------------------------------------------------------
void Setup(void){

    
    ANSEL = 0;
    ANSELH = 0;
    
    TRISA= 0;
    PORTA= 0;
    
    TRISB= 0;
    PORTB= 0;
    
    TRISD = 0;
    PORTD= 0;
    
    TRISE = 0;
    PORTE = 0;
    
    IOCB= 0;
    
    
    
}

//-----------------------------------------------------------------------------
//Interrupcion
//-----------------------------------------------------------------------------



void __interrupt() myISR(void){
    if(PIR1bits.TXIF == 1){
       TXREG = buff[c1];
       if (c1 == 20){
           c1=0;       
       }
        else {
            c1++;
        }   
    }
}


//-----------------------------------------------------------------------------
//---------------------------MAIN----------------------------------------------
//-----------------------------------------------------------------------------

void main(void) {
    Setup();        //Config puertos
    LCD_Initialize();
    USART_Initialize(9600);
    SPIMas();
    
    while(1){
        CS = 0;
        SSPBUF = 1;
        if (!SSPSTATbits.BF){
            V1=SSPBUF;
        }
        __delay_ms(15);
        
        CS= 1;
        CS1 = 0;
        SSPBUF = 1;
        if(!SSPSTATbits.BF){
            c2 = SSPBUF;
        }
        __delay_ms(15);
        
        CS1 = 1;
        CS2 = 0;
        SSPBUF = 1;  
        if(!SSPSTATbits.BF){
            temp = SSPBUF;
        }
        __delay_ms(15);
        
        
        CS2 = 1;
        
        vint = (uint16_t)(((V1*500)/255));
  
        
        //DISPLAY LCD
        LCDGoto(0,0);
        LCDPutStr(" S1:    S2:    S3:");
        sprintf(buff, "%i.%iV %3i %i\r\n", valores[2],valores[1], c2,temp);
        LCDGoto(0,1);
        LCDPutStr(buff);
        
    }
    
    
    
            
    
}
