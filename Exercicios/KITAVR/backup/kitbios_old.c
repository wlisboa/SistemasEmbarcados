//******************************************************************************
//***		KITBIOS.C													 	 ***
//******************************************************************************

/******************************************************************************

VERSÃO: 0.0
DOC REV 0 - 11.09.07

  O seguinte software foi criado com o objetivo de calibração do oscilador interno
  do BINA.



Autor: Washington Pinto Lisboa
email: w_lisboa@click21.com.br

*******************************************************************************/

/**************INICIALIZAÇÃO DAS BIBLIOTECAS***********************************/

#include<avr\io.h>
#include<avr\iom16.h>
#include<avr\interrupt.h>

#include"defines.h"
#include"atrasos.h"
#include"lcd4b.h"

/******************************************************************************/

/******************************************************************************
 *																			  *
 *			Declaração de variáveis globais									  *
 *																			  *
 ******************************************************************************/

int		qtd_pulso, periodo;

unsigned char flag_t;

/******************************************************************************
 *																			  *
 *			Funções relacionadas com interrupções							  *
 *																			  *
 ******************************************************************************/

/******************************************************************************
NOME:        init_INT0()

DESCRIÇÃO:   Inicializa a interrupção externa 0 do chip

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
init_INTx(void)
{
	SREG  = 0x80;
	MCUCR = (1<<ISC01)| (1<<ISC11); // Configura para atuar na borda de descida.
}

/***************************************************************************
NOME:       int0_ctr(int ctr)

DESCRIÇÃO:  Controla a atuação da interrupção externa int0, de acordo com o
            parametro ctr. Quando ctr é levado para 0 a interrupção é desabilitada.

PARAMETROS: ctr - Vairável de controle: 0 - desabilita a interrupção externa.
                                        1 - Habilita a interrupção externa.

RETORNO:    Nulo.
****************************************************************************/

void int0_ctr(int ctr)
{
	if(ctr)
	{
		GIFR |=_BV(INTF0);			// LIMPA A BANEIRA DE ITERRUPÇÃO
		GICR |=_BV(INT0);  			// INICIALIZA A INTERRUPÇÃO
	}
	else
	{
		GICR &= ~_BV(INT0);  		// PARA A INTERRUPÇÃO
		GIFR |=_BV(INTF0);			// LIMPA A BANEIRA DE ITERRUPÇÃO
	}
}

/******************************************************************************
NOME:        ISR ( )

DESCRIÇÃO:   A seguinte função é chamada quando ocorre uma uma borada de
             descida no pino INT0, nesse firware é utilizada para decodificar
			 as informações provenintes do controle remoto.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

ISR (INT0_vect)
{
	qtd_pulso ++;
	flag_t = 1;
}


/***************************************************************************
NOME:       int1_ctr(int ctr)

DESCRIÇÃO:  Controla a atuação da interrupção externa int0, de acordo com o
            parametro ctr. Quando ctr é levado para 0 a interrupção é desabilitada.

PARAMETROS: ctr - Vairável de controle: 0 - desabilita a interrupção externa.
                                        1 - Habilita a interrupção externa.

RETORNO:    Nulo.
****************************************************************************/

void int1_ctr(int ctr)
{
	if(ctr)
	{
		GIFR |=_BV(INTF1);			// LIMPA A BANEIRA DE ITERRUPÇÃO
		GICR |=_BV(INT1);  			// INICIALIZA A INTERRUPÇÃO
	}
	else
	{
		GICR &= ~_BV(INT1);  		// INICIALIZA A INTERRUPÇÃO
		GIFR |=_BV(INTF1);			// LIMPA A BANEIRA DE ITERRUPÇÃO
	}
}

