/*
 * File:   LCD.c
 * Author: Dario Marroquin
 *LCD
 * Created on 9 de febrero de 2021, 1:38
 */


#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#define  _XTAL_FREQ 8000000


void char_LCD(char caracter) {
    RS = 1;  //Direccion de los caracteres
    PUERTO(caracter); 
    EN = 1;         //Envia el valor de este
    __delay_us(5);
    EN = 0;         //Observar como se envio
    __delay_us(5);
    __delay_us(50);
}

void PUERTO(uint8_t x){
    if (x & 1){D0 = 1;}else{D0 = 0;}  //Aqui se define la ubicacion dependiendo del tamaño del caracter a enviar
    if (x & 2){D1 = 1;}else{D1 = 0;}
    if (x & 4){D2 = 1;}else{D2 = 0;}
    if (x & 8){D3 = 1;}else{D3 = 0;}
    if (x & 16){D4 = 1;}else{D4 = 0;}
    if (x & 32){D5 = 1;}else{D5 = 0;}
    if (x & 64){D6 = 1;}else{D6 = 0;}
    if (x & 128){D7 = 1;}else{D7 = 0;}
}

void comandosLCD(uint8_t x){
    RS=0;                   //Modifica brillo LCD
    PUERTO(x);
    EN= 1;                     //Envio caracteres
    __delay_us(5);
    EN=0;
    __delay_us(5);
    __delay_us(2);
}

void LCD_Clear(void){
    comandosLCD(0);         //Limpia LCD
    comandosLCD(1);         //INICIA LCD
}

void LCD_ON(){
    RS= 0;              //Direcciones LCD
    EN= 0;
    PUERTO(0x00);
    __delay_ms(50);
    comandosLCD(0x02);
    comandosLCD(0x38);
    comandosLCD(0x0C);
    comandosLCD(0x06);
}

void LCD_Cursor (uint8_t x, uint8_t y){
    uint8_t a;
    if (x == 1){            //Modificar linea de Arriba
        a = 0x80 + y;       // Direccion para caracteres
        comandosLCD(a);
    }
    else if (x == 2){       //Modificar linea de abajo
        a = 0xC0 + y;
        comandosLCD(a);
    }
        
}

void LCD_Print (char *a){       //Envio de texto
    int i;                      //Guardar caracter
    for (i=0; a[i] != '\0'; i++)
        char_LCD(a[i]);
}

