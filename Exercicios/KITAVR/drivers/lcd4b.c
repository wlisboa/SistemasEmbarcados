//*****************************************************************************
//***		LCD4B.C	   														***
//*****************************************************************************

#include"lcd4b.h"
#include"defines.h"
#include"atrasos.h"

/*****************************************************************************
NOME:			void	fnNibleLcd()

DESCRIÇÃO:		Envia o nible mais significativo do dado para o display de LCD.

PARAMETROS:		dado - Dado a ser enviado.

RETORNO:		Nulo.
******************************************************************************/

void
fnNibleLcd(unsigned char dado)
{
	unsigned char	aux;
	dado	= dado & 0xF0;
	aux		= LCD_PORT;
	aux		= aux & 0x0F;
	dado	= dado | aux;
	
	LCD_PORT= dado;
	LCD_PORT |= _BV(LCD_ENB);   //Seta o bit
	fnAtraso10us(1); 			
	LCD_PORT &= ~_BV(LCD_ENB);  //Zera o bit
	fnAtraso10us(1);
}

/*****************************************************************************
NOME:			void	fnCmdLcd(unsigned char dado)

DESCRIÇÃO:		Envia comandos para o display.

PARAMETROS:		dado - dado a ser enviado para o display. 

RETORNO:		Nulo.
******************************************************************************/

void
fnCmdLcd(unsigned char dado)
{
	LCD_PORT &= ~_BV(LCD_RS);   // Zera o bit 		
	fnNibleLcd(dado);
	dado = dado << 4;
	fnNibleLcd(dado);
	fnAtraso1ms(5);
}

/*****************************************************************************
NOME:			void	data_lcd(unsigned char dado)

DESCRIÇÃO:		Envia dados para o display.

PARAMETROS:		dado - dado a ser enviado para o display. 

RETORNO:		Nulo.
******************************************************************************/

void
fnDataLcd(unsigned char dado)
{
	LCD_PORT |= _BV(LCD_RS);   // Seta o bit
	fnNibleLcd(dado);
	dado = dado << 4;
	fnNibleLcd(dado);
	fnAtraso10us(5);
}


/*****************************************************************************
NOME:			void	init_lcd()

DESCRIÇÃO:		Inicializa o display de LCD.

PARAMETROS:		Nulo

RETORNO:		Nulo
******************************************************************************/

void
fnInitLcd(void)
{
	LCD_DDR = LCD_MASC;  					// Habilita os pinos do micro para escrita.
	fnAtraso1ms(20);
	fnCmdLcd(0x20);
	fnCmdLcd(0x20);
	fnAtraso1ms(15);
	fnCmdLcd(0x28);
	fnCmdLcd(0x0C);
	
	fnCmdLcd(LCD_CLR);

	// Aponta a o primeiro caractere da CGRAM
	fnCmdLcd (LCD_CGADDR (0x40));

	/*
	 * Desenha uma seta para baixo na CGRAM
	 *
	 * 00100
	 * 00100
	 * 00100
	 * 00100
	 * 10101
	 * 01010
	 * 00100
	 * 00000
	 */

	fnDataLcd (0x04);
	fnDataLcd (0x04);
	fnDataLcd (0x04);
	fnDataLcd (0x04);
	fnDataLcd (0x15);
	fnDataLcd (0x0A);
	fnDataLcd (0x04);
	fnDataLcd (0x00);

		/*
	 * Desenha uma seta para cima
	 *
	 * 00100
	 * 01010
	 * 10101
	 * 00100
	 * 00100
	 * 00100
	 * 00100
	 * 00000
	 */

	fnDataLcd (0x04);
	fnDataLcd (0x0A);
	fnDataLcd (0x15);
	fnDataLcd (0x04);
	fnDataLcd (0x04);
	fnDataLcd (0x04);
	fnDataLcd (0x04);
	fnDataLcd (0x00);


	fnCmdLcd(LCD_CLR);

}

/*****************************************************************************
NOME:			void	wr_lcd(char *s)

DESCRIÇÃO:		Escreve uma string de caracteres no display de LCD.

PARAMETROS:		Nulo

RETORNO:		Nulo
******************************************************************************/

void 
fnWrLcd(char *s)
{
	for(;*s != '\0';*s++)
	{
		fnDataLcd(*s);
	}
}



/******************************************************************************
NOME:        fnIntAsc(int num)

DESCRIÇÃO:   Transforma um inteiro para ascII e preenche a variavel indicada no 
             ponteiro "buff" da seguinte forma: xxxxx. Os valores numericos
             devem ser comvertidos antes de serem escritos no display.

PARAMETROS:  num: Valor inteiro a ser convertido.
             buff: ponteiro que indica o destino resultado. 

RETORNO:     nulo.
*******************************************************************************/

void 
fnIntAsc(long int num, char *buff)
{
	long int div;
	for(div=1000; div > 0; div=(div/10))
	{
		*buff++ = (0x30|(num/div));
		num = num%div;
	}
	*buff='\0';
}

/*****************************************************************************
NOME:			void fnPrintInt(int dado)

DESCRIÇÃO:		Escreve um número inteiro no display.

PARAMETROS:		Nulo

RETORNO:		Nulo
******************************************************************************/

void 
fnPrintInt(long int dado)
{
	unsigned char buffer[8];
	fnIntAsc(dado, buffer);
	fnWrLcd(buffer);
}

/********************************************************************
NOME:        fnPosCsr(unsigned char lin,unsigned char col)

DESCRIÇÃO:   Posiciona o cusrsor em qualquer posição do display de acordo
             com os parametros "lin" e "col". O posicionamento é feito a
             partir da posição 0x0 e vai até a posição 1x23.

PARAMETROS:  lin: 0-linha superior. 1-linha inferior.
             col: 0 a 23 posições de coluna do display

RETORNO:     Nulo
********************************************************************/

void
fnPosCsr(unsigned char lin,unsigned char col)
{
	switch(lin)
	{
		case 0:
			fnCmdLcd(0x80+col);
		break;

		case 1:
			fnCmdLcd(0xc0+col);
		break;

		case 2:
			fnCmdLcd(0x90+col);
		break;

		case 3:
			fnCmdLcd(0xD0+col);
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
fnClearLcd(void)
{
	fnCmdLcd(1);
}


/********************************************************************
NOME:        int fnLcdPutchar(char , File *unused)

DESCRIÇÃO:   Escreve um caracter no LCD, usado pela printf.

PARAMETROS:  dado a ser escrito, ponteiro de IO

RETORNO:     zero se escrita OK
********************************************************************/

int 
lcd_putchar(char c, FILE *unused)
{
  static bool nl_seen;

  if (nl_seen && c != '\n')
    {
      
 //      * First character after newline, clear display and home cursor.
       
       fnCmdLcd(1);     // Limpa o display e posiciona o cursor na margem superior esquerda

      nl_seen = false;
    }
  if (c == '\n')
    {
      nl_seen = true;
    }
  else
    {
      fnDataLcd(c);
//	  hd44780_wait_ready();
//      hd44780_outdata(c);
    }

  return 0;
}

