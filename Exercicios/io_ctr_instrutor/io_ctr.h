#ifndef io_ctr_h
#define io_ctr_h

#include <avr/io.h>

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

BIT_PORT_REG setBIT_PORT_REG(uint16_t uiPort,
                            uint16_t  uiDdr,
                            uint16_t uiBit);
void mapPorts(void);
void pinMode(int pin, int dir);
void digitalWrite(int pin, int value);


#endif