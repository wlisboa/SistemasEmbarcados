//*****************************************************************************
//***		EX_INTERRUPT.C	   												***
//*****************************************************************************

#include "defines.h"
#include "ex_interrupt.h"

//*****************************************************************************
//***	INICIALIZAÇÃO E CONTROLE DAS INTERRUPÇÕES EXTERNAS					***
//*****************************************************************************


/******************************************************************************
NOME:        void fnInitExtInterrupt(void)

DESCRIÇÃO:   Faz a inicialização da função de interrupção externa.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
*******************************************************************************/
void
fnInitExtInterrupt(void)
{
	SREG = 0x80;
	MCUCR = _BV(ISC01)| _BV(ISC11);
}

/***************************************************************************
NOME: 		void  fnInt0_Ctr(int ctr)

DESCRIÇÃO:  Controla a atuação da interrupção externa int0, de acordo com o
            parametro ctr. Quando ctr é levado para 0 a interrupção é desabilitada.     

PARAMETROS: ctr - Vairável de controle: 0 - desabilita a interrupção externa. 
                                        1 - Habilita a interrupção externa.									   

RETORNO:    Nulo.
****************************************************************************/

void 
fnInt0_Ctr(int ctr)
{
	if(ctr)
	{
		GIFR |=_BV(INTF0);			// LIMPA A BANEIRA DE ITERRUPÇÃO
		GICR |=_BV(INT0);  			// INICIALIZA A INTERRUPÇÃO 
	}
	else
	{
		GICR &= ~_BV(INT0);  		// PARA A INTERRUPÇÃO 
		GIFR |=_BV(INTF0);			// LIMPA A BANEIRA DE ITERRUPÇÃO
	}
}

