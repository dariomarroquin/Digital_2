/*//////////////////////////////////////////////////////////////////////////////
 * File:   USART.H
 * Author: DARIO MARROQUIN
 */


#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void USART_Initialize(const long int baudrate);

#endif	/* USART_H */

