#include <18f452.h>
#use delay(clock=20000000)
#fuses HS,NOWDT,PUT
#include <lcd_generico.c>
main()
{ 
delay_ms(500);
inic_display();

while (true)
{
mostra("teste");
output_toggle(PIN_D4);
delay_ms (500);
}
}
