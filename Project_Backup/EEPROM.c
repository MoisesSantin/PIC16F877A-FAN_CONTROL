//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - EEPROM.c*************************************/

#include "Hardware.h"
#include "HardwareEEPROM.h"
#include "EEPROM.h"

#define ADDS	 		0

char x = OFF;

/*******************************************************************/
/* Nome da Função: 	 ProcessEEPROM			                       */
/* Proposito:        Processar e plotar dados para a memoria EEPROM*/
/* Entradas:         Dado a ser gravado, Posição inicial e funcão  */
/* Saídas:            Posição final da memoria ou Dado lido        */
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