//**********************FACULDADE DE TECNOLOGIA DE SANTO ANDR�**************************/
//*********T�PICOS AVAN�ADOS DE PROGRAMA��O EM MICROCONTROLADORES - Prof� Weslley*******/
//*****************************Mois�s Santin   RA.: 1112027*****************************/
//************************SISTEMA DE CLIMATIZA��O - MODULAR*****************************/
//********************************MODULO - test.c***************************************/
#include "16F877a.h"
#include "regs_16f87x.h"    

 
#use delay (clock = 4000000)
#fuses xt,nowdt,noprotect,put,nobrownout,nolvp // configura��o dos fus�veis 

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                   Defini��o e inicializa��o dos port's                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ZERO_RAM

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)

#bit   DISPLAY_CONTROL   = portb.7
#bit    ICLK = portc.3
#bit    IDAT = portc.4
#bit    TIDAT = trisc.4
#bit    LENA = porte.1
#bit    LDAT = porte.0
#bit    S1 = portb.0// defini��o das entradas
#bit    S2 = portb.1// defini��o das entradas
#bit    S3 = portb.2// defini��o das entradas
#byte   LPORT = portd
/************************************************************************************/
/*                        Defini��es                                 */
/************************************************************************************/
#define L_ON   0x0F
#define L_OFF   0x08
#define L_CLR   0x01
#define L_L1   0x80
#define L_L2   0xC0
#define L_CR   0x0F      
#define L_NCR   0x0C   
#define L_CFG   0x38
/************************************************************************************/
unsigned char TimerEepromHandler;//Vari�vel de controle da frequ�ncia de leitura
unsigned char Padrao[]= "Aperte uma chave";//Vetor que carrega as mensagens        
        typedef struct
             {
               char RA [8];
               char Nome [8];
             }Aluno;
             
Aluno Integrantes[2];//Vetor do tipo Aluno (estrutura)
Aluno k[2];//Vetor do tipo Aluno (estrutura)
   char* vet; 
   unsigned char i,m,n,x;
   unsigned char d=0;

void InicializaHardware(void);
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char val);
unsigned char I2C_Read(unsigned char ack);
void I2C_Ack(unsigned char val);
unsigned char Read_Eeprom(unsigned int addr);
void Write_Eeprom(unsigned int addr, unsigned char val);
void LCD_Init(void);
void LCD_Command(unsigned char val);
void LCD_Data(unsigned char DataVal);
void LCD_String(char* str);
void LCD_Write(unsigned char val);
void Atraso_Milisegundos(unsigned int valor);
void Int_to_ASCII(unsigned int val, char* str );
void delay(void);
char Int_Struct(char d); // fun��o implementada
char GetLCD_Init(void);
void SetLCD_Init(char Dado);

//char* codetxt_to_ramtxt(const char* ctxt);

typedef enum 
{
   Write = 0x01,
   Read,            
   EEPROM,   
   SleepMode,   
   Control,   
}SystemDado;
SystemDado ProcessFution;
unsigned char ValueWriteLCD[] = "Aperte uma chave";
char  HWLCD_Init;

/*******************************************************************/
/* Nome da Fun��o:  GetProcessFution                          */
/* Proposito:         Devolvi o valor de SystemControl, ou seja    */
/*            do switch S1 sempre que solicitado                    */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
char GetProcessFution(void)
{   
   return (ProcessFution);
}
void SetProcessFution (char Dado)
{
   ProcessFution = Dado;
}

/*******************************************************************/
/* Nome da Fun��o:  Trata_Timer                                    */
/* Proposito:         Interrup��o do timer 0. A cada 1ms.            */
/* Entradas:         Nenhuma                                        */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
#int_timer0
void Trata_Timer(void)
{
   set_timer0( 5 + get_timer0());
   if(TimerEepromHandler)      TimerEepromHandler--;
}

/*******************************************************************/
/* Nome da Fun��o:  delay                                        */
/* Proposito:         Gera delay de 4 nops.                       */
/* Entradas:         Nenhuma                                        */
/* Sa�das:            Nenhuma                                        */
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
/* Nome da Fun��o:  I2C_Init                                        */
/* Proposito:         Inicializa os pinos de I2C do uC.              */
/* Entradas:         Nenhuma                                        */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void I2C_Init(void)
{
  TIDAT=0;
  ICLK=1;
  IDAT=1;
}

