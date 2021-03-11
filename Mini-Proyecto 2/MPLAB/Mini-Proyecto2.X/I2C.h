/*//////////////////////////////////////////////////////////////////////////////
 * File:   USART.H
 * Author: DARIO MARROQUIN
 */


#ifndef __I2C_H
#define	__I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void I2C_init(void);
void I2C_start(void);
void I2C_sleep(void);
void I2C_rstart(void);
void I2C_NACK(void);
void I2C_stop(void);
unsigned char I2C_RX(void);
unsigned char I2C_TX(unsigned char c);

#endif	/* USART_H */

