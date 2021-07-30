//*****************************************************************************
//***		DRIVEADC.H	   														***
//*****************************************************************************

#ifndef		__DRIVEADC_H_
#define 	__DRIVEADC_H_

#define PRECISAO 500 / 1023   // Podemos definir a precisão do AD alterando a
                              // quantidades de zeros nessa variável.

void
fnInitAdc(void);

int
fnLerAdc(void);

void
fnLerTensao(void);

#endif
