#include <18f452.h>
#use delay(clock=20000000)
#fuses HS,NOWDT,PUT

main()
{ 
delay_ms(500);
while (true)
{
output_toggle(PIN_D4);
delay_ms (500);
}
}