/******************************************************************************
NOME:        ISR ( )

DESCRIÇÃO:   A seguinte função é chamada quando ocorre uma uma borada de
             descida no pino INT0, nesse firware é utilizada para decodificar
			 as informações provenintes do controle remoto.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

ISR (INT1_vect)
{
	qtd_pulso ++;
	flag_t = 1;
}

/******************************************************************************
NOME:        init_TC1()

DESCRIÇÃO:   Inicializa a interrupção do timer 1.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
init_TC1(void)
{
//	TCCR1A = (1<<COM1A0);			// Configura para utilizar o OCR1An.
	TCCR1B = (1<<WGM12);			// Configura para "CTC mode" modo 4 de operação.
	TIMSK  = (1<<OCIE1A);			// Configura para gerar interrupção de CTC.

	OCR1AH = 0x4b;					//493e  18800
	OCR1AL = 0x13;
}

/***************************************************************************
NOME:       void timer1_ctr(int ctr)

DESCRIÇÃO:  Controla a atuação da interrupção

PARAMETROS: ctr - Vairável de controle: 0 - desabilita a interrupção externa.
                                        1 - Habilita a interrupção externa.

RETORNO:    Nulo.
****************************************************************************/

void timer1_ctr(int ctr)
{
	if(ctr)
	{
		TCCR1B |= _BV(CS10);		// Liga o timer com frequência de Clock/64
		TCCR1B |= _BV(CS11);		// Liga o timer com frequência de Clock/64
	}
	else
	{
		TCCR1B &= ~_BV(CS10);		// Desliga o timer.
		TCCR1B &= ~_BV(CS11);
		TCNT1H	= 0;
		TCNT1H  = 0;
	}
}

/******************************************************************************
NOME:        ISR ( )

DESCRIÇÃO:   A seguinte função é chamada quando ocorre uma interrupção de
			 comparação no timer 1.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

ISR (TIMER1_COMPA_vect )
{
	periodo ++;
}

/******************************************************************************
NOME:        void	le_freq_low()

DESCRIÇÃO:   Utiliza a interrupção externa 0 para medir a frequencia baixa.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

int
le_freq_low(void)
{
	PORTD &= ~_BV(ESQUERDA);
	periodo = 0;
	qtd_pulso =0;
	flag_t = 0;

	int0_ctr(1);
	do{
	}while(!flag_t);
	timer1_ctr(1);
	do{
	}while(periodo < 10);
	int0_ctr(0);
	timer1_ctr(0);
	PORTD |= _BV(ESQUERDA);

	return qtd_pulso;
}

/******************************************************************************
NOME:        void	le_freq_high()

DESCRIÇÃO:   Utiliza a interrupção externa 0 para medir a frequencia baixa.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

int
le_freq_high(void)
{
	PORTD &= ~_BV(ESQUERDA);
	atraso_1ms(10);

	periodo = 0;
	qtd_pulso =0;

	flag_t = 0;
	int1_ctr(1);
	do{
	}while(!flag_t);
	timer1_ctr(1);

	do{
	}while(periodo < 10);
	int1_ctr(0);
	timer1_ctr(0);
	PORTD |= _BV(ESQUERDA);

	return	qtd_pulso;
}

/******************************************************************************
NOME:        void	preciona_esquerda()

DESCRIÇÃO:   Faz com que o jig precione a tecla esquerda do bina.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
preciona_esquerda()
{
	PORTD &= ~_BV(ESQUERDA);
	atraso_1ms(30);
	PORTD |= _BV(ESQUERDA);
	atraso_1ms(3);
}

/******************************************************************************
NOME:        void	preciona_direita()

DESCRIÇÃO:   Faz com que o jig precione a tecla direita do bina.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
preciona_direita()
{
	PORTD &= ~_BV(DIREITA);
	atraso_1ms(30);
	PORTD |= _BV(DIREITA);
	atraso_1ms(3);
}

/******************************************************************************
NOME:        void	preciona_cima()

DESCRIÇÃO:   Faz com que o jig precione a tecla cima do bina.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
preciona_cima()
{
	PORTD &= ~_BV(CIMA);
	atraso_1ms(30);
	PORTD |= _BV(CIMA);
	atraso_1ms(3);
}

/******************************************************************************
NOME:        void	preciona_baixo()

DESCRIÇÃO:   Faz com que o jig precione a tecla baixo do bina.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
preciona_baixo()
{
	PORTD &= ~_BV(BAIXO);
	atraso_1ms(30);
	PORTD |= _BV(BAIXO);
	atraso_1ms(3);
}

/******************************************************************************
NOME:        void	entrar_ajuste()

DESCRIÇÃO:   Faz com que o bina entre em modo de ajuste.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
entrar_ajuste()
{
	pos_csr(0,0);
	wr_lcd("Entrar no Ajuste");

	PORTD = 0xFF;					// Liga os pull_ups internos da porta
	DDRD  = 0xF4;
	PORTD &= ~_BV(ESQUERDA);

	do{
	}while(!TH_FREQ);

	PORTD |= _BV(ESQUERDA);
	DDRD  = 0xF0;
}

/******************************************************************************
NOME:        void	incrementa_low()

DESCRIÇÃO:   Incrementa a frequência baixa do digito. Para incrementar a
			 frequência deve-se decrementar a constante.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
incrementa_low()
{
	preciona_direita();
	preciona_baixo();
	preciona_esquerda();
}

/******************************************************************************
NOME:        void	Decrementa_low()

DESCRIÇÃO:   Decrementa a frequência baixa do digito. Para incrementar a
			 frequência deve-se decrementar a constante.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
decrementa_low()
{
	preciona_direita();
	preciona_cima();
	preciona_esquerda();
}

/******************************************************************************
NOME:        void	incrementa_high()

DESCRIÇÃO:   Incrementa a frequência baixa do digito. Para incrementar a
			 frequência deve-se decrementar a constante.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
incrementa_high()
{
	preciona_direita();
	preciona_direita();
	preciona_baixo();
	preciona_esquerda();
}

/******************************************************************************
NOME:        void	decrementa_high()

DESCRIÇÃO:   Decrementa a frequência alta do digito. Para incrementar a
			 frequência deve-se decrementar a constante.

PARAMETROS:  Nulo.

RETORNO:     Nulo.
******************************************************************************/

