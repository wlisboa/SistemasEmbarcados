//*****************************************************************************
//***		USART.H  														***
//*****************************************************************************

#include "defines.h"
#include "usart_w.h"

/******************************************************************************
NOME:        fnUsartInit()

DESCRIÇÃO:   Inicializa o canal de comunicação serial

PARAMETROS:  Nulo

RETORNO:     Nulo.
*******************************************************************************/

void
fnInitUsart(unsigned int ubrr)
{
	// Configura a Taxa de comunicação
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char) ubrr;

	// Habilita a transmissão e recepção da serial
	UCSRB = (1<<RXEN) | (1<<TXEN);

	// Configura formato da palavra
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
}


/******************************************************************************
NOME:        fnUsartPutC(unsigned char c)

DESCRIÇÃO:   Envia um caracter via interface serial.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/

void
fnUsartPutC(unsigned char c)
{
	// Verifica se já terminou uma transmissão.
	while(!(UCSRA & (1<<UDRE)));
	// Coloca o caracater no buffer de envio
	UDR = c;
}

/******************************************************************************
NOME:        fnUsartPutC(unsigned char c)

DESCRIÇÃO:   Recebe um caracter via porta serial. Essa função trava o programa
			 até que chegue determinado caracter

PARAMETROS:  Nulo.

RETORNO:     Retorna o caracter recebido via serial.
*******************************************************************************/

unsigned char
fnUsartGetC(void)
{
	unsigned char dado;
	while(!(UCSRA & (1<<RXC)));
	dado = UDR;
	return dado;
}


/******************************************************************************
NOME:        fnWrUsart(unsigned char *c)

DESCRIÇÃO:   Envia uma string via interface serial.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/

void
fnWrUsart(unsigned char *c)
{
	for(;*c != '\0';*c++)
	{
		fnUsartPutC(*c);
	}
}



