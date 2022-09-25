//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 1112035*****************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - HARDWAREEEPROM.c*****************************/
#include "Hardware.h"
#include "HardwareEEPROM.h"

/************************************************************************************/
/*                        Defini��es                                                */
/************************************************************************************/
#bit  ICLK          =    		portc.3
#bit  IDAT          =    		portc.4
#bit  TIDAT         =    		trisc.4


/************************************************************************************/
/*                        Fun��es                                                   */
/************************************************************************************/
char I2C_Init(void);    					 							
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char val);
unsigned char I2C_Read(unsigned char ack);
void delay(void);

/*******************************************************************/
/* Nome da Fun��o:  delay                                          */
/* Proposito:         Gera delay de 4 nops.                        */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
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
/* Nome da Fun��o:  Read_Eeprom                                    */
/* Proposito:         Realiza a leitura de um byte na EEPROM.      */
/* Entradas:         unsigned int addr - endereco a ser lido       */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
unsigned char Read_Eeprom(unsigned int addr)
{
	unsigned char ret;                                                  // Variavel que Ler I2C
	unsigned char ah;                                                   // Recebi endere�o
	unsigned char al;                                                   // Recebi Dado
	if (I2C_Init())				
	{
		I2C_Init();				     								    // Fun��o implementada no HardwareEEPROM_I2C.
	}
	ah=(addr&0x0100)>>8;                                                // Valor de A0 do endere�o
	al=addr&0x00FF;                                                     // Filtro do dado 1 Byte
	
	I2C_Start();                                                        // Start I2C
	if(ah)                                                              // A0 = 1, Bloco superior da memoria 1FF
	{
	I2C_Write(0xA2);                                                    // Endere�o � 1010 (A) 0010 (A2 A1 A0 R/W) Leitura
	}
	else                                                                // Se n�o Bloco Inferior da memoria 0FF
	{
	I2C_Write(0xA0);
	}
	I2C_Write(al);                                                      // Endere�o da posi��o da memoria
	
	I2C_Start();
	if(ah)                                                              // A0 est� conectado para VCC?
	{
	I2C_Write(0xA3);                                                    // Endere�o � 1010 (A) 0011 (A2 A1 A0 R/W) Escreta
	}
	else                                                                // A0 est� conectado para TERRA?
	{
	I2C_Write(0xA1);                                                    // Endere�o � 1010 (A) 0001 (A2 A1 A0 R/W) Escreta
	}
	ret=I2C_Read(1);
	I2C_Stop();
	
	return ret;
}

/*******************************************************************/
/* Nome da Fun��o:  Write_Eeprom                                   */
/* Proposito:         Realiza a escrita de um byte na EEPROM.      */
/* Entradas:         unsigned int addr - endereco a ser escrito    */
/*               unsigned char val - valor a ser escrito           */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
void Write_Eeprom(unsigned int addr, unsigned char val)
{
	unsigned int tmp;
	unsigned char ah;
	unsigned char al;
	unsigned char nt;
	if (I2C_Init() != TRUE)				
	{
		I2C_Init();				     									// Fun��o implementada no HardwareEEPROM_I2C.
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
/* Nome da Fun��o:  I2C_Init                                       */
/* Proposito:         Inicializa os pinos de I2C do uC.            */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
char I2C_Init(void)
{
  TIDAT=0;                                      // trisc.4 - Configura��o como sa�da
  ICLK=1;                                       // portc.3 - SCL
  IDAT=1;                                       // ports.4 - SDA
  return (TRUE);
}

/*******************************************************************/
/* Nome da Fun��o:  I2C_Start                                      */
/* Proposito:         Gera condicao de start no I2C.               */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
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
/* Nome da Fun��o:  I2C_Start                                      */
/* Proposito:         Gera condicao de start no I2C.               */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
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
/* Nome da Fun��o:  I2C_Write                                      */
/* Proposito:         Escreve um byte atraves da I2C.              */
/* Entradas:         unsigned char val - byte a ser escrito.       */
/* Sa�das:            Nenhuma                                      */
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
/* Nome da Fun��o:  I2C_Read                                       */
/* Proposito:         Realiza a leitura de um byte no I2C.         */
/* Entradas:         unsigned char ack - 1 -> com acknowledge      */
/*                              0 -> sem acknowledge               */
/* Sa�das:            Nenhuma                                      */
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