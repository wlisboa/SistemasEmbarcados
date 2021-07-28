 /****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa
 *****************************************/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "io_ctr.h"

void escreveDisplay(int valor){
    if (valor == 1){
        digitalWrite(D2,FALSE); //Seg a
        digitalWrite(D3,TRUE); //Seg b
        digitalWrite(D4,TRUE); //Seg c
        digitalWrite(D5,FALSE); //Seg d
        digitalWrite(D6,FALSE); //Seg e
        digitalWrite(D7,FALSE); //Seg f
        digitalWrite(D8,FALSE); //Seg g
        digitalWrite(D9,FALSE); 
    } 

    if (valor == 2){
        digitalWrite(D2,TRUE); //Seg a
        digitalWrite(D3,TRUE); //Seg b
        digitalWrite(D4,FALSE); //Seg c
        digitalWrite(D5,TRUE); //Seg d
        digitalWrite(D6,TRUE); //Seg e
        digitalWrite(D7,FALSE); //Seg f
        digitalWrite(D8,TRUE); //Seg g
        digitalWrite(D9,FALSE); 
    } 
}

int main(){
    mapPorts();
    pinMode(D2,OUTPUT); //Seg a
    pinMode(D3,OUTPUT); //Seg b
    pinMode(D4,OUTPUT); //Seg c
    pinMode(D5,OUTPUT); //Seg d
    pinMode(D6,OUTPUT); //Seg e
    pinMode(D7,OUTPUT); //Seg f
    pinMode(D8,OUTPUT); //Seg g
    pinMode(D9,OUTPUT); //Seg .
    while(1) { 
        escreveDisplay(2);
    }
    return 0;
} 