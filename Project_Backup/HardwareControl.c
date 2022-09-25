//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - HARDWARECONTROL.c****************************/
#include "Hardware.h"
#include "HardwareControl.h"

/************************************************************************************/
/*                        Definições                                                */
/************************************************************************************/
#define MININUM  				102				// 20% de Duty, escopo do programa
#define MAXIMO   				204				// 100% de Duty, maxima do sistema				
#define INICIAL   				102				// 30% de Duty, inicia o programa.
#define LOWPOWER   				0				// 0% de Duty, Programa desligado
#define DUTYCYCLO   			51				// 13,3 % de duty para assim termos 6 velocidades apartir do minimo)
#define VALUECONVERTPORCENT     0,3922


/*******************************************************************/
/* Nome da Função:   ProcessMotorControl                           */
/* Proposito:      Controla o Hardware do ventilador               */
/* Entradas:       Nenhuma                                         */
/* Saídas:         Nenhuma                                         */
/*******************************************************************/
void ProcessMotorControl(void)
{	
	char Auxiliar, Auxiliar2 =OFF;
	Auxiliar2 = GetStateSwitch();
	switch (Auxiliar2)
	{
		case SwitchNotChange:
			break;
			
		case SwitchInicial:
			SetSpeedyRotation (INICIAL);
			SetStateSwitch (SwitchNotChange);
			SetProcessFution(Control);
			break;
			
		case SwitchEEPROM:
			SetStateSwitch (SwitchNotChange);
			break;
			
		case SwitchPlus:
			Auxiliar = GetSpeedyRotation();
			if (Auxiliar <= MAXIMO)
			{
				Auxiliar += DUTYCYCLO;
				SetSpeedyRotation(Auxiliar);
				SetStateSwitch (SwitchNotChange);
				SetProcessFution(Control);
				SetFlag_Conf_LCD (LINHA2);
			}
			break;
			
		case SwitchLess:
		    Auxiliar = GetSpeedyRotation();
			if (Auxiliar >= MININUM)
			{
				Auxiliar -= DUTYCYCLO;
				SetSpeedyRotation(Auxiliar);
				SetStateSwitch (SwitchNotChange);
				SetProcessFution(Control);
				SetFlag_Conf_LCD (LINHA2);
			}
			break; 
			
		case SwitchSleepMode:
			SetSpeedyRotation(LOWPOWER);
			//SetStateSwitch (SwitchEEPROM);
			SetProcessFution(SleepMode);
			break; 
			
	}
	set_pwm2_duty(GetSpeedyRotation());	
}


