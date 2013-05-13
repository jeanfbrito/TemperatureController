
/*
BIBLIOTECA PADRÃO PARA CUSCOPIC
Desenvolvida para PICs famílias 16 ou 18 de 28 ou 40 pinos.
Autor: Daniel Corteletti
Desenvolvido em agosto de 2007
Revisão em setembro 2007
Revisão em novembro 2008
   --> Adição de timeout (mediante variável global de configuração) para função cusco_readkbd()
   --> Variável global cusco_readkbd_timeout c/ valor padrão 0
   --> Adição de rotinas de gravação e leitura da eeprom em 16 e 32 bits.

*/

#define RELE1 pin_e0
#define RELE2 pin_e1
#define BUZZER pin_e2
#define C0 pin_c0
#define C1 pin_c1
#define C2 pin_c2
#define C3 pin_c3
#define C4 pin_c4
#define C5 pin_c5
#define C6 pin_c6
#define C7 pin_c7
#define D0 pin_d0
#define D1 pin_d1
#define D2 pin_d2
#define D3 pin_d3
#define D4 pin_d4
#define D5 pin_d5
#define D6 pin_d6
#define D7 pin_d7
#define A0 pin_a0
#define A1 pin_a1
#define A2 pin_a2
#define A3 pin_a3
#define A4 pin_a4
#define A5 pin_a5


/*
*********************************************************************************
FUNCOES DE TECLADO
Baseada no layout da CUSCO IHM

B7----[ ]---[ ]---[ ]
       |     |     |
B5----[ ]---[ ]---[ ]
       |     |     |
B3----[ ]---[ ]---[ ]
       |     |     |
B2----[ ]---[ ]---[ ]
       |     |     |
       |     |     |
       B6    B4   B1

esta função retorna o código da tecla pressionada, conforme a seguinte tabela :

00h - TECLA 0 PRESSIONADA              01h - TECLA 1 PRESSIONADA              02h - TECLA 2 PRESSIONADA
03h - TECLA 3 PRESSIONADA              04h - TECLA 4 PRESSIONADA              05h - TECLA 5 PRESSIONADA
06h - TECLA 6 PRESSIONADA              07h - TECLA 7 PRESSIONADA              08h - TECLA 8 PRESSIONADA
09h - TECLA 9 PRESSIONADA              10h - TECLA * PRESSIONADA              11h - TECLA # PRESSIONADA
FFh - NENHUMA TECLA PRESSIONADA
*/
#define KBD_NADA      0xff
#define KBD_0         0x00
#define KBD_1         0x01
#define KBD_2         0x02
#define KBD_3         0x03
#define KBD_4         0x04
#define KBD_5         0x05
#define KBD_6         0x06
#define KBD_7         0x07
#define KBD_8         0x08
#define KBD_9         0x09
#define KBD_ASTERISCO 0x10
#define KBD_SUSTENIDO 0x11

#define TECLA_NADA    cusco_tecla_press(KBD_NADA)
#define TECLA_0       cusco_tecla_press(KBD_0)
#define TECLA_1       cusco_tecla_press(KBD_1)
#define TECLA_2       cusco_tecla_press(KBD_2)
#define TECLA_3       cusco_tecla_press(KBD_3)
#define TECLA_4       cusco_tecla_press(KBD_4)
#define TECLA_5       cusco_tecla_press(KBD_5)
#define TECLA_6       cusco_tecla_press(KBD_6)
#define TECLA_7       cusco_tecla_press(KBD_7)
#define TECLA_8       cusco_tecla_press(KBD_8)
#define TECLA_9       cusco_tecla_press(KBD_9)
#define TECLA_AST     cusco_tecla_press(KBD_ASTERISCO)
#define TECLA_SUS     cusco_tecla_press(KBD_SUSTENIDO)



