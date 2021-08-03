//*****************************************************************************
//***		DEFINES.H  														***
//*****************************************************************************

#ifndef		__DEFINES_H_
#define		__DEFINES_H_


#include<avr\io.h>
#include<avr\iom16.h>


/******************************************************************************
 *																			  *	
 *	Definições das teclas do sistema										  * 
 *																			  * 
 ******************************************************************************/

#define		ESQUERDA	5	// DADO  PORTD
#define		CIMA		7   // CLK
#define		BAIXO		6	// STB 
#define		DIREITA		4

#define		SDADO		5
#define		SCLK		7
#define		SSTB		6

#define		H_FREQ		3   // Bits da porta D.
#define		L_FREQ		2

#define		TH_FREQ		(PIND & (1 << PIND3))
#define		T_INICIO	(PINB & (1 << PINB0))


#define 	EEADDR		0x0A


//****************************************************************************
// DEFINIÇÃO DE MACROS QUE UTILIZAM ASM
//****************************************************************************

//
//  As macros abaixo foram criada devido a necessidade de utilização de 
//  instruções que não existem na linguagem C.

//void Teste(unsigned char value)
//{
//	asm volatile("in %0, %1" 
//				: "=r" (value) 
//				: "I" (_SFR_IO_ADDR(PORTD)) 
//	);
//}

#define SET_PB(port,bit) \
		__asm__ __volatile__ ( 	"sbi %0, %1" "\n\t"\
								: /* no outputs */ \
								: "I" (_SFR_IO_ADDR(port)), "I" (bit) \
		)

#define CLR_PB(port,bit) \
		__asm__ __volatile__ (  "cbi %0, %1" "\n\t"\
								: /* no outputs */ \
								: "I" (_SFR_IO_ADDR(port)), "I" (bit) \
		)

#define GASTA1cl() \
		__asm__ __volatile__ (  "nop"\
								::)

#endif





