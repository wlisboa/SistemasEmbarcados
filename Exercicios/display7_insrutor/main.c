 /****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa
 *****************************************/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "io_ctr.h"

int main(){
    int intMinhaVariavel; // Contexto Local 
    mapPorts();
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
    while(1) { 
        digitalWrite(D2,TRUE);
        digitalWrite(D3,TRUE);
    }
    return 0;
} 