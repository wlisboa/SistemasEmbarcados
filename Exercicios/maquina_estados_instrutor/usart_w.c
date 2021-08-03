//*****************************************************************************
//***		USART.H  														***
//*****************************************************************************

#include "usart_w.h"
#include <stdio.h>

/******************************************************************************
NOME:        fnUsartInit()

DESCRICAO:   Inicializa o canal de comunicacao serial

PARAMETROS:  Nulo

RETORNO:     Nulo.
*******************************************************************************/

void fnInitUsart(unsigned int ubrr)
{
	// Configura a Taxa de comunicacao
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	// Habilita a transmiss�o e recep��o da serial
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Configura formato da palavr0a
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

/******************************************************************************
NOME:        fnUsartPutC(unsigned char c)

DESCRICAO:   Envia um caracter via interface serial.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/

void fnUsartPutC(unsigned char c)
{
	// Verifica se j� terminou uma transmiss�o.
	while (!(UCSR0A & (1 << UDRE0)))
		;
	// Coloca o caracater no buffer de envio
	UDR0 = c;
}

/******************************************************************************
NOME:        fnUsartPutC(unsigned char c)

DESCRICAO:   Recebe um caracter via porta serial. Essa funcao trava o programa
			 at� que chegue determinado caracter

PARAMETROS:  Nulo.

RETORNO:     Retorna o caracter recebido via serial.
*******************************************************************************/

unsigned char
fnUsartGetC(void)
{
	unsigned char dado;
	while (!(UCSR0A & (1 << RXC0)))
		;
	dado = UDR0;
	return dado;
}

/******************************************************************************
NOME:        fnWrUsart(unsigned char *c)

DESCRICAO:   Envia uma string via interface serial.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/
void fnWrUsart(char *c)
{
	for (; *c != '\0'; *c++)
	{
		fnUsartPutC(*c);
	}
}

/******************************************************************************
NOME:        

DESCRICAO:   

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/
void fnWrInt(int valor)
{
	char myString[20];
	sprintf(myString, "%d", valor);
	fnWrUsart(myString);
}

/******************************************************************************
NOME:        

DESCRICAO:   

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/
void fnWrHex(uint8_t valor)
{
	char myString[20];
	sprintf(myString, "0x%x", valor);
	fnWrUsart(myString);
}