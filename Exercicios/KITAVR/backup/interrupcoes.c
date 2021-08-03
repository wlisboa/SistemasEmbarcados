//*****************************************************************************
//***		INTERRUPCOES.C	   												***
//*****************************************************************************

#include "defines.h"
#include "interrupcoes.h"

//*****************************************************************************
//***	INICIALIZA��O E CONTROLE DA INTERRUP��O EXTERNA 0					***
//*****************************************************************************

/******************************************************************************
NOME:        void fnInitExtInterrupt(void)

DESCRI��O:   Faz a inicializa��o da fun��o de interrup��o externa.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/
void
fnInitExtInterrupt(void)
{
	SREG  = 0x80;
	MCUCR = _BV(ISC01)| _BV(ISC11);
}

/***************************************************************************
NOME: 		void  fnInt0_Ctr(int ctr)

DESCRI��O:  Controla a atua��o da interrup��o externa int0, de acordo com o
            parametro ctr. Quando ctr � levado para 0 a interrup��o � desabilitada.     

PARAMETROS: ctr - Vair�vel de controle: 0 - desabilita a interrup��o externa. 
                                        1 - Habilita a interrup��o externa.									   

RETORNO:    Nulo.
****************************************************************************/

void 
fnInt0_Ctr(int ctr)
{
	if(ctr)
	{
		GIFR |=_BV(INTF0);			// LIMPA A BANEIRA DE ITERRUP��O
		GICR |=_BV(INT0);  			// INICIALIZA A INTERRUP��O 
	}
	else
	{
		GICR &= ~_BV(INT0);  		// PARA A INTERRUP��O 
		GIFR |=_BV(INTF0);			// LIMPA A BANEIRA DE ITERRUP��O
	}
}


/***************************************************************************
NOME:
DESCRI��O: Fun��o relacionada com a interrup��o do timer0. A seguinte fun��o
		   � uma fun��o de interrup��o, portanto, sua declara��o tera que 
		   utilizar uma macro que faz a declara��o da fun��o que ser� 
		   montada na �rea respons�vel pela interrup��o do chip
PARAMETROS:
RETORNO:   
****************************************************************************/





