//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 111*********************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - EEPROM.c*************************************/

#include "Hardware.h"
#include "HardwareEEPROM.h"
#include "EEPROM.h"

#define ADDS	 		0x00

char x = OFF;

/*******************************************************************/
/* Nome da Função: 	 ProcessEEPROM			                       */
/* Proposito:        Processar e plotar dados para a memoria EEPROM*/
/* Entradas:         Dado a ser gravado, Posição inicial e funcão  */
/* Saídas:            Posição final da memoria ou Dado lido        */
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