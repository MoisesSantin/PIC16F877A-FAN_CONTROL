//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 111*********************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - EEPROM.c*************************************/

#include "Hardware.h"
#include "HardwareEEPROM.h"
#include "EEPROM.h"

#define ADDS	 		0x00

char x = OFF;

/*******************************************************************/
/* Nome da Fun��o: 	 ProcessEEPROM			                       */
/* Proposito:        Processar e plotar dados para a memoria EEPROM*/
/* Entradas:         Dado a ser gravado, Posi��o inicial e func�o  */
/* Sa�das:            Posi��o final da memoria ou Dado lido        */
/*******************************************************************/
char GetDadoEEPROM(void)
{	
	x = Read_Eeprom(ADDS);
	SetProcessFution (Read);
	SetStateSwitch(SwitchEEPROM);
	return (x);
}

void SetDadoEEPROM (char Dado)
{
	SetProcessFution (Write);
	write_Eeprom(ADDS,*Dado);
}