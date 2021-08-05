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

int inTicSistema;

ISR (TIMER0_COMPA_vect)
{
	inTicSistema++;
}

ISR(INT0_vect)
{
    // Desliga o flag global de interrupção
	SREG &= ~_BV(7); 
    fnWrUsart("\n\n\rEntrou na interrupcao Externa\n\n\r");
    // Habilita o flag global de interrupção
	SREG |= _BV(7); 
}

void fnInitTimer0(){
    TCCR0A |= (1 << COM0A0); // Configure timer 0 for OC0A comapare match.
    TIMSK0 |= (1 << OCIE0A); // Enable CTC interrupt
	SREG |= _BV(7);          // Enable global interrupts
    OCR0A   = 55;            // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
    TCCR0B |= ((1 << CS01) | (1 << CS00)); // Start timer at Fcpu/64
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
    fnInitTimer0();

    fnTelaInicial();

    // Loop principal
    while(1) {
        fnWrUsart("Tick: ");
        fnWrInt(inTicSistema);
        fnWrUsart("\n\r");
        _delay_ms(1000);
    }
    return 0;
}