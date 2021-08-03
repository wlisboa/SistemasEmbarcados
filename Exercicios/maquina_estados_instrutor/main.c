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


#define S_MENU_PRINCIAL  '0'
#define S_ACIONA_LED     '1' 
#define S_ACIONA_DISPLAY '2'
#define S_AD_DIGITAL     '3'
#define S_AD_SERIAL      '4'

int intEstado = S_MENU_PRINCIAL;
unsigned char ucEstadoLed;

void fnMenuPrincipal(void){
    unsigned char ucCmd;
    fnWrUsart("Ola eu sou um sistema embarcado\n\r");
    fnWrUsart("Comandos:\n\r");
    fnWrUsart("1 - Aciona o Led\n\r");
    fnWrUsart("2 - Display de 7 segmentos\n\r");
    fnWrUsart("3 - Ad digital\n\r");
    fnWrUsart("4 - Ad Serial\n\r");
    fnWrUsart("Digite um comando:");
    ucCmd = fnUsartGetC();
    fnUsartPutC(ucCmd);
    fnWrUsart("\n\r");
    intEstado = ucCmd;
}

void fnAcionaLed(void){
    static int intMenuLed;
    fnWrUsart("Menu aciona Led\n\r");
    fnWrUsart("l - Para acender e apagar o Led\n\r");
    fnWrUsart("q - Para sair\n\r");

    intMenuLed = fnUsartGetC();
    if (intMenuLed == 'l'){
        if (ucEstadoLed == 1){
            ucEstadoLed = 0;
            digitalWrite(D13, FALSE);
        }
        else{
            ucEstadoLed = 1;
            digitalWrite(D13, TRUE);
        }        
    }
    else if (intMenuLed == 'q'){
        intEstado = S_MENU_PRINCIAL;       
    }
}

void fnAcionaDisplay(void){
    static int intMenuAcionaDisplay;
    fnWrUsart("Menu aciona display\n\r");
    fnWrUsart("0 a 9 - Para acionar o display\n\r");
    fnWrUsart("q     - Para sair\n\r");
    intMenuAcionaDisplay = fnUsartGetC(); 
    if (intMenuAcionaDisplay == 'q'){
        intEstado = S_MENU_PRINCIAL;
    }
    else if('0'<= intMenuAcionaDisplay <= '9') {
        escreveDisplay(intMenuAcionaDisplay - 48);
    }
}

void fnAdDigital(void){
    
}

void fnAdSerial(void){
}


int main(){
    int intContador = 0;
    int iTensao;

    // Inicializacao das bibliotecas
    mapPorts();
    initDisplay();
    fnInitUsart(MYUBRR);
    fnInitAdc();
    pinMode(D13,OUTPUT);
    digitalWrite(A0, FALSE);

    // Loop principal
    while(1) {

        switch (intEstado){
            case S_MENU_PRINCIAL:
                /* code */
                fnMenuPrincipal();
            break;
            case S_ACIONA_LED:
                /* code */
                fnAcionaLed();
            break;
            case S_ACIONA_DISPLAY:
                /* code */
                fnAcionaDisplay();
            break;
            case S_AD_DIGITAL:
                /* code */
                fnAdDigital();
            break;
            case S_AD_SERIAL:
                /* code */
                fnAdSerial();
            break;

            default:
                intEstado = S_MENU_PRINCIAL;
                fnWrUsart("\n\n\r>>>>>ERRO<<<<\n\n\r");
            break;
        }
    }
    return 0;
}