/*******************************************************************/
/* Nome da Fun��o:  I2C_Start                                       */
/* Proposito:         Gera condicao de start no I2C.                 */
/* Entradas:         Nenhuma                                        */
/* Sa�das:            Nenhuma                                        */
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
/* Nome da Fun��o:  I2C_Start                                       */
/* Proposito:         Gera condicao de start no I2C.                 */
/* Entradas:         Nenhuma                                        */
/* Sa�das:            Nenhuma                                        */
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
/* Nome da Fun��o:  I2C_Write                                       */
/* Proposito:         Escreve um byte atraves da I2C.                 */
/* Entradas:         unsigned char val - byte a ser escrito.        */
/* Sa�das:            Nenhuma                                        */
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
/* Nome da Fun��o:  I2C_Read                                       */
/* Proposito:         Realiza a leitura de um byte no I2C.           */
/* Entradas:         unsigned char ack - 1 -> com acknowledge       */
/*                              0 -> sem acknowledge      */
/* Sa�das:            Nenhuma                                        */
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
/* Entradas:                                              */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
void ProcessDisplay(void)                              // Precisa testa-la ainda
{   
   char Dado;
   if (GetLCD_Init() == FALSE)                              
   {
      LCD_Init();
      SetLCD_Init(TRUE);
   }
   Dado = GetProcessFution();
   switch (Dado)
   {   
      case Write:
            LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
            LCD_Command(L_L1);
         Padrao="Gravado ok";
            LCD_String(Padrao);
            LCD_Command(L_L2);
            Padrao = "INFORMACOES";
            LCD_String(Padrao);
            break;
      case Read:
            LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
            LCD_Command(L_L1);
            ValueWriteLCD = "CARREGANDO...";
            LCD_String(ValueWriteLCD);
            LCD_Command(L_L2);
            ValueWriteLCD = "DADOS ANTERIOR!";
            LCD_String(ValueWriteLCD);
            SetProcessFution(Control);
            break;
      case EEPROM:
            LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
            LCD_Command(L_L1);
            ValueWriteLCD = "OPERACAO";
            LCD_String(ValueWriteLCD);
            LCD_Command(L_L2);
            //LCD_String(GetSpeedyRotation());
            break;
      case SleepMode:
            LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
            break;
      case Control:
            LCD_Command(L_CLR);            //Aqui os dados que ser�o escritos LCD_String (o que quer escrever);
            LCD_Command(L_L1);
            ValueWriteLCD = "VELOCIDADE";
            LCD_String(ValueWriteLCD);
            LCD_Command(L_L2);
           // LCD_String(GetSpeedyRotation());
            break;
   }
}
/*******************************************************************/
/* Nome da Fun��o:  InicializaHardware                             */
/* Proposito:         Inicializa os perifericos do microcontrolador. */
/* Entradas:         Nenhuma                                        */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void InicializaHardware(void)
{
   setup_adc(ADC_OFF);
   setup_adc_ports(NO_ANALOGS);                /* AD Converter         */
   setup_psp(PSP_DISABLED);                    /* Parallel slave port   */
   setup_spi(FALSE);                           /* SPI Disabled         */
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4);    /*4M/4 = 1M -> 1M/4 = 250000             */
                                               /* 1/250000 = 4us -> 255* 4us = 1.02ms      */
   set_timer0( 5);
   setup_comparator(NC_NC_NC_NC);              /* Desliga comparadores internos         */
   setup_vref(FALSE);                           /* Tens�o de referencia  para o comparador   */
   
   PORTA = 0x00;                             // limpa PORTA
   PORTB = 0x00;                             // limpa PORTB
   PORTC = 0x00;                            // limpa PORTC
   PORTD = 0x00;                             // limpa PORTD
   PORTE = 0x00;                             // limpa PORTE
   
   set_tris_a(0b11111111);            
   set_tris_b(0b01111111);            
   set_tris_c(0b00000001);            
   set_tris_d(0b00000000);            
   set_tris_e(0b00000000);            
   
   enable_interrupts(int_timer0);
   enable_interrupts(global);
   I2C_Init();
   LCD_Init();
}

/*******************************************************************/
/* Nome da Fun��o:  Read_Eeprom                                    */
/* Proposito:         Realiza a leitura de um byte na EEPROM.        */
/* Entradas:         unsigned int addr - endereco a ser lido        */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
unsigned char Read_Eeprom(unsigned int addr)
{
  unsigned char ret;
  unsigned char ah;
  unsigned char al;

  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;

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

  I2C_Start();
  if(ah)
  {
    I2C_Write(0xA3);
  }
  else
  {
    I2C_Write(0xA1);
  }
  ret=I2C_Read(1);
  I2C_Stop();

  return ret;   
}

