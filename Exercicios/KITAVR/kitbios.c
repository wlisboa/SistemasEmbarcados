//******************************************************************************
//***		KITBIOS.C													 	 ***
//******************************************************************************

/******************************************************************************

VERS�O: 0.0
DOC REV 0 - 11.09.07
DOC REV 1 - 04.06.08
DOC REV 2 - 28.08.09

Autor: Washington Pinto Lisboa
email: w_lisboa@click21.com.br

*******************************************************************************/

/**************INICIALIZA��O DAS BIBLIOTECAS***********************************/

#include<avr\io.h>
#include<avr\iom16.h>
#include<avr\interrupt.h>

#include "defines.h" 		// Iclus�o das defini��es globais do sistema
#include "atrasos.h"
#include "ex_interrupt.h" 
#include "timer_0.h" 
#include "lcd4b.h"
#include "telas_sys.h"


/******************************************************************************/

/**************ROTINAS DE INTERRUP��O DO SISTEMA*******************************/

/******************************************************************************
NOME:        ISR (INT0_vect)

DESCRI��O:   A seguinte fun��o � chamada quando ocorre uma uma borada de 
             descida no pino INT0, nesse firware � utilizada para decodificar 
			 as informa��es provenintes do controle remoto.

PARAMETROS:  Nulo. 

RETORNO:     Nulo. 
******************************************************************************/

ISR (INT0_vect)
{

}

/******************************************************************************
NOME:        ISR (TIMER0_COMP_vect)

DESCRI��O:   E a temporiza��o principal do sistema que pode ser utilizada
             para uso geral.

			 Temporiza��o 10us.


PARAMETROS:  Nulo

RETORNO:     Nulo
******************************************************************************/

ISR (TIMER0_COMP_vect)
{
	inTicSistema++;
}


/******************************************************************************
NOME:       main() 
DESCRI��O:  Esse � o m�todo principal, � o passo inicial da execu��o do programa.
			O programa ser� dividido da seguinte forma: O metodo main() iniciar� 
			sua execu��o configurando todo o hardware que ser� utilizado no
			programa. Logo depois come�ar� a execu��o da fun��o desejada.
			A inicializa��o ocorrer� da seguinte forma:


			Inicia��o das porta:

				O software configura o registro de modos da porta assim como 
				a dire��o na qual a porta estar� inicializada.


			Configura��o do hardware:
				
				Nessa etapa o software far� a configura��o dos registros de controle 
				do hardware. Nessa primeira etapa criaremos os m�dulos de drivers que 
				ser�o utilizados como ferramentas para outro tipo de tarefa.


			Execu��o do programa:

				O programa principal faz uso dos drivers realizar algum tipo de 
				tarefa desejada.

			Configura��o da Sess�o de BootLoader

 			Boot Lock Bit0 (Application Section)			
			BLB02	BLB01	
			1		1		-	Sem restri��es para escrita ou litura na Sess�o
								de aplica��o
								

			Boot Lock Bit1 (Boot Lodade Section)
			BLB12	BLB11
			1		0		-	N�o permite a escrita na sess�o de Boot Loader.	

			
			Table 100 - Configura o tamanho da sess�o de Boot Loader
			BOOTSZ1 BOOTSZ0
			0		0		-	Configura a Se��o para o maior tamanho.


PARAMETROS:  
RETORNO:     
******************************************************************************/

int 
main()
{			

	fnInitExtInterrupt();
	fnInitTimer0();
	fnInitLcd();


	//fnTelaApresentacao();
	fnTelaProgramacao();

	for(;;);

	return 0;
}

