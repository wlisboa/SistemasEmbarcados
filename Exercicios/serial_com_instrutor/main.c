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
    unsigned char ucCmd;
    mapPorts();
    initDisplay();
    fnInitUsart(MYUBRR);

    while(1) { 
        fnWrUsart("Ola eu sou um sistema embarcado\n\r");
        fnWrUsart("Digite um comando:");
        ucCmd = fnUsartGetC();
        if (ucCmd == '1'){
            fnWrUsart("\n\n\rVoce digitou um comando valido\n\n\r");
            escreveDisplay(1);
        }
        else if(ucCmd == '2'){
            fnWrUsart("\n\n\rVoce digitou um comando valido\n\n\r");
            escreveDisplay(2);
        }
        else{
            fnWrUsart("\n\n\r>>>>>ERRO<<<<\n\n\r");
        }
        _delay_ms(10);
    }
    return 0;
}

