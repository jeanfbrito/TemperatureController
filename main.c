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
  int screen = 0; //0-Tela principal, 1-Config. Temperatura, 2-Config. Horario
  
update_clock(); 
float read_temperature();
check_temperature();
show_clock();
show_temperature();
configure_temperature();
configure_time();
 
main()
{ 
   
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
   
      switch(screen){
         case 0:
            update_clock();
            read_temperature();
            check_temperature();
            show_clock();
            show_temperature();
            break;
         case 1:
            configure_temperature();
         case 2:
            configure_time();
      }
      
   
      temperatura = read_temperature();

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

float read_temperature() {
   long int temp;
   //starts the conversion and reads the result
   temp = read_adc();

   //faz o calculo para converter a tensao em graus celsius
   return(temp);//((temp - 50) * 8.9)/ 100;
}
