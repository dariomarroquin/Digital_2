/*
 * File:   LAB1.c
 * Author: crade
 *
 * Created on 28 de enero de 2021, 17:39
 */
#include <xc.h>

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
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

#define SEMROJO PORTEbits.RE0
#define SEMAMA  PORTEbits.RE1
#define SEMVER  PORTEbits.RE2
#define _XTAL_FREQ 8000000            //8 MHZ

//-----------------------------------------------------------------------------
//Funciones
//--------------------------------------------
void Setup (void);
void Semaforo (void);
int Carrera (unsigned int Race);
int  Winner = 0;

//-----------------------------------------------------------------------------
//Listas
//--------------------------------------------

char P1 [8] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};
char P2 [8] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};
char Player1 = 0;
char Player2 = 0;

//-----------------------------------------------------------------------------
//CONFIG
//--------------------------------------------
void Setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISC = 0;
    PORTC = 0;
    
    TRISD = 0;
    PORTD = 0;
    
    TRISB = 0;
    PORTB = 0;
    
    TRISA = 0b00000111;
    PORTA = 0;
    
    TRISE = 0;
    PORTE = 0;
    
}

//-----------------------------------------------------------------------------
//Semaforo
//--------------------------------------------

void Semaforo (void){
    Player1 = 0;
    Player2 = 0;
    Winner = 0;
    
    
    SEMROJO = 1;
    __delay_ms(500);
    SEMROJO = 0;
    
    SEMAMA = 1;
    __delay_ms(500);
    SEMAMA = 0;
    
    SEMVER = 1;
    __delay_ms(500);
    SEMVER = 0;
    
    PORTC = P1[Player1];
    PORTD = P2[Player2];
}

//-----------------------------------------------------------------------------
//Carrera
//--------------------------------------------

int Carrera (unsigned int Race){
    if (Race==1){
        while (1){
            if (PORTAbits.RA0 ==1){
                __delay_ms(50);
                if (PORTAbits.RA0 ==0){
                    Player1++;
                    PORTC = P1[Player1];
                     if (Player1==8){
                           return (1); 
                            }
                }
            }    
            if (PORTAbits.RA1 ==1){
                    __delay_ms(50);
                    if (PORTAbits.RA1 ==0){
                        Player2++;
                        PORTD = P2[Player2];
                        if (Player2==8){
                             return (2); 
                              }
                    }
            }
        }
    }
}


//-----------------------------------------------------------------------------
//Programis
//--------------------------------------------
void main(void) {
    Setup();
    while(1){
     if (PORTAbits.RA2 == 1){
         __delay_ms(50);
     }
     if (PORTAbits.RA2 == 0){
        Semaforo();
        Winner = Carrera(1);
        if (Winner == 1){
            PORTB = 0b00000001;
        }
        else  {
            PORTB = 0b00000010;
        }
        }

        
    }

}
