//*****************************************************************************
//***		MONITOR_SER.C													***
//*****************************************************************************

#include <string.h>
#include "defines.h"
#include "usart_w.h"
#include "telas_sys.h"
#include "monitor_ser.h"

#define QUANT_COMANDOS	1		// Indica a quantidade de comandos na tabela


/******************************************************************************
NOME:        fnDecodificaComando(void)

DESCRIÇÃO:   Busca o comando digitado no console na tabela de comandos e retorna
			 o seu número na tabela caso o comando seja encontrado. Caso o comando
			 não seja encontrado a função retorna uma menságem de erro no console
			 e pede para que o comando seja digitado novamente.

PARAMETROS:  Nulo.

RETORNO:     Caso encontrado retornao número do comando na tabela.
			 -1 caso o comando não seja encontrado.	
******************************************************************************/

unsigned char
fnBuscaComando(void)
{
	unsigned char result_cmp, i;

	for(i = 0 ; i < QUANT_COMANDOS; i++)
	{
		fnLoadCmd_P(i);
		result_cmp = strcmp(str_cmd,str_sys);
		if (result_cmp == 0)
		{
			return i;
		}
	}
	return -1;
}

/******************************************************************************
NOME:       fnConsole(void)  

DESCRIÇÃO:  Emula uma janela de comandos (Console) através da porta serial. Os 
		    comados estão armazenados em uma tabela na memória de código, o console 
		    fica responsavel por armazenar o que foi digitado em um buffer na memória 
		    Ram "str_cmd" e ao precionar ENTER no terminal serial então o comando
			será decodificado e então um valor será retornado.
			Caso o comando não seja encontrado na tabela é retornada uma tela de erro.
			a função so retorna quando um comando é encontrado.

PARAMETROS:	Nulo.

RETORNO:	Nulo.
******************************************************************************/

unsigned char
fnConsole(void)
{
	unsigned char dadoLido, i, result;

	i = 0; 							// Aponta para o inicio da string de comando.
	while(1)						// Fica preso enquanto o comando é digitado
	{
		dadoLido = fnUsartGetC();
		str_cmd[i] = dadoLido;      // Preenche a string que guarda o comando

		if (dadoLido == '\r')
		{
			if (i == 0)				// Foi precionado ENTER sem comando
			{
				fnTelaLinhaComando();
			}
			else
			{
				i = 0;
				result = fnBuscaComando();
				if (result == -1)
				{
					fnTelaErroComando();
				}
				else
				{
					return result;
				}
			}			
		}
		else
		{
			fnUsartPutC(dadoLido);		
			if (i < 10)
				i++;
		}		
	}
	
}
