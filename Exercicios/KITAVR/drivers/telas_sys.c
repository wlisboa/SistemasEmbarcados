//*****************************************************************************
//***		TELAS_SYS.C													    ***
//*****************************************************************************

#include <avr\pgmspace.h>   // Biblioteca respons�vel pelo contrle da mem�ria de programa
#include <avr\eeprom.h>
#include "defines.h"
#include "lcd4b.h" 
#include "usart_w.h"
#include "telas_sys.h"

/**************�REA RESERVADA PARA COMANDOS DO SISTEMA************************/

const char msg0[]	PROGMEM = "menu";
const char msg1[] 	PROGMEM = "";
const char msg2[] 	PROGMEM = "";
const char msg3[] 	PROGMEM = "";
const char msg4[] 	PROGMEM = "";
const char msg5[] 	PROGMEM = "";
const char msg6[] 	PROGMEM = "";
const char msg7[] 	PROGMEM = "";
const char msg8[] 	PROGMEM = "";
const char msg9[] 	PROGMEM = "";
const char msg10[] 	PROGMEM = "";
const char msg11[] 	PROGMEM = "";
const char msg12[] 	PROGMEM = "";
const char msg13[] 	PROGMEM = "";
const char msg14[] 	PROGMEM = "";
const char msg15[] 	PROGMEM = "";
const char msg16[] 	PROGMEM = "";
const char msg17[] 	PROGMEM = "";
const char msg18[] 	PROGMEM = "";
const char msg19[] 	PROGMEM = "";

/**************�REA RESERVADA PARA MENSAGENS DO SISTEMA************************/
//							   01234567890123456789012345678901234567890123456789
const char msg20[] 	PROGMEM = "Teste Keyboard";
const char msg21[] 	PROGMEM = "INVISION";
const char msg22[] 	PROGMEM = "Estado";
const char msg23[] 	PROGMEM = "Principal";
const char msg24[] 	PROGMEM = "Secundario";
const char msg25[] 	PROGMEM = "Programacao";
const char msg26[] 	PROGMEM = "Teclas: ";
const char msg27[] 	PROGMEM = "Led: ";
const char msg28[] 	PROGMEM = "Prox: ";
const char msg29[] 	PROGMEM = "LEITURA DA TECLA";
const char msg30[] 	PROGMEM = "";
const char msg31[] 	PROGMEM = "";

PGM_P array[32] PROGMEM = {     // As mens�gens declaradas nessa estrutura
	msg0,						// s� poder�o ser utilizadas dentro do pr�prio m�dulo	
	msg1,						// a interface para essas mens�gens sera feita atrav�s
	msg2,						// de fun��es.	
	msg3,
	msg4,
	msg5,
	msg6,
	msg7,
	msg8,
	msg9,
	msg10,
	msg11,
	msg12,
	msg13,
	msg14,
	msg15,
	msg16,
	msg17,
	msg18,
	msg19,
	msg20,
	msg21,
	msg22,
	msg23,
	msg24,
	msg25,
	msg26,
	msg27,
	msg28,
	msg29,
	msg30,
	msg31
};								

PGM_P d;

/******************************************************************************
NOME:        fnWrLcd_P(int msg)	

DESCRI��O:   A seguinte fun��o escreve mens�gens contidas na mem�ria de programa
			 isso foi feito para grar economia de mem�ria ram do sistema. 
			 Para o melhor entendimento da implementa��o aqui mostrada verifique o 
			 documento "avr-libc" p�g 192.

PARAMETROS:  msg : N�mero da mens�gem na tabela de mens�gens

RETORNO:     
******************************************************************************/

void
fnWrLcd_P(int msg)
{
	char buf[20];

	memcpy_P(&d, &array[msg], sizeof(PGM_P));
	strcpy_P(buf, d);

	fnWrLcd(buf);
}

/******************************************************************************
NOME:        fnWrUsart_P(int msg)	

DESCRI��O:   A seguinte fun��o escreve mens�gens contidas na mem�ria de programa
			 no canal serial

PARAMETROS:  msg : N�mero da mens�gem na tabela de mens�gens

RETORNO:     
******************************************************************************/

void
fnWrUsart_P(int msg)
{
	char buf[50];

	memcpy_P(&d, &array[msg], sizeof(PGM_P));
	strcpy_P(buf, d);
	
	fnWrUsart(buf);
}

/******************************************************************************
NOME:   	 fnLoadCmd_P(int msg)

DESCRI��O:   Carrega um comando contido na mem�ria de programaa na vari�vel
			 global "srt_sys" que est� armazenada na mem�ria ram

PARAMETROS:  int msg: N�mero do comando que deve ser carregado.

RETORNO:     Nulo.
******************************************************************************/