void
decrementa_high()
{
	preciona_direita();
	preciona_direita();
	preciona_cima();
	preciona_esquerda();
}

/******************************************************************************
NOME:        void	ajusta_low()

DESCRIÇÃO:   Ajuata a frequencia baixa.

PARAMETROS:  inf - Nível inferior da frequencia.
			 inf - Nível superior da frequencia.

RETORNO:     Nulo.
******************************************************************************/

void
ajusta_low(int inf, int sup)
{
	unsigned char f_saida;
	int freq_lida;
	f_saida = 1;
	do
	{
		freq_lida = le_freq_low();
		pos_csr(3,0);
		print_int(freq_lida);

		if(freq_lida < inf)
		{
			incrementa_low();
		}
		else
		{
			if(freq_lida > sup)
			{
				decrementa_low();
			}
			else
			{
				f_saida = 0;
			}
		}
	}while(f_saida);
}


/******************************************************************************
NOME:        void	ajusta_high()

DESCRIÇÃO:   Ajuata a frequencia baixa.

PARAMETROS:  inf - Nível inferior da frequencia.
			 inf - Nível superior da frequencia.

RETORNO:     Nulo.
******************************************************************************/

void
ajusta_high(int inf, int sup)
{
	unsigned char f_saida;
	int freq_lida;
	f_saida = 1;
	do
	{
		freq_lida = le_freq_high();
		pos_csr(3,0);
		print_int(freq_lida);

		if(freq_lida < inf)
		{
			incrementa_high();
		}
		else
		{
			if(freq_lida > sup)
			{
				decrementa_high();
			}
			else
			{
				f_saida = 0;
			}
		}
	}while(f_saida);
}

/******************************************************************************
 *																			  *
 *			Rotina principal do sistema										  *
 *																			  *
 ******************************************************************************/

