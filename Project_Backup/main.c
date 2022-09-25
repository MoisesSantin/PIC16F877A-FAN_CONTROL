//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - MAIN.c***************************************/

#include "Hardware.h"
#include "display.h"
#include "HardwareControl.h"
#include "menu.h"
#include "EEPROM.h"
#include "main.h"

/*******************************************************************/
/* Nome da Fun��o:    main                                         */
/* Proposito:      Fun��o principal.                               */
/* Entradas:       Nenhuma                                         */
/* Sa�das:         Nenhuma                                         */
/*******************************************************************/
void main(void)
{
char dado;
InitSystemVariables();
while(TRUE)				
   {				
      switch (GetCurrState())				
      {				
         case SystemOff: 			
            if (!S1) 
			{
				SetCurrState(SystemInit);
				SetProcessFution(Inicial);
			}
			break;
			
         case SystemInit:				
            if (GetHwInitState() == FALSE)	InicializaHardware();
			ProcessDisplay();
            SetCurrState(SystemRun);
            break;	
			
         case SystemRun:				
            ProcessTasks();					
            break;				

         case SystemDeInit:
            DeInitSystem();
			SetCurrState(SystemOff);
            break;				
      }
      
   }
}

/*******************************************************************/
/* Nome da Fun��o:  ProcessTasks                                   */
/* Proposito:    Processa Tarefas do programa ligado               */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
void ProcessTasks(void)
{   
      if (DadosInit == TRUE)					
      {	
		char dado;
		GetDadoEEPROM();				
		ProcessMotorControl();
		ProcessDisplay();
		DadosInit = FALSE;
	  }	
      ProcessMenu();
	  ProcessMotorControl(); 
      ProcessDisplay();         
}

/*******************************************************************/
/* Nome da Fun��o:  DeInitSystem                                   */
/* Proposito:    Processa Tarefas do programa ao ser ligado        */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
void DeInitSystem(void)
{   
   SetDadoEEPROM();
   ProcessDisplay();
   SetStateSwitch (SwitchSleepMode);
   ProcessMotorControl();					
   ProcessDisplay();
   DadosInit = TRUE;									
}



