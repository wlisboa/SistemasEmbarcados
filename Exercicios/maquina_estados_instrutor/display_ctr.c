
#include "display_ctr.h" 


void initDisplay(){
    pinMode(D2,OUTPUT); //Seg a
    pinMode(D3,OUTPUT); //Seg b
    pinMode(D4,OUTPUT); //Seg c
    pinMode(D5,OUTPUT); //Seg d
    pinMode(D6,OUTPUT); //Seg e
    pinMode(D7,OUTPUT); //Seg f
    pinMode(D8,OUTPUT); //Seg g
    pinMode(D9,OUTPUT); //Seg .
}

void clearDisplay(){
    digitalWrite(D2,FALSE); //Seg a
    digitalWrite(D3,FALSE); //Seg b
    digitalWrite(D4,FALSE); //Seg c
    digitalWrite(D5,FALSE); //Seg d
    digitalWrite(D6,FALSE); //Seg e
    digitalWrite(D7,FALSE); //Seg f
    digitalWrite(D8,FALSE); //Seg g
    digitalWrite(D9,FALSE); //Seg .
}

void escreveDisplay(int valor){
    clearDisplay();
    switch(valor){
        case 0:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D4,TRUE); //Seg c
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D6,TRUE); //Seg e
            digitalWrite(D7,TRUE); //Seg f
        break;
        case 1:
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D4,TRUE); //Seg c
        break;
        case 2:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D6,TRUE); //Seg e
            digitalWrite(D8,TRUE); //Seg g
        break;
        case 3:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D4,TRUE); //Seg c
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D8,TRUE); //Seg g
        break;
        case 4:
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D4,TRUE); //Seg c
            digitalWrite(D7,TRUE); //Seg f
            digitalWrite(D8,TRUE); //Seg g
        break;
        case 5:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D4,TRUE); //Seg c
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D7,TRUE); //Seg f
            digitalWrite(D8,TRUE); //Seg g
        break;
        case 6:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D4,TRUE); //Seg c
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D6,TRUE); //Seg e
            digitalWrite(D7,TRUE); //Seg f
            digitalWrite(D8,TRUE); //Seg g
        break;
        case 7:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D4,TRUE); //Seg c
        break;
        case 8:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D4,TRUE); //Seg c
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D6,TRUE); //Seg e
            digitalWrite(D7,TRUE); //Seg f
            digitalWrite(D8,TRUE); //Seg g
        break;
        case 9:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D3,TRUE); //Seg b
            digitalWrite(D4,TRUE); //Seg c
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D7,TRUE); //Seg f
            digitalWrite(D8,TRUE); //Seg g
        break;
        default:
            digitalWrite(D2,TRUE); //Seg a
            digitalWrite(D5,TRUE); //Seg d
            digitalWrite(D6,TRUE); //Seg e
            digitalWrite(D7,TRUE); //Seg f
            digitalWrite(D8,TRUE); //Seg g
        break;
    }
}