//*****************************************************************************
//***		LCD4B.H	   														***
//*****************************************************************************

#ifndef		__LCD4B_H_
#define		__LCD4B_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//****************************************************************************
//		DEFINIÇÃO DA PORTA UTILIZADA PARA O ACIONAMENTO DO DISPLAY
//****************************************************************************

#define		LCD_PORT	PORTC
#define		LCD_DDR		DDRC
#define		LCD_RS		PC3
#define		LCD_ENB 	PC2
#define		LCD_MASC 	0xFC


/* Clear LCD display command. 
 * 
 *comando de limpesa do LCD.
 */
#define LCD_CLR		0x01

/* Home cursor command. 
 *
 * Leva o cursor para posição inicial.
 */
#define LCD_HOME	0x02

/*
 * Select the entry mode.  inc determines whether the address counter
 * auto-increments, shift selects an automatic display shift.
 *
 * seleciona o modo de entrada de dados dizendo para que lado o cursor irá 
 * se deslocar 0 esquerda 1 direita. "inc" determina quando o endereço 
 * auto incrementa o contador de endereço, shift determina se a informação
 * deve se deslocar ou não com a entrada de um novo caractere. 
 */
#define LCD_ENTMODE(inc, shift) \
	(0x04 | ((inc)? 0x02: 0) | ((shift)? 1: 0))

/*
 * Selects disp[lay] on/off, cursor on/off, cursor blink[ing]
 * on/off.
 */
#define LCD_DISPCTL(disp, cursor, blink) \
	(0x08 | ((disp)? 0x04: 0) | ((cursor)? 0x02: 0) | ((blink)? 1: 0))

/*
 * With shift = 1, shift display right or left.
 * With shift = 0, move cursor right or left.
 */
#define LCD_SHIFT(shift, right) \
	(0x10 | ((shift)? 0x08: 0) | ((right)? 0x04: 0))

/*
 * Function set.  if8bit selects an 8-bit data path, twoline arranges
 * for a two-line display, font5x10 selects the 5x10 dot font (5x8
 * dots if clear).
 */
#define LCD_FNSET(if8bit, twoline, font5x10) \
	(0x20 | ((if8bit)? 0x10: 0) | ((twoline)? 0x08: 0) | ((font5x10)? 0x04: 0))

/*
 * Set the next character generator address to addr.
 */
#define LCD_CGADDR(addr) \
	(0x40 | ((addr) & 0x3f))

/*
 * Set the next display address to addr.
 */
#define LCD_DDADDR(addr) \
	(0x80 | ((addr) & 0x7f))


// Caracter da seta para direita (->)
#define SETA_DIREITA 126

// Caracter da seta para direita (<-)
#define SETA_ESQUERDA 127

// Endereço do caractere especial bolinha do simbolo de grau na CGRAM
#define	SETA_CIMA 0

// Endereço da seta para baixo
#define	SETA_BAIXO 1

// Endereço do caractere especial quadrado na CGRAM
#define	QUADRADO 0xFF


//  Prototipo das funções di módulo

void	fnNibleLcd(unsigned char dado);
void	fnCmdLcd(unsigned char dado);
void	fnDataLcd(unsigned char dado);
void	fnInitLcd(void);
void	fnWrLcd(char *s);
void	fnIntAsc(long int num, char *buff);
void	fnPrintInt(long int dado);
void	fnPosCsr(unsigned char lin,unsigned char col); 
void	fnClearLcd(void);
int 
lcd_putchar(char c, FILE *unused);

#endif
