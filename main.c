#include <18f452.h>
#device ADC=10
#use delay(clock=20000000)
#fuses HS,NOWDT,PUT
#include <lcd_generico.c>
#include "ds1307.c"
 
  BYTE sec; 
  BYTE min; 
  BYTE hrs; 
  BYTE day; 
  BYTE month; 
  BYTE yr; 
  BYTE dow; 
  
update_clock(); 
 
main()
{ 
   
   long int temp;
   float temperatura;


  
  ds1307_init(); 
  
  // Set date for -> 15 June 2005 Tuesday 
  // Set time for -> 15:20:55 
  ds1307_set_date_time(18,11,12,2,22,05,55); 


   setup_adc(ADC_CLOCK_INTERNAL);
   //enables the a/d module 
   set_adc_channel(0);
   //the next read_adc call will read channel 0
   delay_us(10);
   //a small delay is required after setting the channel

   //aguarda 500ms
   delay_ms(500);
   
   //inicializa o display LCD
   inic_display();


   while (true)
   {

      //starts the conversion and reads the result
      temp = read_adc();

      //faz o calculo para converter a tensao em graus celsius
      temperatura = temp;//((temp - 50) * 8.9)/ 100;

      //envia o cursor do LCD para a posicao 0,0
      display(0,0x80);

      //imprime na tela a temperatura
      printf(mostra,"Temperatura: %.1lfC   ",temperatura);
      
      //envia o cursor do LCD para a posicao 1,0
      display(0,0xC0);

      //imprime na tela a temperatura
      update_clock();

      //alterna o estado do pino D4
      output_toggle(PIN_a4);

      //aguarda 500ms
      delay_ms (500);
   }
}

update_clock(){
    //ds1307_get_date(day,month,yr,dow); 
    ds1307_get_time(hrs,min,sec); 
      
    sec = ds1307_read_byte(0);
    sec = bcd2bin(sec);
      
    //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
    printf(mostra,"Hora: \%02d:\%02d:\%02d", hrs,min,sec); 
}
