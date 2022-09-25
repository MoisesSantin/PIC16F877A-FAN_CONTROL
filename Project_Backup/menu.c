//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - MENU.c***************************************/
#include "Hardware.h"
#include "menu.h"

#bit  S2 			= 			portb.1    
#bit  S3 			= 			portb.2 
/*******************************************************************/
/* Nome da Função: 	 ProcessMenu			                       */
/* Proposito:        Processar e plotar dados do menu              */
/* Entradas:         Nenhuma  									   */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
void ProcessMenu(void)
{	
	if (!S1) SetCurrState(SystemDeInit);	
	else if(!S2) 
	{
		SetStateSwitch(SwitchLess);
	}
	else if (!S3) 
	{
		SetStateSwitch(SwitchPlus);
	}
}