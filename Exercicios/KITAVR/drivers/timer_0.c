//*****************************************************************************
//***		TIMER_0.C  														***
//*****************************************************************************


//**************************************************************************** 
//
// Módulo responsável pela configuração e controle do TIMER_COUNTER_0
//
//****************************************************************************


#include "defines.h"
#include "timer_0.h"


/*****************************************************************************
NOME:		void fnInitTimer0()

DESCRIÇÃO:	A seguinte função é responsável pela inicialização do TIMER_COUNTER_0.
            Esse timer será utilizado como temporização principal do sistema, 
			por isso deve ser configurado para estourar a cada 50us e gerar uma
			interrupção.
			Para gerar tal temporização configurou-se o timer para o modo CTC.

			Temporização:

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

DESCRIÇÃO:	
				
PARAMETROS:		

RETORNO:		
******************************************************************************/

void
fnStarTimer0(void)
{
}

/*****************************************************************************
NOME:

DESCRIÇÃO:	
				
PARAMETROS:		

RETORNO:		
******************************************************************************/

void
fnStopTimer0(void)
{
}






