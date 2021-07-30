//*****************************************************************************
//***		DRIVEADC.C														***
//*****************************************************************************

#include "defines.h"
#include "driveadc.h"

#include "lcd4b.h"


/*****************************************************************************
NOME:			void	fnInitAdc()

DESCRIÇÃO:		Inializa os registradores do conversor analógico- digital.

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

DESCRIÇÃO:	 Nulo

PARAMETROS:  Nulo

RETORNO:     Nulo.
****************************************************************************/

int
fnLerAdc(void)
{  
	int Vlow, Vhi;
	float tensao;
	
	ADCSRA |=_BV(ADSC);         //Seta o flag para iniciar a conversão.
	
	do{
	}while(ADCSRA & _BV(ADSC)); //Prende a execussão do programa até que a leitura esteja terminada

	Vlow = ADCL;
 	Vhi  = ADCH;
 	Vhi  = Vhi<<8;
 	tensao = Vhi | Vlow;

 	tensao = (tensao * PRECISAO);
	return tensao;
}


/***************************************************************************
NOME:        fnLerTensao(void)

DESCRIÇÃO:	 -

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
