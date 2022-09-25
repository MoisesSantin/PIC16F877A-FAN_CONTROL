//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 1112035*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - MAIN.c***************************************/

#include "Hardware.h"
#include "display.h"
#include "HardwareControl.h"
#include "menu.h"
#include "EEPROM.h"
#include "main.h"

/*******************************************************************/
/* Nome da Função:    main                                         */
/* Proposito:      Função principal.                               */
/* Entradas:       Nenhuma                                         */
/* Saídas:         Nenhuma                                         */
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
            if (!S1) SetCurrState(SystemInit);
			break;
			
         case SystemInit:				
            if (GetHwInitState() == FALSE)	InicializaHardware();
			ProcessDisplay(); 
			SetFlag_Conf_LCD (LINHA1e2);
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
/* Nome da Função:  ProcessTasks                                   */
/* Proposito:    Processa Tarefas do programa ligado               */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
void ProcessTasks(void)
{   
      if (DadosInit == TRUE)					
      {	
		char dado;
		dado = GetDadoEEPROM();
		SetSpeedyRotation (dado);				
		ProcessMotorControl();
		ProcessDisplay();
		DadosInit = FALSE;
	  }	
      ProcessMenu();
	  ProcessMotorControl(); 
      ProcessDisplay();         
}

/*******************************************************************/
/* Nome da Função:  DeInitSystem                                   */
/* Proposito:    Processa Tarefas do programa ao ser ligado        */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
void DeInitSystem(void)
{   
   char dado;
   dado = GetSpeedyRotation();
   SetDadoEEPROM(dado);
   SetStateSwitch (SwitchSleepMode);
   ProcessMotorControl();					
   ProcessDisplay();
   DadosInit = TRUE;									
}



