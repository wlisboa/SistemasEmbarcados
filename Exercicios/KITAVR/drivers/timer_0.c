//*****************************************************************************
//***		TIMER_0.C  														***
//*****************************************************************************


//**************************************************************************** 
//
// M�dulo respons�vel pela configura��o e controle do TIMER_COUNTER_0
//
//****************************************************************************


#include "defines.h"
#include "timer_0.h"


/*****************************************************************************
NOME:		void fnInitTimer0()

DESCRI��O:	A seguinte fun��o � respons�vel pela inicializa��o do TIMER_COUNTER_0.
            Esse timer ser� utilizado como temporiza��o principal do sistema, 
			por isso deve ser configurado para estourar a cada 50us e gerar uma
			interrup��o.
			Para gerar tal temporiza��o configurou-se o timer para o modo CTC.

			Temporiza��o:

			Contagem = Fclock/8

			Comparador = 15

			Frequencia de 100Khz e tempo de 10us



			TCCR0				
			+----------------------------------------------------------+	
			|FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 |
			+----------------------------------------------------------+

					
			TIMSK	
			+----------------------------------------------------------+	
			|OCIE2| TOIE2 | TICIE1| OCIEIA| OCIE1B| TOIE1| OCIE0| TOIE0|
			+----------------------------------------------------------+
				
PARAMETROS:		

RETORNO:		
******************************************************************************/

void
fnInitTimer0(void)
{
	TCCR0  = _BV(CS01) | _BV(WGM01); 
	OCR0   = 75;
	TIMSK  = _BV(OCIE0);
	TCNT0  = 0x00;
}

/*****************************************************************************
NOME:

DESCRI��O:	
				
PARAMETROS:		

RETORNO:		
******************************************************************************/

void
fnStarTimer0(void)
{
}

/*****************************************************************************
NOME:

DESCRI��O:	
				
PARAMETROS:		

RETORNO:		
******************************************************************************/

void
fnStopTimer0(void)
{
}






