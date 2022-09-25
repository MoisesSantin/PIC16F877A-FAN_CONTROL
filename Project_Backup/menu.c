//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - MENU.c***************************************/
#include "Hardware.h"
#include "menu.h"

#bit  S2 			= 			portb.1    
#bit  S3 			= 			portb.2 
/*******************************************************************/
/* Nome da Fun��o: 	 ProcessMenu			                       */
/* Proposito:        Processar e plotar dados do menu              */
/* Entradas:         Nenhuma  									   */
/* Sa�das:            Nenhuma                                      */
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