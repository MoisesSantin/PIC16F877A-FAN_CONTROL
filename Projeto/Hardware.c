//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 1112035*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - HARDWARE.c***********************************/

#include "Hardware.h"



/************************************************************************************/
/*                        Funções                                                   */
/************************************************************************************/
char SpeedyRotation;

/*******************************************************************/
/* Nome da Função:  Trata_int_RB0                                  */
/* Proposito:         Interrupção do S1                            */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
// #int_ext
// void Trata_int_RB0(void)
// {   
	// TimerDebounce = DEBOUNCE_50;
	// disable_interrupts(int_ext);
// }


/*******************************************************************/
/* Nome da Função:  Trata_Timer                                    */
/* Proposito:         Interrupção do timer 0. A cada 1ms.          */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
#int_timer0
void Trata_Timer(void)
{
   set_timer0( 5 + get_timer0());
   if (TimerDebounce)      TimerDebounce --;
}

/*******************************************************************/
/* Nome da Função:  GetProcessFution                          */
/* Proposito:         Devolvi o valor de SystemControl, ou seja    */
/*            do switch S1 sempre que solicitado              	   */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
char GetTimerDebounce(void)
{	
	return (TimerDebounce);
}
void SetTimerDebounce (char Dado)
{
	TimerDebounce = Dado;
}

/*******************************************************************/
/* Nome da Função:  GetProcessFution                          */
/* Proposito:         Devolvi o valor de SystemControl, ou seja    */
/*            do switch S1 sempre que solicitado              	   */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
SystemConfLCD GetFlag_Conf_LCD(void)
{	
	return (Flag_Conf_LCD);
}
void SetFlag_Conf_LCD (SystemConfLCD Dado)
{
	Flag_Conf_LCD = Dado;
}


SystemStates GetCurrState(void)
{
	return (CurrState);
}

void SetCurrState(SystemStates Dado)
{
	CurrState = Dado;
}

/*******************************************************************/
/* Nome da Função:  GetProcessFution                          */
/* Proposito:         Devolvi o valor de SystemControl, ou seja    */
/*            do switch S1 sempre que solicitado              	   */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
SystemDado GetProcessFution(void)
{	
	return (ProcessFution);
}
void SetProcessFution (SystemDado Dado)
{
	ProcessFution = Dado;
}
/*******************************************************************/
/* Nome da Função:  GetStateSwitch                          */
/* Proposito:         Devolvi o valor de SystemControl, ou seja    */
/*            do switch S1 sempre que solicitado              	   */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
char GetStateSwitch(void)
{	
	return (StateSwitch);
}
void SetStateSwitch(char Dado)
{
	StateSwitch = Dado;
}

char GetSpeedyRotation(void)
{
	return (SpeedyRotation);
}

void SetSpeedyRotation(char Dado)
{
	SpeedyRotation = Dado;
}
/*******************************************************************/
/* Nome da Função:  GetLCD_Init                                    */
/* Proposito:         Flag se Hardware foi inicializado            */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
char GetLCD_Init(void)
{
   return (HWLCD_Init);
}
void SetLCD_Init(char Dado)
{
	HWLCD_Init = Dado;
}

/*******************************************************************/
/* Nome da Função:  HwInitVariables                                */
/* Proposito:         Inicializa variaveis                         */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/

void InitSystemVariables(void)                  					// Escopo main.c
{
   HwInitState   = FALSE;											// Flag da inicialização do Hardaware, main.c e Hardware.c
   HWLCD_Init = FALSE;												// Flag da inicialização do Hardware do LCD, display.c
   TimerDebounce = OFF;												// Tempo de debounce para o S1
   SetStateSwitch (SwitchInicial);										// Seleção de comando para o controle, inicial com o Padrão
   SetProcessFution(Inicial);											// Variavel que indica qual o modulo está processando
   Flag_S1 = OFF;													// Flag do debounce
   SetLCD_Init(FALSE);
   SetSpeedyRotation(OFF);
   SetCurrState(SystemOff);
}

/*******************************************************************/
/* Nome da Função:  InicializaHardware                             */
/* Proposito:         Inicializa os perifericos do microcontrolador*/
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
void InicializaHardware(void)
{
   setup_adc(ADC_OFF);
   setup_adc_ports(NO_ANALOGS);               						 /* AD Converter         */
   setup_psp(PSP_DISABLED);                    						 /* Parallel slave port   */
   setup_spi(FALSE);                           						 /* SPI Disabled         */
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4);    						 /*4M/4 = 1M -> 1M/4 = 250000             */
																	 /* 1/250000 = 4us -> 255* 4us = 1.02ms      */
   set_timer0(5);
   setup_comparator(NC_NC_NC_NC);              						 /* Desliga comparadores internos         */
   setup_vref(FALSE);                           					 /* Tensão de referencia  para o comparador   */
   setup_timer_2(T2_DIV_BY_4,250,1);								 //bloco PWM trabalha no timer 2, precisa configurar ele PAGINA 212 DO LIVRO E XEROX
   setup_ccp2(ccp_pwm);                     						 //pagina 218 livro, usa os dois blocos
   ext_int_edge(H_to_L);                   						 	// Configura interrupção para borda de subida
   
   PORTA = 0x00;                                					 // limpa PORTA
   PORTB = 0x00;                                					 // limpa PORTB
   PORTC = 0x00;                               						 // limpa PORTC
   PORTD = 0x00;                               						 // limpa PORTD
   PORTE = 0x00;                                					 // limpa PORTE
   
   set_tris_a(0b11111111);            
   set_tris_b(0b01111111);            
   set_tris_c(0b00000001);            
   set_tris_d(0b00000000);            
   set_tris_e(0b00000000);            
   
    enable_interrupts(int_timer0);									 // Habilita interrupção do Timer0
   // enable_interrupts (int_ext);										 // Habilita interrupção externa
   enable_interrupts(global);										 // Habilita interrupção Global
   HwInitState = TRUE;												 // Sinaliza que o Hardware fui inicializado
   SetProcessFution(Inicial);
}

/*******************************************************************/
/* Nome da Função:  GetHwInitState                                 */
/* Proposito:         Flag se Hardware foi inicializado            */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
char GetHwInitState(void)
{
   return (HwInitState);
}


