 /****************************************  
 Software criado para estudo da linguagem C
 Autor: Washington Lisboa


 *****************************************/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN 5 

/***************************************************
Configuração de entrada ou saída
***************************************************/
#define OUTPUT 0
#define INPUT  1

#define FALSE  0
#define TRUE   1

/***************************************************
Definições dos pinos digitais
***************************************************/
#define D0      0  // Port D
#define D1      1
#define D2      2
#define D3      3
#define D4      4
#define D5      5
#define D6      6
#define D7      7
#define D8      8  // Porta B
#define D9      9
#define D10     10
#define D11     11
#define D12     12
#define D13     13

/***************************************************
Definições dos pinos analogicos
***************************************************/
#define A0     14
#define A1     15
#define A2     16
#define A3     17
#define A4     18
#define A5     19

typedef struct{
    uint16_t uiPort;
    uint16_t uiDdr;
    uint16_t uiBit;
}BIT_PORT_REG;

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
        *uiptrDdr &= ~(1<<uiBit );
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

/***************************************************
void pinMode(int pin, int dir)
Descrição: Configura os pinos do chip como entrada
ou como saída
***************************************************/
void pinMode_old(int pin, int dir){
    //Configuração do D0
    if (pin == D0){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b11111110;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b00000001;
        }
    }

    //Configuração do D1
    if (pin == D1){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b11111101;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b00000010;
        }
    }

    //Configuração do D2
    if (pin == D2){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b11111011;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b00000100;
        }
    }

    //Configuração do D3
    if (pin == D3){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b11110111;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b00001000;
        }
    }

    //Configuração do D4
    if (pin == D4){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b11101111;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b00010000;
        }
    }    

    //Configuração do D5
    if (pin == D5){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b11011111;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b00100000;
        }
    }

    //Configuração do D6
    if (pin == D6){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b10111111;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b01000000;
        }
    }

    //Configuração do D7
    if (pin == D7){
        if (dir == INPUT){
            //Configura como entrada
            DDRD = DDRD & 0b01111111;         
        }
        else{
            //Configura como saída
            DDRD = DDRD | 0b10000000;
        }
    }

    //Configuração do D8
    if (pin == D8){
        if (dir == INPUT){
            //Configura como entrada
            DDRB = DDRB & 0b11111110;         
        }
        else{
            //Configura como saída
            DDRB = DDRB | 0b00000001;
        }
    }

    //Configuração do D9
    if (pin == D9){
        if (dir == INPUT){
            //Configura como entrada
            DDRB = DDRB & 0b11111101;         
        }
        else{
            //Configura como saída
            DDRB = DDRB | 0b00000010;
        }
    }

   //Configuração do D10
    if (pin == D10){
        if (dir == INPUT){
            //Configura como entrada
            DDRB = DDRB & 0b11111011;         
        }
        else{
            //Configura como saída
            DDRB = DDRB | 0b00000100;
        }
    }

    //Configuração do D11
    if (pin == D11){
        if (dir == INPUT){
            //Configura como entrada
            DDRB = DDRB & 0b11110111;         
        }
        else{
            //Configura como saída
            DDRB = DDRB | 0b00001000;
        }
    }

    //Configuração do D12
    if (pin == D12){
        if (dir == INPUT){
            //Configura como entrada
            DDRB = DDRB & 0b11101111;         
        }
        else{
            //Configura como saída
            DDRB = DDRB | 0b00010000;
        }
    }

    //Configuração do D13
    if (pin == D13){
        if (dir == INPUT){
            //Configura como entrada
            DDRB = DDRB & 0b11011111;         
        }
        else {
            //Configura como saída
            DDRB = DDRB | 0b00100000;
        }
    }

    //Configuração do A0
    if (pin == A0){
        if (dir == INPUT){
            //Configura como entrada
            DDRC = DDRC & 0b11111110;         
        }
        else{
            //Configura como saída
            DDRC = DDRC | 0b00000001;
        }
    }

    //Configuração do A1
    if (pin == A1){
        if (dir == INPUT){
            //Configura como entrada
            DDRC = DDRC & 0b11111101;         
        }
        else{
            //Configura como saída
            DDRC = DDRC | 0b00000010;
        }
    }

    //Configuração do A2
    if (pin == A2){
        if (dir == INPUT){
            //Configura como entrada
            DDRC = DDRC & 0b11111011;         
        }
        else{
            //Configura como saída
            DDRC = DDRC | 0b00000100;
        }
    }

    //Configuração do A3
    if (pin == A3){
        if (dir == INPUT){
            //Configura como entrada
            DDRC = DDRC & 0b11110111;         
        }
        else{
            //Configura como saída
            DDRC = DDRC | 0b00001000;
        }
    }

    //Configuração do A4
    if (pin == A4){
        if (dir == INPUT){
            //Configura como entrada
            DDRC = DDRC & 0b11101111;         
        }
        else{
            //Configura como saída
            DDRC = DDRC | 0b00010000;
        }
    }    

    //Configuração do A5
    if (pin == A5){
        if (dir == INPUT){
            //Configura como entrada
            DDRC = DDRC & 0b11011111;         
        }
        else{
            //Configura como saída
            DDRC = DDRC | 0b00100000;
        }
    }
}

/***************************************************
void digitalWrite(int pin, int value)
Descrição: Escreve um valor TRUE ou FALSE 
em um determinado pino.
***************************************************/
void digitalWrite_old(int pin, int value){
    
    //Configuração do D0
    if (pin == D0){
        if (value == FALSE){
            //Configura como entrada
            PORTD = PORTD & 0b11111110;         
        }
        else{
            //Configura como saída
            PORTD = PORTD | 0b00000001;
        }
    }

    //Configuração do D13
    if (pin == D13){
        if (value == FALSE){
            //Configura como entrada
            PORTB = PORTB & 0b11011111;         
        }
        else{
            //Configura como saída
            PORTB = PORTB | 0b00100000;
        }
    }
}

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