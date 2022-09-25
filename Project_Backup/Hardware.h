//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - HARDWARE.h***********************************/



#ifndef Hardware_h
#define Hardware_h
#include "Fuses.h"

/************************************************************************************/
/*                        Definições                                                */
/************************************************************************************/


#define DEBOUNCE_50      		50
#define DEBOUNCE_1       		1
#define NUMERO_DE_AMOSTRAGEM 	3
#define ON               		0x01
#define OFF              		0x00
#define L_ON         			0x0F
#define L_OFF        			0x08
#define L_CLR        			0x01
#define L_L1         			0x80
#define L_L2         			0xC0
#define L_CR         			0x0F
#define L_NCR        			0x0C
#define L_CFG        			0x38
#bit  rb0              =    	portb.0
#bit  DISPLAY_CONTROL  =    	portb.7
#bit  LENA             =    	porte.1
#bit  LDAT             =    	porte.0
#byte LPORT            =    	portd
#bit    S1 			   = 		portb.0


/************************************************************************************/
/*                        Structs                                                   */
/************************************************************************************/
typedef enum 
{
   SwitchNotChange = 0x00,
   SwitchInicial,
   SwitchEEPROM,
   SwitchPlus,
   SwitchLess,
   SwitchSleepMode,
}SystemStatesSwitch;

SystemStatesSwitch StateSwitch;

typedef enum 
{
	Write = 0x01,
	Read,				
	Inicial,
	SleepMode,	
	Control,	
}SystemDado;

SystemDado ProcessFution;

typedef enum 
{
   SystemOff = 0x01,
   SystemInit,
   SystemRun,
   SystemDeInit
}SystemStates;
SystemStates CurrState;


typedef enum 
{
	DESABILITADO = 0x00,
	LINHA1e2,				
	LINHA2,	
}SystemConfLCD;

SystemConfLCD Flag_Conf_LCD;

/************************************************************************************/
/*                        Variaveis Globais                                         */
/************************************************************************************/
//char FlagSystemControl;
char TimerDebounce;											// Tempo de debounce
//char Flag_S1;												// Flag do debounce
//char SpeedyEEPROM;											// Valor de velocidade da eeprom
static char HWLCD_Init;										// Status do hardware, se foi inicializado ou não
static char HwInitState;									// Status do hardware, se foi inicializado ou não
//char SpeedyRotationLCD;

/************************************************************************************/
/*                        Funções                                                   */
/************************************************************************************/
void Trata_int_RB0(void);
void InitSystemVariables(void);
void InicializaHardware(void);


void SetProcessFution (SystemDado Dado);
void SetStateSwitch (SystemStatesSwitch Dado);
void SetSpeedyRotation(char Dado);
void SetTimerDebounce (char Dado);
void SetLCD_Init(char Dado);
void SetFlag_Conf_LCD (SystemConfLCD Dado);
void SetCurrState(SystemStates Dado);
void SetHW_I2C (char Dado);


char GetHW_I2C(void);
SystemStatesSwitch GetCurrState(void);
SystemConfLCD GetFlag_Conf_LCD(void);
char GetLCD_Init(void);
char GetTimerDebounce(void);
char GetLCD_Init(void);
char GetSpeedyRotation(void);
char GetHwInitState(void);
SystemDado GetProcessFution(void);
SystemStatesSwitch GetStateSwitch(void);


#endif