int
main()
{
	int valor;

	PORTD = 0xFF;					// Liga os pull_ups internos da porta
	DDRD  = 0xF0;

	PORTB = 0x01;					// Liga os pull_ups internos da porta
	DDRB  = 0x00;

	init_lcd();						// Inicializa o display de LCD.
	init_INTx();					// Inicializa as interrupções externas.
	init_TC1();						// Inicializa o Timer 1.

	int0_ctr(0);
	int1_ctr(0);

	wr_lcd("Pres Inicio");

	for(;;)
	{

		do{
		}while(T_INICIO);


		entrar_ajuste();
		clear_lcd();
		wr_lcd("Digito: 0");


//  Ajusta Digito:0, low = 941 , high = 1336
		pos_csr(2,0);
		wr_lcd("Baixa = 941");

		ajusta_low(927, 955);

		pos_csr(2,0);
		wr_lcd("Alta = 1336");

		ajusta_high(1316, 1356);

		preciona_cima();

//  Ajusta Digito:1, low = 697 , high = 1209
		pos_csr(0,8);
		data_lcd('1');

		pos_csr(2,0);
		wr_lcd("Baixa = 697");
		ajusta_low(687, 707);

		pos_csr(2,0);
		wr_lcd("Alta = 1209");
		ajusta_high(1191, 1227);

		preciona_cima();
//  Ajusta Digito:2, low = 697 , high = 1336
		pos_csr(0,8);
		data_lcd('2');

		pos_csr(2,0);
		wr_lcd("Baixa = 697");
		ajusta_low(687, 707);

		pos_csr(2,0);
		wr_lcd("Alta = 1336");
		ajusta_high(1316, 1356);


		preciona_cima();
//  Ajusta Digito:3, low = 697 , high = 1477
		pos_csr(0,8);
		data_lcd('3');

		pos_csr(2,0);
		wr_lcd("Baixa = 697");
		ajusta_low(687, 707);

		pos_csr(2,0);
		wr_lcd("Alta = 1477");
		ajusta_high(1455, 1499);


		preciona_cima();
//  Ajusta Digito:4, low = 770 , high = 1209
		pos_csr(0,8);
		data_lcd('4');

		pos_csr(2,0);
		wr_lcd("Baixa = 770");
		ajusta_low(759, 781);

		pos_csr(2,0);
		wr_lcd("Alta = 1209");
		ajusta_high(1191, 1227);


		preciona_cima();
//  Ajusta Digito:5, low = 770 , high = 1336
		pos_csr(0,8);
		data_lcd('5');

		pos_csr(2,0);
		wr_lcd("Baixa = 770");
		ajusta_low(759, 781);

		pos_csr(2,0);
		wr_lcd("Alta = 1336");
		ajusta_high(1316, 1356);


		preciona_cima();
//  Ajusta Digito:6, low = 770 , high = 1477
		pos_csr(0,8);
		data_lcd('6');

		pos_csr(2,0);
		wr_lcd("Baixa = 770");
		ajusta_low(759, 781);

		pos_csr(2,0);
		wr_lcd("Alta = 1477");
		ajusta_high(1455, 1499);


		preciona_cima();
//  Ajusta Digito:7, low = 852 , high = 1209
		pos_csr(0,8);
		data_lcd('7');

		pos_csr(2,0);
		wr_lcd("Baixa = 852");
		ajusta_low(840, 864);

		pos_csr(2,0);
		wr_lcd("Alta = 1209");
		ajusta_high(1191, 1227);


		preciona_cima();
//  Ajusta Digito:8, low = 852 , high = 1336
		pos_csr(0,8);
		data_lcd('8');

		pos_csr(2,0);
		wr_lcd("Baixa = 852");
		ajusta_low(840, 864);

		pos_csr(2,0);
		wr_lcd("Alta = 1336");
		ajusta_high(1316, 1356);


		preciona_cima();
//  Ajusta Digito:9, low = 852 , high = 1477
		pos_csr(0,8);
		data_lcd('9');

		pos_csr(2,0);
		wr_lcd("Baixa = 852");
		ajusta_low(840, 864);

		pos_csr(2,0);
		wr_lcd("Alta = 1477");
		ajusta_high(1455, 1499);


		clear_lcd();
		wr_lcd("Fim do Ajuste ");

	}// Fim do loop principal.

	return 0;
}
