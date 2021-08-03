//*****************************************************************************
//***		LCD4B.H	   														***
//*****************************************************************************

#ifndef		__LCD4B_H_
#define		__LCD4B_H_

/******************************************************************************
 *																			  *	
 *	Definições da porta e dos bits que devem ser utilizados para o 			  *	
 *	acionamento do display de LCD											  *		
 *																			  * 
 ******************************************************************************/

#define		LCD_PORT	PORTC
#define		LCD_DDR		DDRC
#define		LCD_RS		PC3
#define		LCD_ENB 	PC2
#define		LCD_MASC 	0xFC

void	nible_lcd(unsigned char dado);
void	cmd_lcd(unsigned char dado);
void	init_lcd(void);
void	wr_lcd(char *s);
void	int_asc(long int num, char *buff);
void	print_int(long int dado);
void	pos_csr(unsigned char lin,unsigned char col); 
void	clear_lcd(void);

#endif
