//*****************************************************************************
//***		TELAS_SYS.H														***
//*****************************************************************************

#ifndef		__TELAS_SYS_H_
#define		__TELAS_SYS_H_

void
fnWrLcd_P(int msg);

void
fnWrUsart_P(int msg);

void
fnLoadCmd_P(int msg);

void
fnTelaApresentacao(void);

void
fnTelaProgramacao(void);

void
fnTelaLeituraTecla(void);

void
fnTelaAquisicaoTensao(void);

void
fnTelaLinhaComando(void);

void
fnTelaMonitorPrincipal(void);

void
fnTelaErroComando(void);

void
fnTelaEstadoPrincipal(void);



#endif
