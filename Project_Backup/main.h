//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - MAIN.h***************************************/

#ifndef main_h
#define main_h

/************************************************************************************/
/*                        Variaveis Globais                                         */
/************************************************************************************/
char DadosInit = FALSE;												// Dados da eeprom iniciado

/************************************************************************************/
/*                        Funções                                                   */
/************************************************************************************/
void ProcessTasks(void);
void DeInitSystem(void);
void main(void);
char ProcessUARTData(void);
#endif
