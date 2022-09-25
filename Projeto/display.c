//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//*****************************Rodrigo Medrano RA.: 111*********************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - DISPLAY**************************************/
#include "Hardware.h"
#include "display.h"


void LCD_Data(unsigned char DataVal);
void LCD_Command(unsigned char val);
void LCD_String(char* str);
void Atraso_Milisegundos(unsigned int valor);
void LCD_Write(unsigned char val);
void LCD_Init(void);

	char LCD = OFF;
	char Dado = 0;
	unsigned char ValueWriteLCD[] = "Aperte uma chave";
	unsigned char Padrao[]= "Aperte uma chave";//Vetor que carrega as mensagens     

/*******************************************************************/
/* Nome da Fun��o:  Atraso_Milisegundos                            */
/* Proposito:         Gera atraso em milisegundos.                 */
/* Entradas:         unsigned int valor - tempo desejado em ms      */
/* Sa�das:            Nenhuma                                        */
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
/* Nome da Fun��o:  LCD_Write                                       */
/* Proposito:         Realiza a leitura de um byte no I2C.           */
/* Entradas:         unsigned char val - valor a ser enviado para o */
/*                              display.               */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void LCD_Write(unsigned char val)
{
  LPORT = val;
}
/*******************************************************************/
/* Nome da Fun��o:  LCD_Command                                     */
/* Proposito:         Envia comando de controle do display.          */
/* Entradas:         unsigned char val - comando para o display.    */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void LCD_Command(unsigned char val)
{
   LENA = 1;
   LCD_Write(val);
   LDAT=0;
   Atraso_Milisegundos(3);
   LENA=0;
   Atraso_Milisegundos(3);
   LENA=1;
}
/*******************************************************************/
/* Nome da Fun��o:  LCD_Data                                     */
/* Proposito:         Envia dados para o display.                    */
/* Entradas:         unsigned char DataVal - dados a serem enviados */
/*                                 para o display.        */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void LCD_Data(unsigned char DataVal)
{
   LENA=1;
   LCD_Write(DataVal);
   LDAT=1;
   Atraso_Milisegundos(3);
   LENA=0;
   Atraso_Milisegundos(3);
   LENA=1;
}
/*******************************************************************/
/* Nome da Fun��o:  LCD_Init                                     */
/* Proposito:         Inicializa o display.                          */
/* Entradas:         Nenhuma                                        */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void LCD_Init(void)
{
   LENA=0;
   LDAT=0;
   Atraso_Milisegundos(20);
   LENA=1;
   
   LCD_Command(L_CFG);
   Atraso_Milisegundos(5);
   LCD_Command(L_CFG);
   Atraso_Milisegundos(1);
   LCD_Command(L_CFG); //configura
   LCD_Command(L_OFF);
   LCD_Command(L_ON); //liga
   LCD_Command(L_CLR); //limpa
   LCD_Command(L_CFG); //configura
   LCD_Command(L_L1);
   SetLCD_Init(TRUE);
}
/*******************************************************************/
/* Nome da Fun��o:  LCD_String                                     */
/* Proposito:         Envia string para o display.                   */
/* Entradas:         char* str - ponteiro para a string origem.     */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void LCD_String(char* str)
{
 unsigned char i=0;
  
 while(str[i] != 0 )
 {
   LCD_Data(str[i]);
   i++;
 }  
}
/*******************************************************************/
/* Nome da Fun��o:  ProcessDisplay                                 */
/* Proposito:         Plotagem de dados para Display               */
/* Entradas:         										       */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
void ProcessDisplay(void)										// Precisa testa-la ainda
{	
	if (GetLCD_Init() == FALSE)										
	{
		LCD_Init();
		SetLCD_Init(TRUE);
	}
	Dado = 0;
	switch (GetProcessFution())
	{	
		case Write:
				strcpy(Padrao, "SALVANDO..."); 
				LCD_String(Padrao);
				LCD_Command(L_L2);
				strcpy(Padrao, "INFORMACOES");
				LCD_String(Padrao);
				break;
				
		case Read:
				LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
				LCD_Command(L_L1);
				strcpy(Padrao, "CARREGANDO...");
				LCD_String(Padrao);
				LCD_Command(L_L2);
				strcpy(Padrao, "DADOS ANTERIOR!");
				LCD_String(Padrao);
				SetProcessFution(Inicial);
				break;
				
		case Inicial:
				LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
				LCD_Command(L_L1);
				strcpy(Padrao, "SISTEMA ON");
				LCD_String(Padrao);
				LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
				LCD_Command(L_L1);
				strcpy(Padrao, "VELOCIDADE");
				LCD_String(Padrao);
				LCD_Command(L_L2);
				strcpy(Padrao, "Velocidade 30%");
				LCD_String(Padrao);
				break;
				
				
		case SleepMode:
				LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
				break;
				
		case Control:
				if(GetFlag_Conf_LCD() == LINHA2)
				{
					LCD_Command(0xca);
					Dado = GetSpeedyRotationLCD();
					switch (Dado)
					{
						case 51:strcpy(Padrao, " 20 % ");
							Break;              
						case 102:strcpy(Padrao, " 40 % ");
							Break;             
						case 153:strcpy(Padrao, " 60 % ");
							Break;               
						case 204:strcpy(Padrao, " 80 % ");;
							Break;              
						case 255:strcpy(Padrao, " 100 % ");;
							Break;        
					}
					LCD_String(Padrao);
					SetFlag_Conf_LCD (DESABILITADO);
				}
				break;
	}
}
