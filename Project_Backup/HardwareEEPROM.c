//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZAÇÃO - MODULAR*****************************/
//********************************MODULO - HARDWAREEEPROM.c*****************************/
#include "Hardware.h"
#include "HardwareEEPROM.h"

/************************************************************************************/
/*                        Definições                                                */
/************************************************************************************/
#bit  ICLK          =    		portc.3
#bit  IDAT          =    		portc.4
#bit  TIDAT         =    		trisc.4


/************************************************************************************/
/*                        Funções                                                   */
/************************************************************************************/  					 							
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char val);
unsigned char I2C_Read(unsigned char ack);
void delay(void);

/*******************************************************************/
/* Nome da Função:  delay                                        */
/* Proposito:         Gera delay de 4 nops.                       */
/* Entradas:         Nenhuma                                        */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
void delay(void)
{
#asm
   NOP  
   NOP  
   NOP  
   NOP 
#endasm 
}

/*******************************************************************/
/* Nome da Função:  I2C_Init                                        */
/* Proposito:         Inicializa os pinos de I2C do uC.              */
/* Entradas:         Nenhuma                                        */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
void I2C_Init(void)
{
  TIDAT=0;
  ICLK=1;
  IDAT=1;
  SetHW_I2C (TRUE);
}

/*******************************************************************/
/* Nome da Função:  I2C_Start                                       */
/* Proposito:         Gera condicao de start no I2C.                 */
/* Entradas:         Nenhuma                                        */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
void I2C_Start(void)
{
  ICLK=1;
  IDAT=1;
  delay();
  IDAT=0;
  delay();
}
/*******************************************************************/
/* Nome da Função:  I2C_Start                                       */
/* Proposito:         Gera condicao de start no I2C.                 */
/* Entradas:         Nenhuma                                        */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
void I2C_Stop(void)
{
  ICLK=1;
  IDAT=0;
  delay();
  IDAT=1;
  delay();
}
/*******************************************************************/
/* Nome da Função:  I2C_Write                                       */
/* Proposito:         Escreve um byte atraves da I2C.                 */
/* Entradas:         unsigned char val - byte a ser escrito.        */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
void I2C_Write(unsigned char val)
{
  char i;
  ICLK=0;
  for(i=0;i<8;i++)      
  {
    IDAT=((val>>(7-i))& 0x01);
    ICLK=1;
    delay();
    ICLK=0;
  }   
  IDAT=1;
  delay();
  ICLK=1;
  delay();
  ICLK=0;
}
/*******************************************************************/
/* Nome da Função:  I2C_Read                                       */
/* Proposito:         Realiza a leitura de um byte no I2C.           */
/* Entradas:         unsigned char ack - 1 -> com acknowledge       */
/*                              0 -> sem acknowledge      */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
unsigned char I2C_Read(unsigned char ack)
{
  char i;
  unsigned char ret=0;

  ICLK=0;
  TIDAT=1;
  IDAT=1;
  for(i=0;i<8;i++)
  {
    ICLK=1;
    delay();
    ret|=(IDAT<<(7-i));
    ICLK=0;
  }
  TIDAT=0;
  if(ack) 
    IDAT=0;
  else
    IDAT=1;
  delay();
  ICLK=1;
  delay();
  ICLK=0;

  return ret;
}

/*******************************************************************/
/* Nome da Função:  Atraso_Milisegundos                            */
/* Proposito:         Gera atraso em milisegundos.                 */
/* Entradas:         unsigned int valor - tempo desejado em ms      */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
void Atraso_Milisegundos(unsigned int valor)
{
unsigned int  i;
unsigned char j;

 for (i =0; i< valor; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
#asm
   NOP
   NOP
   NOP
   NOP
   NOP
#endasm;
   }
 }
}
/*******************************************************************/
/* Nome da Função:  LCD_Write                                       */
/* Proposito:         Realiza a leitura de um byte no I2C.           */
/* Entradas:         unsigned char val - valor a ser enviado para o */
/*                              display.               */
/* Saídas:            Nenhuma                                        */
/*******************************************************************/
void LCD_Write(unsigned char val)
{
  LPORT = val;
}