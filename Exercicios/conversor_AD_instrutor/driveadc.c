//*****************************************************************************
//***		DRIVEADC.C														***
//*****************************************************************************

#include "driveadc.h"
#include "usart_w.h"


/*****************************************************************************
NOME:			void	fnInitAdc()

DESCRICAO:		Inializa os registradores do conversor anal�gico- digital.

PARAMETROS:		Nulo

RETORNO:		Nulo.
******************************************************************************/

void
fnInitAdc(void)
{
	/**************CONTROLE DO ADC************************/
	ADMUX  =0b01000000;
	ADCSRA =0b10000010 ;
	/*****************************************************/
}

/***************************************************************************
NOME:        fnLerAdc(unsigned char canal)

DESCRICAO:	 Nulo

PARAMETROS:  Nulo

RETORNO:     Nulo.
****************************************************************************/

int
fnLerAdc(void)
{  
	int Vlow, Vhi;
	float tensao;
	
	ADCL = 0;
	ADCH = 0;

	ADCSRA |=_BV(ADSC);         //Seta o flag para iniciar a convers�o.
	
	
	fnWrUsart("\n\rDEPURACAO\n\r");
	fnWrUsart("ADCSRA: ");
	fnWrHex(ADCSRA);
	fnWrUsart("\n\r");

	
	while(ADCSRA & _BV(ADSC)){
		;//Prende a execuss�o do programa at� que a leitura esteja terminada
	} 

	Vlow = ADCL;
 	Vhi  = ADCH;
	fnWrUsart("\n\rDEPURACAO\n\r");
	fnWrUsart("Vlow: ");
	fnWrHex(Vlow );
	fnWrUsart("\n\r");

	fnWrUsart("Vhi: ");
	fnWrHex(Vhi);
	fnWrUsart("\n\r");

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

int
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
	
	return (media/10);
}
