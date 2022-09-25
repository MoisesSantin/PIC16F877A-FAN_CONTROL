//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDRÉ**************************/
//*********TÓPICOS AVANÇADOS DE PROGRAMAÇÃO EM MICROCONTROLADORES - Profº Weslley*******/
//*****************************Moisés Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 1112035*****************************/
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
char I2C_Init(void);    					 							
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char val);
unsigned char I2C_Read(unsigned char ack);
void delay(void);

/*******************************************************************/
/* Nome da Função:  delay                                          */
/* Proposito:         Gera delay de 4 nops.                        */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
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
/* Nome da Função:  Read_Eeprom                                    */
/* Proposito:         Realiza a leitura de um byte na EEPROM.      */
/* Entradas:         unsigned int addr - endereco a ser lido       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
unsigned char Read_Eeprom(unsigned int addr)
{
	unsigned char ret;                                                  // Variavel que Ler I2C
	unsigned char ah;                                                   // Recebi endereço
	unsigned char al;                                                   // Recebi Dado
	if (I2C_Init())				
	{
		I2C_Init();				     								    // Função implementada no HardwareEEPROM_I2C.
	}
	ah=(addr&0x0100)>>8;                                                // Valor de A0 do endereço
	al=addr&0x00FF;                                                     // Filtro do dado 1 Byte
	
	I2C_Start();                                                        // Start I2C
	if(ah)                                                              // A0 = 1, Bloco superior da memoria 1FF
	{
	I2C_Write(0xA2);                                                    // Endereço é 1010 (A) 0010 (A2 A1 A0 R/W) Leitura
	}
	else                                                                // Se não Bloco Inferior da memoria 0FF
	{
	I2C_Write(0xA0);
	}
	I2C_Write(al);                                                      // Endereço da posição da memoria
	
	I2C_Start();
	if(ah)                                                              // A0 está conectado para VCC?
	{
	I2C_Write(0xA3);                                                    // Endereço é 1010 (A) 0011 (A2 A1 A0 R/W) Escreta
	}
	else                                                                // A0 está conectado para TERRA?
	{
	I2C_Write(0xA1);                                                    // Endereço é 1010 (A) 0001 (A2 A1 A0 R/W) Escreta
	}
	ret=I2C_Read(1);
	I2C_Stop();
	
	return ret;
}

/*******************************************************************/
/* Nome da Função:  Write_Eeprom                                   */
/* Proposito:         Realiza a escrita de um byte na EEPROM.      */
/* Entradas:         unsigned int addr - endereco a ser escrito    */
/*               unsigned char val - valor a ser escrito           */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
void Write_Eeprom(unsigned int addr, unsigned char val)
{
	unsigned int tmp;
	unsigned char ah;
	unsigned char al;
	unsigned char nt;
	if (I2C_Init() != TRUE)				
	{
		I2C_Init();				     									// Função implementada no HardwareEEPROM_I2C.
	}
	tmp=val;
	ah=(addr&0x0100)>>8;
	al=addr&0x00FF;
	nt=0;
	
	do
	{
	I2C_Start();
	if(ah)
	{
		I2C_Write(0xA2);
	}
	else
	{
		I2C_Write(0xA0);
	}
	I2C_Write(al);
	I2C_Write(tmp);
	I2C_Stop();
	
	nt++;
	}
	while((tmp != Read_Eeprom(addr))&&(nt < 10));
}
/*******************************************************************/
/* Nome da Função:  I2C_Init                                       */
/* Proposito:         Inicializa os pinos de I2C do uC.            */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
char I2C_Init(void)
{
  TIDAT=0;                                      // trisc.4 - Configuração como saída
  ICLK=1;                                       // portc.3 - SCL
  IDAT=1;                                       // ports.4 - SDA
  return (TRUE);
}

/*******************************************************************/
/* Nome da Função:  I2C_Start                                      */
/* Proposito:         Gera condicao de start no I2C.               */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
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
/* Nome da Função:  I2C_Start                                      */
/* Proposito:         Gera condicao de start no I2C.               */
/* Entradas:         Nenhuma                                       */
/* Saídas:            Nenhuma                                      */
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
/* Nome da Função:  I2C_Write                                      */
/* Proposito:         Escreve um byte atraves da I2C.              */
/* Entradas:         unsigned char val - byte a ser escrito.       */
/* Saídas:            Nenhuma                                      */
/*******************************************************************/
void I2C_Write(unsigned char val)
{
  char y;
  ICLK=0;
  for(y = 0; y < 8 ; y++)
  {
    IDAT=((val>>(7-y))& 0x01);
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
/* Proposito:         Realiza a leitura de um byte no I2C.         */
/* Entradas:         unsigned char ack - 1 -> com acknowledge      */
/*                              0 -> sem acknowledge               */
/* Saídas:            Nenhuma                                      */
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