//*****************************************************************************
//***		DRIVEADC.C														***
//*****************************************************************************

#include "defines.h"
#include "driveadc.h"

#include "lcd4b.h"


/*****************************************************************************
NOME:			void	fnInitAdc()

DESCRI��O:		Inializa os registradores do conversor anal�gico- digital.

PARAMETROS:		Nulo

RETORNO:		Nulo.
******************************************************************************/

void
fnInitAdc(void)
{
	/**************CONTROLE DO ADC************************/
	ADMUX  =0b01000000;
	ADCSRA =0b10000000;
	SFIOR  =0b00000000;
	/*****************************************************/
}

/***************************************************************************
NOME:        fnLerAdc(unsigned char canal)

DESCRI��O:	 Nulo

PARAMETROS:  Nulo

RETORNO:     Nulo.
****************************************************************************/

int
fnLerAdc(void)
{  
	int Vlow, Vhi;
	float tensao;
	
	ADCSRA |=_BV(ADSC);         //Seta o flag para iniciar a convers�o.
	
	do{
	}while(ADCSRA & _BV(ADSC)); //Prende a execuss�o do programa at� que a leitura esteja terminada

	Vlow = ADCL;
 	Vhi  = ADCH;
 	Vhi  = Vhi<<8;
 	tensao = Vhi | Vlow;

 	tensao = (tensao * PRECISAO);
	return tensao;
}


/***************************************************************************
NOME:        fnLerTensao(void)

DESCRI��O:	 -

PARAMETROS:  -

RETORNO:     Nulo.
****************************************************************************/

void
fnLerTensao(void)
{
	int i;
	int media;

	media = fnLerAdc();

	media = 0;
	for(i = 0;i < 10; i++)
	{	
		media = media + fnLerAdc();
	}
	
	tensao_lida = media;
	tensao_lida = media / 10;
}