short cusco_tecla_press(int ctecla)
  {
  short flag=0;
  output_b(0);
  delay_us(500);
  switch (ctecla)
     {
     case KBD_0         : output_high(PIN_B4);
                          output_low(PIN_B2);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=1;
                          output_low(PIN_B4);
                          output_high(PIN_B2);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=0;
                          break;

     case KBD_1         : output_high(PIN_B6);
                          output_low(PIN_B7);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=1;
                          output_low(PIN_B6);
                          output_high(PIN_B7);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=0;
                          break;

     case KBD_2         : output_high(PIN_B4);
                          output_low(PIN_B7);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=1;
                          output_low(PIN_B4);
                          output_high(PIN_B7);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=0;
                          break;

     case KBD_3         : output_high(PIN_B7);
                          output_low(PIN_B1);
                          input(PIN_B7);
                          delay_us(20);
                          if (!input(PIN_B7)) flag=1;
                          output_low(PIN_B7);
                          output_high(PIN_B1);
                          input(PIN_B7);
                          delay_us(20);
                          if (!input(PIN_B7)) flag=0;
                          break;

     case KBD_4         : output_high(PIN_B6);
                          output_low(PIN_B5);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=1;
                          output_low(PIN_B6);
                          output_high(PIN_B5);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=0;
                          break;

     case KBD_5         : output_high(PIN_B4);
                          output_low(PIN_B5);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=1;
                          output_low(PIN_B4);
                          output_high(PIN_B5);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=0;
                          break;

     case KBD_6         : output_high(PIN_B5);
                          output_low(PIN_B1);
                          input(PIN_B5);
                          delay_us(20);
                          if (!input(PIN_B5)) flag=1;
                          output_low(PIN_B5);
                          output_high(PIN_B1);
                          input(PIN_B5);
                          delay_us(20);
                          if (!input(PIN_B5)) flag=0;
                          break;

     case KBD_7         : output_high(PIN_B6);
                          output_low(PIN_B3);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=1;
                          output_low(PIN_B6);
                          output_high(PIN_B3);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=0;
                          break;

     case KBD_8         : output_high(PIN_B4);
                          output_low(PIN_B3);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=1;
                          output_low(PIN_B4);
                          output_high(PIN_B3);
                          input(PIN_B4);
                          delay_us(20);
                          if (!input(PIN_B4)) flag=0;
                          break;

     case KBD_9         : output_high(PIN_B3);
                          output_low(PIN_B1);
                          input(PIN_B3);
                          delay_us(20);
                          if (!input(PIN_B3)) flag=1;
                          output_low(PIN_B3);
                          output_high(PIN_B1);
                          input(PIN_B3);
                          delay_us(20);
                          if (!input(PIN_B3)) flag=0;
                          break;

     case KBD_SUSTENIDO : output_high(PIN_B2);
                          output_low(PIN_B1);
                          input(PIN_B2);
                          delay_us(20);
                          if (!input(PIN_B2)) flag=1;
                          output_low(PIN_B2);
                          output_high(PIN_B1);
                          input(PIN_B2);
                          delay_us(20);
                          if (!input(PIN_B2)) flag=0;
                          break;

     case KBD_ASTERISCO : output_high(PIN_B6);
                          output_low(PIN_B2);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=1;
                          output_low(PIN_B6);
                          output_high(PIN_B2);
                          input(PIN_B6);
                          delay_us(20);
                          if (!input(PIN_B6)) flag=0;
                          break;

     case KBD_NADA      : output_b(0b01010010);
                          input(PIN_B6);
                          input(PIN_B4);
                          input(PIN_B1);
                          delay_us(20);
                          if (input(PIN_B6) && input(PIN_B4) && input(PIN_B1)) flag=1;
                          break;



     }
  return(flag);
  }


int cusco_tecla()
  {
  output_b(0x7E); //01111110
  if (!input(PIN_B6)) return(KBD_1);
  if (!input(PIN_B4)) return(KBD_2);
  if (!input(PIN_B1)) return(KBD_3);
  output_b(0xDE); //11011110
  if (!input(PIN_B6)) return(KBD_4);
  if (!input(PIN_B4)) return(KBD_5);
  if (!input(PIN_B1)) return(KBD_6);
  output_b(0xF6); //11110110
  if (!input(PIN_B6)) return(KBD_7);
  if (!input(PIN_B4)) return(KBD_8);
  if (!input(PIN_B1)) return(KBD_9);
  output_b(0xFA); //11111010
  if (!input(PIN_B6)) return(KBD_ASTERISCO);
  if (!input(PIN_B4)) return(KBD_0);
  if (!input(PIN_B1)) return(KBD_SUSTENIDO);
  return(0xFF); // caso nada tenha sido pressionado
  }

// fim da função de teclado LE_KB()
// ****************************************************************************************


/*
funcao cusco_readkbd()
retorna um valor do tipo INT32 (até 9 digitos) lidos via teclado, escrevendo ou nao o valor
no display, na posicao onde estiver o cursor.

uso:

INT32 x;

x = cusco_readkbd(0);  <--- mostra o valor digitado.

ou

x = cusco_readkbd(1);  <--- mostra asteriscos no lugar do valor digitado

ou

x = cusco_readkbd(2); <--- nao mostra nada mas busca valor do teclado

o valor deverá ser inserido usando o teclado numerico matricial.
o valor finaliza com um enter (ou #)
a funcao retornará o valor digitado ou -1 se for cancelado com um (*)
*/

// FIM DAS ROTINAS DE TECLADO PARA CUSCOPIC
//*******************************************************************************

long long_read_eeprom(int pos)   // lê da posição pos e pos+1 da eeprom (16 bits)
  {                              // devolvendo um long
  long aux;
  aux = read_eeprom(pos+1);
  aux = (aux << 8) + read_eeprom(pos);
  return(aux);
  }

int32 int32_read_eeprom(int pos)   // lê da posição pos,pos+1,pos+2,pos+3 da eeprom (32 bits)
  {                               // devolvendo um int32
  int32 aux;
  aux = read_eeprom(pos+3);
  aux = (aux << 8) + read_eeprom(pos+2);
  aux = (aux << 8) + read_eeprom(pos+1);
  aux = (aux << 8) + read_eeprom(pos);
  return(aux);
  }

//
void long_write_eeprom(int ender, long vlr)
  {
  int auxl, auxh;
  auxl = vlr % 256;
  auxh = vlr >> 8;
  write_eeprom(auxl, ender);
  write_eeprom(auxh, ender+1);
  }

void int32_write_eeprom(int ender, int32 vlr)
  {
  int aux, i;
  for(i=0; i<4; i ++)
    {
    aux=vlr%256;
    vlr = vlr >> 8;
    write_eeprom(ender+i, aux);
    }
  }
