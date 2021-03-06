/*
 * File:   LAB3.c
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
#include "LCD.h"
#include "ADC.h"
#include "USART.h"

//-----------------------------------------------------------------------------
//Creacion Variables
//-----------------------------------------------------------------------------
uint8_t contador = 0; 
uint8_t vADC1;
uint8_t vADC2;
float V1= 0.0;
float V2 = 0.0;




//-----------------------------------------------------------------------------
//Listas
//-----------------------------------------------------------------------------
char RUSART = 0;
char data[20];

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
    
    ANSELH = 0;
    ANSEL  = 0;
    
    
    TRISA = 0;
    PORTA = 0;
    
    TRISB = 0;
    PORTB = 0;
 
    TRISE = 0;
    PORTE = 0;

 
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE   = 1;
    PIR1bits.RCIF   = 0;
    INTCONbits.GIE  = 1;
    
}

//-----------------------------------------------------------------------------
//Conversion
//-----------------------------------------------------------------------------
float conversion(uint8_t b){
    return b*0.0196;        //Convertir voltaje a binario
}

//-----------------------------------------------------------------------------
//Interrupcion
//-----------------------------------------------------------------------------
void __interrupt() ISR(){
    if (RCIF == 1){         //ACTIVA UART
        RCIF = 0;           //Apaga bander
        RUSART= Read_USART();   //Lee valor recibido 
        if (RUSART == '+'){contador++;}     //Lee para sumar o restar contador
        else if (RUSART== '-'){contador--;}    
    };
}


void main(void) {
    Setup();        //Config puertos
    config_ADC();   //Config ADC
    USART_Init(9600);   //Baudrate usart
    LCD_ON();           //Encender LCD
    LCD_Clear();        //Limpiar LCD
    while(1){
      vADC1 = ValorADC(0);  //Leer ADC y guardar en variables
      vADC2 = ValorADC(1);
      V1 = conversion(vADC1); //Voltajes a binarios
      V2 = conversion(vADC2);
      Write_USART_String("V1   V2   contador \n");  // Datos del pic a cmd
      sprintf(data, "%2.1f   %2.1f   %d", V1, V2, contador); //Voltajes a string para envio a compu
      Write_USART_String(data);         //Envia string de valores a computadora
      Write_USART(13);                  //Estas ecuaciones dan salto de line
      Write_USART(10);          
      LCD_Clear();                      //Limpiar LCD
      LCD_Cursor(1,1);                  //Cursor en prumera fila
      LCD_Print("V1   V2   conta");     //Titulos de tabla
      LCD_Cursor(2,0);                  //Cursor a segunda fila
      LCD_Print(data);                  //Imprimir datos en LCD
      __delay_ms(500);      
    }
    return;
}
