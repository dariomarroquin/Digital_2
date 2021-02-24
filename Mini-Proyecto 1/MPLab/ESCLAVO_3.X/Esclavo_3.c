//-----------------------------------------------
//Librerias
//-----------------------------------------------






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
#include "ADC.h"
#include "spies.h"

//-----------------------------------------------------------------------------
//Creacion Variables
//--------------------------------------------

#define _XTAL_FREQ 8000000            //8 MHZ
int vADC=0;
float V1= 0.0;

uint16_t temperature = 0;
uint8_t valor = 0;
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
    
    TRISD=0;
    PORTD=0;
    
    ANSEL=0;
    ANSELH=0;
    config_ADC();
       
}

//-----------------------------------------------------------------------------
//Interrupcion
//-----------------------------------------------------------------------------
void interr (void){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}


void __interrupt() ISR(){
    
    if(PIR1bits.SSPIF){
        if(!SSPSTATbits.BF){
            valor = SSPBUF;
        }
        SSPBUF = vADC;
        PIR1bits.SSPIF = 0;
    }
}

float conversion(uint8_t b){
    return b*0.0196;        //Convertir voltaje a binario
}


void main(void) {
    Setup();        //Config puertos
    interr();
    SPI_ES();
    while (1) {
        vADC= ValorADC(0);
        V1 = conversion(vADC);
        if (V1 > 0.3528){
            PORTDbits.RD0 =1;
            PORTDbits.RD1 =0;
            PORTDbits.RD2 =0;
        }
        
        if ((V1 <= 0.3528) && (V1 >= 0.25)) {
            PORTDbits.RD1 =1;
            PORTDbits.RD0 =0;
            PORTDbits.RD2 =0;
        }
        
        if (V1 < 0.25){
            PORTDbits.RD2 =1;
            PORTDbits.RD1 =0;
            PORTDbits.RD0 =0;
        }
        PORTB=vADC;
    
    }
}
