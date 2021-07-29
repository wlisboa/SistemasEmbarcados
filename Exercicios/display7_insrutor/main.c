 /****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa
 *****************************************/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "io_ctr.h"
#include "display_ctr.h"

int main(){
    int intContador = 0;
    mapPorts();
    initDisplay();
    while(1) { 
        while (intContador < 10){
            escreveDisplay(intContador);
            intContador++;
            _delay_ms(1000);
        }
        intContador = 0;        

        for(intContador = 0; intContador < 10; intContador++){
            escreveDisplay(intContador);
            _delay_ms(100);
        }
        intContador = 0;        
    }
    return 0;
}

