//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 1112035*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - HARDWAREEEPROM.h*****************************/

#ifndef HardwareEEPROM_h
#define HardwareEEPROM_h

/************************************************************************************/
/*                        Funções                                                   */
/************************************************************************************/
unsigned char Read_Eeprom(unsigned int addr);
void Write_Eeprom(unsigned int addr, unsigned char val);

#endif