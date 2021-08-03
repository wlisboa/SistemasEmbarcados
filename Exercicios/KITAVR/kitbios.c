//******************************************************************************
//***		KITBIOS.C													 	 ***
//******************************************************************************

/******************************************************************************

VERSÃO: 0.0
DOC REV 0 - 11.09.07
DOC REV 1 - 04.06.08
DOC REV 2 - 28.08.09

Autor: Washington Pinto Lisboa
email: w_lisboa@click21.com.br

*******************************************************************************/

/**************INICIALIZAÇÃO DAS BIBLIOTECAS***********************************/

#include<avr\io.h>
#include<avr\iom16.h>
#include<avr\interrupt.h>

#include "defines.h" 		// Iclusão das definições globais do sistema
#include "atrasos.h"
#include "ex_interrupt.h" 
#include "timer_0.h" 
#include "lcd4b.h"
#include "telas_sys.h"


/******************************************************************************/

/**************ROTINAS DE INTERRUPÇÃO DO SISTEMA*******************************/

/******************************************************************************
NOME:        ISR (INT0_vect)

DESCRIÇÃO:   A seguinte função é chamada quando ocorre uma uma borada de 
             descida no pino INT0, nesse firware é utilizada para decodificar 
			 as informações provenintes do controle remoto.

PARAMETROS:  Nulo. 

RETORNO:     Nulo. 
******************************************************************************/

ISR (INT0_vect)
{

}

/******************************************************************************
NOME:        ISR (TIMER0_COMP_vect)

DESCRIÇÃO:   E a temporização principal do sistema que pode ser utilizada
             para uso geral.

			 Temporização 10us.


PARAMETROS:  Nulo

RETORNO:     Nulo
******************************************************************************/

ISR (TIMER0_COMP_vect)
{
	inTicSistema++;
}


/******************************************************************************
NOME:       main() 
DESCRIÇÃO:  Esse é o método principal, é o passo inicial da execução do programa.
			O programa será dividido da seguinte forma: O metodo main() iniciará 
			sua execução configurando todo o hardware que será utilizado no
			programa. Logo depois começará a execução da função desejada.
			A inicialização ocorrerá da seguinte forma:


			Iniciação das porta:

				O software configura o registro de modos da porta assim como 
				a direção na qual a porta estará inicializada.


			Configuração do hardware:
				
				Nessa etapa o software fará a configuração dos registros de controle 
				do hardware. Nessa primeira etapa criaremos os módulos de drivers que 
				serão utilizados como ferramentas para outro tipo de tarefa.


			Execução do programa:

				O programa principal faz uso dos drivers realizar algum tipo de 
				tarefa desejada.

			Configuração da Sessão de BootLoader

 			Boot Lock Bit0 (Application Section)			
			BLB02	BLB01	
			1		1		-	Sem restrições para escrita ou litura na Sessão
								de aplicação
								

			Boot Lock Bit1 (Boot Lodade Section)
			BLB12	BLB11
			1		0		-	Não permite a escrita na sessão de Boot Loader.	

			
			Table 100 - Configura o tamanho da sessão de Boot Loader
			BOOTSZ1 BOOTSZ0
			0		0		-	Configura a Seção para o maior tamanho.


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

