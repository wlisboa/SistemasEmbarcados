 /****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa


 *****************************************/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "io_ctr.h"

int main(){
    mapPorts();
    pinMode(D13,OUTPUT);
    while(1) { 
        digitalWrite(D13,TRUE);
        _delay_ms(100);
        digitalWrite(D13,FALSE);
        _delay_ms(100);
    }
    return 0;
} 