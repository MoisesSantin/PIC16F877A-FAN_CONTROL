//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - MAIN.h***************************************/

#ifndef main_h
#define main_h

/************************************************************************************/
/*                        Variaveis Globais                                         */
/************************************************************************************/
char DadosInit = FALSE;												// Dados da eeprom iniciado

/************************************************************************************/
/*                        Fun��es                                                   */
/************************************************************************************/
void ProcessTasks(void);
void DeInitSystem(void);
void main(void);
char ProcessUARTData(void);
#endif
