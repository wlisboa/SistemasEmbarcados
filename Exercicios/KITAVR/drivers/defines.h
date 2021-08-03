//*****************************************************************************
//***		DEFINES.H  														***
//*****************************************************************************

#ifndef		__DEFINES_H_
#define		__DEFINES_H_

#include<avr\io.h>
#include<avr\iom16.h>


//****************************************************************************
//		DEFINIÇÕES DOS ESTADOS DO SISTEMA
//****************************************************************************

enum
{
	PRINCIPAL,
	ESTADO_A,
	ESTADO_B,
	ESTADO_C,
	ESTADO_D,
	ESTADO_E,
	ESTADO_F,
	ESTADO_G
};

//****************************************************************************
//		DEFINIÇÕES COM O MONITOR SERIAL
//****************************************************************************

unsigned char 
str_cmd[10],
str_sys[10];


//****************************************************************************
//		DEFINIÇÕES RELACIONADAS COM O ADC
//****************************************************************************

int tensao_lida;


//****************************************************************************
//		VARIÁVEIS UTILIZADAS NO TESTE
//****************************************************************************
#define MAX_TECLAS 8
#define MIN_TECLAS 1

#define MAX_COR_LED 4
#define MIN_COR_LED 1



unsigned char  print_flag, seta_flag, num_teclas, tecla_leitura, cor_led, pos_menu,
			   pos_menu_D;

int tensao_tecla;
int inTicSistema;


//****************************************************************************
//		REGISTROS DE CONTROLE SOFTWARE DO SISTEMA
//****************************************************************************

//  Os registros de sistema são utilizados para guardar as solicitações de software
//  bit7   	bit6   	bit5   	bit4   	bit3   	bit2   	bit1   	bit0   	
//  SF		SF		SF		SF		SW1     SW2     SW3     SW4
static unsigned char
REG_SISTEMA_0;

//****************************************************************************
//		DEFINIÇÕES RELACIONADAS AO TECLADO
//****************************************************************************

#define		TECLAS_DDR		DDRD
#define		TECLAS_PORT		PORTD
#define		TECLAS_PIN		PIND

// Verifica se o bit da tecla foi para nivel 0
#define		SW1_HW	(PIND & _BV(PIND3))
#define		SW2_HW	(PIND & _BV(PIND4))
#define		SW3_HW	(PIND & _BV(PIND5))
#define		SW4_HW	(PIND & _BV(PIND6))

// Usado para testar se a tecla foi precionada
#define		SW1		(REG_SISTEMA_0 & _BV(0)) 
#define		SW2		(REG_SISTEMA_0 & _BV(1)) 
#define		SW3		(REG_SISTEMA_0 & _BV(2)) 
#define		SW4		(REG_SISTEMA_0 & _BV(3)) 

// Limpa ps bits do sistema referentes as teclas
#define		CLEAR_SW1	REG_SISTEMA_0 &= ~_BV(0)
#define		CLEAR_SW2	REG_SISTEMA_0 &= ~_BV(1)
#define		CLEAR_SW3	REG_SISTEMA_0 &= ~_BV(2)
#define		CLEAR_SW4	REG_SISTEMA_0 &= ~_BV(3)


//****************************************************************************
//		DEFINIÇÃO DE MACROS QUE UTILIZAM ASM
//****************************************************************************

#define SET_PB(port,bit) \
		__asm__ __volatile__ ( 	"sbi %0, %1" "\n\t"\
								: /* no outputs */ \
								: "I" (_SFR_IO_ADDR(port)), "I" (bit) \
		)

#define CLR_PB(port,bit) \
		__asm__ __volatile__ (  "cbi %0, %1" "\n\t"\
								: /* no outputs */ \
								: "I" (_SFR_IO_ADDR(port)), "I" (bit) \
		)

#define GASTA1cl() \
		__asm__ __volatile__ (  "nop"\
								::)


#endif





