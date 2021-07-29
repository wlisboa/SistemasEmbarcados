//*****************************************************************************
//***		USART_W.H  														***
//*****************************************************************************

#ifndef		__USART_W_H_
#define		__USART_W_H_

#include <avr\io.h>

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD - 1

void
fnInitUsart(unsigned int ubrr);

void
fnUsartPutC(unsigned char c);

unsigned char
fnUsartGetC(void);

void
fnWrUsart(unsigned char *c);

#endif
