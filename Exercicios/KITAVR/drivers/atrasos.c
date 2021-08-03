//*****************************************************************************
//***		ATRASOS.C  														***
//*****************************************************************************

#include "atrasos.h"

/******************************************************************************
NOME:        fnAtraso10us(int tempo)

DESCRIÇÃO:   Fução utilizada para prender a execusão do programa durante um
             determinado "tempo" multiplo de 10us. Essa função é geralmente 
			 utilizada para implementação de atrasos de hardware.

PARAMETROS:  tempo: quantidade de tempo multipla de 10us que a execução
                    do programa permanecerá presa.

RETORNO:     Nulo.
*******************************************************************************/

void	
fnAtraso10us(int tempo)
{
	int	i,j;
	for(i=0;i<tempo;i++)
	{
	 	j++;
  		j++;
  		j++;
  		j++;
  		j++;
	}
}

/******************************************************************************
NOME:        fnAtraso100us(int tempo)

DESCRIÇÃO:   Fução utilizada para prender a execusão do programa durante um
             determinado "tempo" multiplo de 100us.

PARAMETROS:  tempo: quantidade de tempo multipla de 100us que a execução
                    do programa permanecerá presa.

RETORNO:     Nulo.
*******************************************************************************/

void	
fnAtraso100us(int tempo)
{
	int	i,j;
	for(i=0;i<tempo;i++)
	{
		for(j=0;j<61;j++){;}
	}
}

/******************************************************************************
NOME:        fnAtraso1ms(int tempo)

DESCRIÇÃO:   Utilizada a função "atraso_100us" para prender a execusão do programa
             durante um determinado "tempo" multiplo de 1ms.

PARAMETROS:  tempo: quantidade de tempo multipla de 1ms que a execução
                    do programa permanecerá presa.

RETORNO:     Nulo.
*******************************************************************************/

void	
fnAtraso1ms(int tempo)
{
	int t;
	for(t=0; t < tempo; t++)
	{
		fnAtraso100us(tempo);
	}
}

