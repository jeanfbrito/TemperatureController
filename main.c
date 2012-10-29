#include <18f452.h>
#device ADC=10
#use delay(clock=20000000)
#fuses HS,NOWDT,PUT
#include <lcd_generico.c>
main()
{ 
   long int temp;
   float temperatura;

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
      temperatura = ((temp - 50) * 8.9)/ 100;

      //envia o cursor do LCD para a posicao 0,0
      display(0,0x80);

      //imprime na tela a temperatura
      printf(mostra,"Temperatura: %.1lfC   ",temperatura);

      //alterna o estado do pino D4
      output_toggle(PIN_D4);

      //aguarda 500ms
      delay_ms (500);
   }
}
