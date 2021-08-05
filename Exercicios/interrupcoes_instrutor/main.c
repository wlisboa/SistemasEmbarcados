/****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa
 *****************************************/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "io_ctr.h"
#include "display_ctr.h"
#include "usart_w.h"
#include "driveadc.h"


ISR(INT0_vect)
{
    // Desliga o flag global de interrupção
	SREG &= ~_BV(7); 
    fnWrUsart("\n\n\rEntrou na interrupcao\n\n\r");
    // Habilita o flag global de interrupção
	SREG |= _BV(7); 
}

void fnInitExtInterrupt(void)
{
    // Desliga o flag global de interrupção
	SREG &= ~_BV(7); 

    EICRA = _BV(ISC01);  // Configura o pino D2 para detectar borda de descida
    EIMSK = _BV(INT0);   // Habilita a interrupção 0

    // Habilita o flag global de interrupção
	SREG |= _BV(7); 
}

void fnTelaInicial(void){
    fnWrUsart("Ola eu sou um sistema embarcado\n\r");
    fnWrUsart("Tnterrupcoes:\n\r");
}

int main(){
    int valor;

    // Inicializacao das bibliotecas
    mapPorts();
    fnInitUsart(MYUBRR);
    digitalWrite(D2, TRUE);
    pinMode(D2, INPUT);
    fnInitExtInterrupt();

    fnTelaInicial();

    // Loop principal
    while(1) {
        fnWrUsart(".");
        _delay_ms(1000);
    }
    return 0;
}