/*******************************************************************/
/* Nome da Fun��o:  Write_Eeprom                                   */
/* Proposito:         Realiza a escrita de um byte na EEPROM.        */
/* Entradas:         unsigned int addr - endereco a ser escrito     */
/*               unsigned char val - valor a ser escrito        */
/* Sa�das:            Nenhuma                                        */
/*******************************************************************/
void Write_Eeprom(unsigned int addr, unsigned char val)
{
  unsigned int tmp;
  unsigned char ah;
  unsigned char al;
  unsigned char nt;

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
/* Nome da Fun��o:  Int_Struct                                   */
/* Proposito: Inicializa/configura estruturas e atualiza mensagem inicial*/
/* Entradas:  char d - valor do case desejado                          */
/* Sa�das:  char d - vari�vel de controle da atualiza��o          */
/*******************************************************************/
char Int_Struct(char d)
{        
   switch(d)
   {
      case 0: //Inicializa estrutura que receber� os valores lidos na eeprom
        strcpy(k[0].Nome, "VAZIO  ");
        strcpy(k[1].Nome, "       ");
        strcpy(k[0].RA, "       ");
        strcpy(k[1].RA, "       "); 
        Break;
        
      case 1: //Copia nome e ra de cada integrante na estrutura
       strcpy(Integrantes[0].Nome, "Moises "); 
       strcpy(Integrantes[1].Nome, "Rodrigo");
       strcpy(Integrantes[0].RA, "2027   ");
       strcpy(Integrantes[1].RA, "2035   ");                
       Break;
       
      case 25: //Atualiza LCD     
       d=0;
       LCD_Command(L_CLR);
       Padrao="Aperte uma chave";
       LCD_String(Padrao);
       Break;
   }
        d++;
        return(d);
          
}
   
/*******************************************************************/
/* Nome da Fun��o:  GetLCD_Init                                    */
/* Proposito:         Flag se Hardware foi inicializado            */
/* Entradas:         Nenhuma                                       */
/* Sa�das:            Nenhuma                                      */
/*******************************************************************/
char GetLCD_Init(void)
{
   return (HWLCD_Init);
}
void SetLCD_Init(char Dado)
{
   HWLCD_Init = Dado;
}
   
/*******************************************************************/
/* Nome da Fun��o:    main                                         */
/* Proposito:      Fun��o principal.                               */
/* Entradas:      Nenhuma                                          */
/* Sa�das:         Nenhuma                                         */
/*******************************************************************/
void main(void)
{
   InicializaHardware();
   TimerEepromHandler = 0;    
     Int_Struct(1);   
     LCD_String(Padrao);
  while(true)
   {
      if(!TimerEepromHandler)
         { 
         d=Int_Struct(d); // fun��o que atualiza LCD
         if(!S1)
               { 
                for(m=0;m<2;m++)
                    {                      
                      for(i=0;i<7;i++) 
                        {  
                          n=14*m;
                          vet=&Integrantes[m].Nome[i];
                          Write_Eeprom((i+n),*vet);                          
                          k[m].Nome[i]=Read_Eeprom(i+n);                            
                          vet=&Integrantes[m].RA[i];                                      
                          Write_Eeprom((i+n+7),*vet); 
                          k[m].RA[i]=Read_Eeprom(i+n+7);                          
                        }                    
                    }
                     LCD_Command(L_CLR);
                     Padrao="Gravado";
                     LCD_String(Padrao);
               }
            else if(!S2)
               {   
               SetProcessFution (x);
               ProcessDisplay();
               x++;
                // for(m=0;m<2;m++)
                  // {  
                    // LCD_Command(L_CLR);
                    // LCD_Command(L_L1);
                    // LCD_String(k[m].Nome);                    
                    // LCD_Command(L_L2);
                    // LCD_String(k[m].RA);
                    // Atraso_Milisegundos(1000);
                  // }                
               }
            else if(!S3) //Apaga eeprom (escreve 0x00)
            {
            LCD_Command(L_CLR);
            for(i=0;i<28;i++)Write_Eeprom(i,0x00);
                d=Int_Struct(0);
                Padrao="Apagado";
                LCD_String(Padrao);
            }
            TimerEepromHandler = 100;       
          }   
   }    
 }


