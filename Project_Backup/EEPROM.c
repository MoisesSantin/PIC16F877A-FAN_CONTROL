//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - EEPROM.c*************************************/

#include "Hardware.h"
#include "HardwareEEPROM.h"
#include "EEPROM.h"

#define ADDS	 		0

char x = OFF;

/*******************************************************************/
/* Nome da Fun��o: 	 ProcessEEPROM			                       */
/* Proposito:        Processar e plotar dados para a memoria EEPROM*/
/* Entradas:         Dado a ser gravado, Posi��o inicial e func�o  */
/* Sa�das:            Posi��o final da memoria ou Dado lido        */
/*******************************************************************/
void GetDadoEEPROM(void)
{	
	x = Read_Eeprom(ADDS);
	SetSpeedyRotation(x);
	SetProcessFution (Read);
	SetStateSwitch(SwitchEEPROM);
}

void SetDadoEEPROM (void)
{
	if (GetHW_I2C() != TRUE) I2C_Init();
	x = GetSpeedyRotation();
	write_Eeprom(ADDS,x);
	SetProcessFution (Write);
	
}