//*****************************************************************************
//***		DRIVEADC.H	   														***
//*****************************************************************************

#ifndef		__DRIVEADC_H_
#define 	__DRIVEADC_H_

#include <avr/io.h>

#define PRECISAO 500 / 1023   // Podemos definir a precis�o do AD alterando a
                              // quantidades de zeros nessa vari�vel.

void
fnInitAdc(void);

int
fnLerAdc(uint8_t pin);

int
fnLerTensao(uint8_t pin);

#endif
