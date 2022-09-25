//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - HARDWAREEEPROM.h*****************************/

#ifndef HardwareEEPROM_h
#define HardwareEEPROM_h

/************************************************************************************/
/*                        Fun��es                                                   */
/************************************************************************************/
unsigned char Read_Eeprom(unsigned int addr);
void Write_Eeprom(unsigned int addr, unsigned char val);
void I2C_Init(void);  

#endif