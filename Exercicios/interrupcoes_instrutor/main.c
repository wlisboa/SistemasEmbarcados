/****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa
 *****************************************/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "io_ctr.h"
#include "display_ctr.h"
#include "usart_w.h"
#include "driveadc.h"


ISR (INT0_vect)
{
    fnWrUsart("Entrou na interrupção");
}


void
fnInitExtInterrupt(void)
{
	SREG |= (1<<7); 
	MCUCR = _BV(ISC01)| _BV(ISC11);
}

void fnTelaInicial(void){
    fnWrUsart("Ola eu sou um sistema embarcado\n\r");
    fnWrUsart("Tnterrupcoes:\n\r");
}

int main(){
    int valor;

    // Inicializacao das bibliotecas
    mapPorts();
    initDisplay();
    fnInitUsart(MYUBRR);
    fnInitAdc();
    pinMode(D13, INPUT);
    digitalWrite(D13, TRUE);

    fnTelaInicial();

    // Loop principal
    while(1) {
        valor = digitalRead(D13);
        fnWrInt(valor);
        fnWrUsart("\n\r");
        _delay_ms(100);
    }

    return 0;
}