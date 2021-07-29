 /****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa
 *****************************************/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "io_ctr.h"
#include "display_ctr.h"
#include "usart_w.h"

int main(){
    int intContador = 0;
    mapPorts();
    initDisplay();
    fnInitUsart(MYUBRR);

    while(1) { 
        fnWrUsart("Hello Word");
        _delay_ms(1000);
    }
    return 0;
}

