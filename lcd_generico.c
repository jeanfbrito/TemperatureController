/*

Função para utilização do display LCD para qualquer tamanho

   inic_display();                        função para configurar e inicializar o display
   display(char tipo,char dado);          função para enviar um comando ou um dado para o display
   mostra(char dado);                     funçao para enviar um dado para o display

   Configuração dos pinos do microcontrolador

   RB0 = enable display
   RB1 = RS
   RB2 = RW
   RB3 =
   RB4 = DB4
   RB5 = DB5
   RB6 = DB6
   RB7 = DB7

   Primeira linha = 0x80
   Segunda  linha = 0xC0
   Terceira linha = 0x94
   Quarta linha   = 0xD4

Aprimorado por Cleber Toss Hoffmann
cleber.toss.hoffmann@gmail.com

*/
//
#byte PORTB=0xF81
#byte TRISB=0xF93

//Constantes
#define set_bit0 0x01
#define set_bit1 0x02
#define set_bit2 0x04

#define clear_bit0 0xfe
#define clear_bit1 0xfd
#define clear_bit2 0xfb

void inic_display();

#separate
void display(char tipo,char dado);

#separate
void mostra(char dado);

void inic_display()
{
 TRISB =0x00;
 delay_ms(50);

 PORTB  = 0x30;
 PORTB |= set_bit0;
 delay_us(5);
 PORTB &= clear_bit0;
 delay_ms(25);

 PORTB = 0x30;
 PORTB |= set_bit0;
 delay_us(5);
 PORTB &= clear_bit0;
 delay_ms(25);

 PORTB = 0x30;
 PORTB |= set_bit0;
 delay_us(5);
 PORTB &= clear_bit0;
 delay_ms(25);

 PORTB = 0x30;
 PORTB |= set_bit0;
 delay_us(5);
 PORTB &= clear_bit0;

 delay_us(200);
 PORTB = 0x20;
 PORTB |= set_bit0;
 delay_us(5);
 PORTB &= clear_bit0;

 delay_us(200);
 display(0,0x28);
 display(0,0x08);
 display(0,0x01);
 delay_ms(5);
 display(0,0x06);
 display(0,0x0c);

}


/* display
   Envia um dado para o display.
   Se tipo=0, é um comando (RS=0)
   Se tipo=1, é um dado (RS=1)
*/
#separate
void display(char tipo,char dado)
{
 char temp;
 if(tipo == true)
    {
     temp=(dado & 0xf0) | set_bit1;
     PORTB = temp;
     PORTB |= set_bit0;
     delay_us(5);
     PORTB &= clear_bit0;
//   delay_us(50);
     temp=(dado << 4) | set_bit1;
     PORTB = temp;
     PORTB |= set_bit0;
     delay_us(5);
     PORTB &= clear_bit0;
     delay_us(50);

    }
 else
    {
     temp=(dado & 0xf0);
     PORTB = temp;
     PORTB |= set_bit0;
     delay_us(5);
     PORTB &= clear_bit0;
//   delay_us(50);
     temp=(dado << 4);
     PORTB = temp;
     PORTB |= set_bit0;
     delay_us(5);
     PORTB &= clear_bit0;
     delay_us(50);
    }

}

#separate
void mostra(char dado)
{
 display(1,dado);
}
