//*****************************************************************************
//***		LCD4B.C	   														***
//*****************************************************************************

#include"lcd4b.h"
#include"defines.h"
#include"atrasos.h"

/*****************************************************************************
NOME:			void	nible_lcd()

DESCRIÇÃO:		Envia o nible mais significativo do dado para o display de LCD.

PARAMETROS:		dado - Dado a ser enviado.

RETORNO:		Nulo.
******************************************************************************/

void
nible_lcd(unsigned char dado)
{
	unsigned char	aux;
	dado	= dado & 0xF0;
	aux		= LCD_PORT;
	aux		= aux & 0x0F;
	dado	= dado | aux;
	LCD_PORT= dado;
	
	fnAtraso10us(1); 			
	LCD_PORT |= _BV(LCD_ENB);   //Seta o bit
	fnAtraso10us(1); 			
	LCD_PORT &= ~_BV(LCD_ENB);  //Zera o bit
	fnAtraso10us(1);
}

/*****************************************************************************
NOME:			void	cmd_lcd(unsigned char dado)

DESCRIÇÃO:		Envia comandos para o display.

PARAMETROS:		dado - dado a ser enviado para o display. 

RETORNO:		Nulo.
******************************************************************************/

void
cmd_lcd(unsigned char dado)
{
	LCD_PORT &= ~_BV(LCD_RS);   // Zera o bit 		
	nible_lcd(dado);
	dado = dado << 4;
	nible_lcd(dado);
	fnAtraso1ms(5);
}

/*****************************************************************************
NOME:			void	data_lcd(unsigned char dado)

DESCRIÇÃO:		Envia dados para o display.

PARAMETROS:		dado - dado a ser enviado para o display. 

RETORNO:		Nulo.
******************************************************************************/

void
data_lcd(unsigned char dado)
{
	LCD_PORT |= _BV(LCD_RS);   // Seta o bit
	nible_lcd(dado);
	dado = dado << 4;
	nible_lcd(dado);
}


/*****************************************************************************
NOME:			void	init_lcd()

DESCRIÇÃO:		Inicializa o display de LCD.

PARAMETROS:		Nulo

RETORNO:		Nulo
******************************************************************************/

void
init_lcd(void)
{
	LCD_DDR = LCD_MASC;  					// Habilita os pinos do micro para escrita.
	fnAtraso1ms(20);
	cmd_lcd(0x20);
	cmd_lcd(0x20);
	fnAtraso1ms(15);
	cmd_lcd(0x28);
	cmd_lcd(0x0C);
	cmd_lcd(0x01);
}

/*****************************************************************************
NOME:			void	wr_lcd(char *s)

DESCRIÇÃO:		Escreve uma string de caracteres no display de LCD.

PARAMETROS:		Nulo

RETORNO:		Nulo
******************************************************************************/

void 
wr_lcd(char *s)
{
	for(;*s != '\0';*s++)
	{
		data_lcd(*s);
	}
}

/******************************************************************************
NOME:        int_asc(int num)

DESCRIÇÃO:   Transforma um inteiro para ascII e preenche a variavel indicada no 
             ponteiro "buff" da seguinte forma: xxxxx. Os valores numericos
             devem ser comvertidos antes de serem escritos no display.

PARAMETROS:  num: Valor inteiro a ser convertido.
             buff: ponteiro que indica o destino resultado. 

RETORNO:     nulo.
*******************************************************************************/

void 
int_asc(long int num, char *buff)
{
	long int div;
	for(div=1000000;div > 0;div=(div/10))
	{
		*buff++ = (0x30|(num/div));
		num = num%div;
	}
	*buff='\0';
}

/*****************************************************************************
NOME:			void print_int(int dado)

DESCRIÇÃO:		Escreve um número inteiro no display.

PARAMETROS:		Nulo

RETORNO:		Nulo
******************************************************************************/

void 
print_int(long int dado)
{
	char buffer[8];
	int_asc(dado, buffer);
	wr_lcd(buffer);
}

/********************************************************************
NOME:        pos_csr(unsigned char lin,unsigned char col)

DESCRIÇÃO:   Posiciona o cusrsor em qualquer posição do display de acordo
             com os parametros "lin" e "col". O posicionamento é feito a
             partir da posição 0x0 e vai até a posição 1x23.

PARAMETROS:  lin: 0-linha superior. 1-linha inferior.
             col: 0 a 23 posições de coluna do display

RETORNO:     Nulo
********************************************************************/

void
pos_csr(unsigned char lin,unsigned char col)
{
	switch(lin)
	{
		case 0:
			cmd_lcd(0x80+col);
		break;

		case 1:
			cmd_lcd(0xc0+col);
		break;

		case 2:
			cmd_lcd(0x90+col);
		break;

		case 3:
			cmd_lcd(0xD0+col);
		break;
	}
}

/********************************************************************
NOME:        void clear_lcd()

DESCRIÇÃO:   Limpa o display e posiciona o corsor na posição 0x0.

PARAMETROS:  Nulo

RETORNO:     Nulo
********************************************************************/

void
clear_lcd(void)
{
	cmd_lcd(1);
}

