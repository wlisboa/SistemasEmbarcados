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

int main(){
    int intContador = 0;
    unsigned char ucCmd;
    unsigned char ucEstado;
    char myString[20];
    int valor = 5;
    sprintf(myString, "Valor = %d", &valor);

    mapPorts();
    initDisplay();
    fnInitUsart(MYUBRR);

    pinMode(D13, OUTPUT);

    while(1) { 
        fnWrUsart("Ola eu sou um sistema embarcado\n\r");
        fnWrUsart(myString);
        fnWrUsart("Comandos:\n\r");
        fnWrUsart("1 - Escreve no display\n\r");
        fnWrUsart("2 - Escreve no display\n\r");
        fnWrUsart("l - Liga o Led\n\r");
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
        else if(ucCmd == 'l'){
            fnWrUsart("\n\n\rVoce digitou um comando valido\n\n\r");
            if (ucEstado == 1){
                ucEstado = 0;
                digitalWrite(D13, FALSE);
            }
            else{
                ucEstado = 1;
                digitalWrite(D13, TRUE);
            }
        }
        else{
            fnWrUsart("\n\n\r>>>>>ERRO<<<<\n\n\r");
        }
        _delay_ms(10);
    }
    return 0;
}