void
fnLoadCmd_P(int msg)
{
	memcpy_P(&d, &array[msg], sizeof(PGM_P));
	strcpy_P(str_sys, d);
}

/******************************************************************************
NOME:        fnTelaApresentacao()

DESCRI��O:   Desenha uma tela de apresenta��o no display de LCD.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
fnTelaApresentacao(void)
{
	fnClearLcd();
	fnWrLcd_P(20); // "Teste Keyboard";
	fnPosCsr(3,0);
	fnWrLcd_P(21); // "INVISION";
}

/******************************************************************************
NOME:        fnTelaEstadoPrincipal()

DESCRI��O:   

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
fnTelaEstadoPrincipal(void)
{	
	fnClearLcd();
	fnWrLcd_P(20); // "Teste Keyboard";
	fnPosCsr(3,0);
	fnWrLcd_P(21); // "INVISION";
}

/******************************************************************************
NOME:        fnTelaEstadoA()

DESCRI��O:   

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
fnTelaProgramacao(void)
{	
	fnClearLcd();
	fnWrLcd_P(25); // Programacao	

	fnPosCsr(1,0);
	fnWrLcd_P(26); // Teclas: <-

	printf("%d",num_teclas);

	fnPosCsr(2,0);
	fnWrLcd_P(27); // Led:

	if(cor_led == 1)
	{
		printf("Vermelho");
	}

	if(cor_led == 2)
	{
		printf("Verde");		
	}

	if(cor_led == 3)
	{
		printf("Ambar");		
	}

	if(cor_led == 4)
	{
		printf("Azul");		
	}

	fnPosCsr(3,0);
	fnWrLcd_P(28); // Prox:

	
	fnPosCsr(pos_menu,14);

	if(seta_flag == 1)
	{
		fnDataLcd(SETA_CIMA);      //  
		fnDataLcd(SETA_BAIXO);     //
	}
	else
	{
		fnDataLcd(SETA_ESQUERDA);
	}
}

/******************************************************************************
NOME:        fnTelaLeituraTecla(void)

DESCRI��O:   

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
fnTelaLeituraTecla(void)
{
	int   buffer;
	float valor_lido;
	

	fnClearLcd();
	fnWrLcd_P(29); // LEITURA DA TECLA
	
	fnPosCsr(1,0);
	printf("Tecla: %d", tecla_leitura);
	
	fnPosCsr(2,0);
	
	buffer = eeprom_read_word(tecla_leitura * 2);

	valor_lido =  buffer;
	valor_lido = valor_lido / 100;
	printf("Valor: %.2f",valor_lido);

	fnPosCsr(3,0);
	printf("Sair");
	
	
	fnPosCsr(pos_menu_D,14);
	
	if(seta_flag == 1)
	{
		fnDataLcd(SETA_CIMA);      //  
		fnDataLcd(SETA_BAIXO);     //
	}
	else
	{
		fnDataLcd(SETA_ESQUERDA);
	}

}

/******************************************************************************
NOME:        fnAquisicaoTensao(void)

DESCRI��O:   

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/
void
fnTelaAquisicaoTensao(void)
{
	float valor_lido;	
	fnPosCsr(2,8);
	valor_lido =  tensao_lida;
	valor_lido = valor_lido / 100;
	printf("%.2f",valor_lido);
	fnAtraso1ms(30);
}

//*****************TELAS UTILIZADAS NO MONITOR SERIAL**************************

/******************************************************************************
NOME:        fnTelaMonitorPrincipal()

DESCRI��O:   Desenha uma tela inicial no monitor serial. Essa tela cont�m as 
			 informa��es de vers�o e de apresenta��o do sistema.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
fnTelaMonitorPrincipal(void)
{
	fnWrUsart_P(20);		// KIT AVR
	fnUsartPutC('\n');
	fnUsartPutC('\r');
	fnWrUsart_P(21);		// By: Washington
	fnUsartPutC('\n');
	fnUsartPutC('\n');
	fnUsartPutC('\r');
	fnWrUsart_P(25);		// Por vafor digite sua senha + ENTER para come�ar
	fnUsartPutC('\n');
	fnUsartPutC('\r');
	fnWrUsart_P(20);		// KIT AVR>
	fnUsartPutC('>');
}

/******************************************************************************
NOME:        

DESCRI��O:

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
fnTelaErroComando(void)
{
	fnUsartPutC('\n');
	fnUsartPutC('\r');
	fnWrUsart_P(28);		// Comando n�o encontrado
	
	fnWrUsart("Erro");
}


/******************************************************************************
NOME:        fnTelaLinhaComando(void)

DESCRI��O:	 Desenha a linha de comando do monitor serial	

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
fnTelaLinhaComando(void)
{
	fnUsartPutC('\n');
	fnUsartPutC('\r');
	fnWrUsart_P(20);		// KIT AVR>
	fnUsartPutC('>');
}






