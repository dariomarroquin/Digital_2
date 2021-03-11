/*
 * File:   I2C.c
 * Author: crade
 *
 * Created on 10 de marzo de 2021, 15:11
 */


#include <xc.h>
#include "I2C.h"

void I2C_init(){
    TRISC3 = 1;
    TRISC4 = 1;
    SSPBUF = 0x00;
    SSPSTAT = 0xc0;
    SSPCON = 0X28;
    SSPCON2 = 0x00;
    SSPIF = 0;
    SSPADD = 9;   
}

void I2C_start(){
    SEN = 1;
    while (SEN);
}


void I2C_sleep(void){
   while (SSPIF ==0);
   SSPIF = 0;
}


void I2C_rstart(void){
    RSEN = 1;
    while(RSEN);
}

void I2C_NACK(void){
    ACKDT = 1;
    ACKEN =1;
    while(ACKEN);
}
void I2C_stop(void){
    I2C_sleep();
    PEN = 1;
    while(PEN);
}

unsigned char I2C_RX(){
    RCEN = 1;
    while(!BF);
    return SSPBUF;
}


unsigned char I2C_TX(unsigned char c){
    SSPBUF = c;
    while(BF);
    I2C_sleep();
}