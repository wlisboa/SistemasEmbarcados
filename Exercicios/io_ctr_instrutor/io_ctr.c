#include "io_ctr.h"

BIT_PORT_REG bprPortMap[20];

BIT_PORT_REG setBIT_PORT_REG(uint16_t uiPort,
                            uint16_t  uiDdr,
                            uint16_t uiBit){
    BIT_PORT_REG bprLoad;
    bprLoad.uiPort =  uiPort;
    bprLoad.uiDdr =  uiDdr;
    bprLoad.uiBit =  uiBit;
    return bprLoad;
}

void mapPorts(void){
    bprPortMap[D0] = setBIT_PORT_REG(&PORTD, &DDRD, PD0);
    bprPortMap[D1] = setBIT_PORT_REG(&PORTD, &DDRD, PD1);
    bprPortMap[D2] = setBIT_PORT_REG(&PORTD, &DDRD, PD2);
    bprPortMap[D3] = setBIT_PORT_REG(&PORTD, &DDRD, PD3);
    bprPortMap[D4] = setBIT_PORT_REG(&PORTD, &DDRD, PD4);
    bprPortMap[D5] = setBIT_PORT_REG(&PORTD, &DDRD, PD5);
    bprPortMap[D6] = setBIT_PORT_REG(&PORTD, &DDRD, PD6);
    bprPortMap[D7] = setBIT_PORT_REG(&PORTD, &DDRD, PD7);
    bprPortMap[D8] = setBIT_PORT_REG(&PORTB, &DDRB, PB0);
    bprPortMap[D9] = setBIT_PORT_REG(&PORTB, &DDRB, PB1);
    bprPortMap[D10]= setBIT_PORT_REG(&PORTB, &DDRB, PB2);
    bprPortMap[D11]= setBIT_PORT_REG(&PORTB, &DDRB, PB3);
    bprPortMap[D12]= setBIT_PORT_REG(&PORTB, &DDRB, PB4);
    bprPortMap[D13]= setBIT_PORT_REG(&PORTB, &DDRB, PB5);
    bprPortMap[A0] = setBIT_PORT_REG(&PORTC, &DDRC, PC0);
    bprPortMap[A1] = setBIT_PORT_REG(&PORTC, &DDRC, PC1);
    bprPortMap[A2] = setBIT_PORT_REG(&PORTC, &DDRC, PC2);
    bprPortMap[A3] = setBIT_PORT_REG(&PORTC, &DDRC, PC3);
    bprPortMap[A4] = setBIT_PORT_REG(&PORTC, &DDRC, PC4);
    bprPortMap[A5] = setBIT_PORT_REG(&PORTC, &DDRC, PC5);
}

/***************************************************
void pinMode(int pin, int dir)
Descrição: Configura os pinos do chip como entrada
ou como saída
***************************************************/
void pinMode(int pin, int dir){
    uint16_t *uiptrDdr;
    uint16_t uiBit;
    
    uiptrDdr = bprPortMap[pin].uiDdr;
    uiBit = bprPortMap[pin].uiBit;

    if (dir == INPUT){
        //Configura como entrada
        *uiptrDdr &= ~(1<<uiBit );
    }
    else{
        //Configura como saída
        *uiptrDdr |= (1<<uiBit );
    }
}

/***************************************************
Descrição: 
***************************************************/
void digitalWrite(int pin, int value){
    uint16_t *uiptrPort;
    uint16_t uiBit;
    uiptrPort = bprPortMap[pin].uiPort;
    uiBit = bprPortMap[pin].uiBit;

    if (value == FALSE){
        //Configura como entrada
        *uiptrPort &= ~(1<<uiBit);
    }
    else{
        //Configura como saída
        *uiptrPort |= (1<<uiBit);
    }
}