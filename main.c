#include <18f452.h>
#device ADC=10
#use delay(clock=20000000)
#fuses HS,NOWDT,PUT
#include <lcd_generico.c>
#include <math.h>
#include "ds1307.c"

#define TECLA_SET    !input(PIN_D0)
#define TECLA_MAIS   !input(PIN_D3)
#define TECLA_MENOS  !input(PIN_D2)

#define SAIDA01 PIN_D1

#define POTENTIAL_DIVIDER_RESISTOR 10000
#define THERMISTOR_B_VALUE 3977
#define THERMISTOR_REF_TEMP 298.15
#define THERMISTOR_REF_RESISTANCE 10000

#define DEBOUNCE 2

long int tecla_menos_tempo = DEBOUNCE;
long int tecla_mais_tempo = DEBOUNCE;
long int tecla_set_tempo = DEBOUNCE;

int1 tecla_menos_status = false;
int1 tecla_mais_status = false;
int1 tecla_set_status = false;

int1 tecla_menos_state = false;
int1 tecla_mais_state = false;
int1 tecla_set_state = false;

int1 entrar_temperatura = true;
int1 entrar_relogio = true;

BYTE sec; 
BYTE min; 
BYTE hrs; 
BYTE day; 
BYTE month; 
BYTE yr; 
BYTE dow; 
int temperatura_maxima = 30;
int tela = 0; //0-Tela principal, 1-Config. Temperatura, 2-Config. Horario
float temperatura;

int histerese = 3;

update_clock(); 
read_temperature();
check_temperature();
show_clock();
show_temperature();
configure_temperature();
configure_time();
verifica_teclas();

main()
{ 
ds1307_init(); 

// Set date for -> 15 June 2005 Tuesday 
// Set time for -> 15:20:55 
//ds1307_set_date_time(18,11,12,2,22,05,55); 


  setup_adc(ADC_CLOCK_INTERNAL);
//enables the a/d module 
  set_adc_channel(0);
//the next read_adc call will read channel 0
  delay_us(10);
//a small delay is required after setting the channel

//aguarda 100ms
  delay_ms(100);

//inicializa o display LCD
  inic_display();

  while (true)
  {

    switch(tela){
      case 0:
        display(0,0x01);
        update_clock();
        read_temperature();
        check_temperature();
        show_temperature();
        show_clock();

        if(tecla_set_status && !tecla_menos_status && tecla_mais_status)
          tela = 2;

        if(tecla_set_status && tecla_menos_status && !tecla_mais_status)
          tela = 1;
        

        break;
      case 1:
        read_temperature();
        configure_temperature();
        break;
      case 2:
        //update_clock();
        configure_time();
        break;
    }

//alterna o estado do pino D4
    //output_toggle(PIN_D1);

    verifica_teclas();

//aguarda 500ms
    delay_ms (100);
  }
}

check_temperature(){
  if(temperatura < temperatura_maxima - histerese)
    output_high(SAIDA01);
  else if(temperatura > temperatura_maxima)
    output_low(SAIDA01);
}

read_temperature() {
long int adc;
float formula;

  adc = read_adc();
  formula = ((adc - 220) * 0.0007 );
  if(formula < 0)
   formula = 0;
  temperatura = adc * (0.049 + formula);

  //envia o cursor do LCD para a posicao 0,0
  //display(0,0xA0);
//imprime na tela a temperatura
  //printf(mostra,"ADC: %ld    ",adc);
  //envia o cursor do LCD para a posicao 0,0
  //display(0,0xD0);
//imprime na tela a temperatura
  //printf(mostra,"form: %f    ",formula);
  
}


show_temperature(){
//envia o cursor do LCD para a posicao 0,0
  display(0,0x80);
//imprime na tela a temperatura
  printf(mostra,"Temperatura: %.0lfC    ",temperatura);
}

update_clock(){

  ds1307_get_date(day,month,yr,dow); 
  ds1307_get_time(hrs,min,sec); 

  sec = ds1307_read_byte(0);
  sec = bcd2bin(sec);

}

show_clock(){

//envia o cursor do LCD para a posicao 1,0
  display(0,0xC0);

//printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
  printf(mostra,"Hora: \%02d:\%02d:\%02d     ", hrs,min,sec); 
}


configure_time() {
  static int state = 0;

  //envia o cursor do LCD para a posicao 1,0
  display(0,0x80);
  //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
  printf(mostra,"Config Relogio    ");

  //envia o cursor do LCD para a posicao 1,0
  display(0,0xC0);
  //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
  printf(mostra,"H\%02d:\%02d:\%02d D\%02d/\%02d/\%02d       ", hrs,min,sec,day,month,yr); 


  switch(state){
    case 0: //menu superior
      if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
        state = 1;
      // else if(TECLA_MAIS)
      //   tela = 0;
      // else if(TECLA_MENOS)
      //   tela = 1;
      break;

    case 1: //hora
      display(0,0xC0);
      //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
      printf(mostra,"Horas:\%02d              ", hrs);
      if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
        state = 2;
      else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
        hrs++;
        if(hrs > 23)
          hrs = 0;
      }
      else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
        hrs--;
        if(hrs == -1)
          hrs = 23;
      }
      break;
    case 2: //minuto
      display(0,0xC0);
      //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
      printf(mostra,"Minutos:\%02d            ", min);
      if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
        state = 3;
      else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
        min++;
        if(min > 59)
          min = 0;
      }
      else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
        min--;
        if(min == -1)
          min = 59;
      }
      break;
    case 3: //segundo
      display(0,0xC0);
      //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
      printf(mostra,"Segundos:\%02d               ", sec);
      if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
        state = 4;
      else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
        sec++;
        if(sec > 59)
          sec = 0;
      }
      else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
        sec--;
        if(sec == -1)
          sec = 59;
      }
      break;
    case 4: //dia
      display(0,0xC0);
      //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
      printf(mostra,"Dia:\%02d                ", day);
      if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
        state = 5;
      else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
        day++;
        if(day > 31)
          day = 1;
      }
      else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
        day--;
        if(day < 1)
          day = 31;
      }
      break;
    case 5: //mes
      display(0,0xC0);
      //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
      printf(mostra,"Mes:\%02d                ", month);
      if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
        state = 6;
      else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
        month++;
        if(month > 12)
          month = 1;
      }
      else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
        month--;
        if(month < 1)
          month = 12;
      }
      break;
    case 6: //ano
      display(0,0xC0);
      //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
      printf(mostra,"Ano:\%02d                ", yr);
      if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
        state = 7;
      else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
        yr++;
        if(yr > 30)
          yr = 0;
      }
      else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
        yr--;
        if(yr < 1)
          yr = 30;
      }
      break;
    case 7: //mes

      //envia o cursor do LCD para a posicao 1,0
      display(0,0xC0);
      //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
      printf(mostra,"Salvar? - NAO, + SIM"); 
      if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
        ds1307_set_date_time(day,month,yr,dow,hrs,min,sec);
        tela = 0;
        state = 0;
      }
      else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
        state = 0;
        tela = 0;
      }
      break;
    }

}

configure_temperature() {
  static int state;

  //envia o cursor do LCD para a posicao 1,0
  display(0,0x80);
  //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
  printf(mostra,"Config Temperatura    ");

  //envia o cursor do LCD para a posicao 1,0
  display(0,0xC0);
  //printf(mostra,"\f\%02d/\%02d/\%02d\r\n",day,month,yr); 
  printf(mostra,"Temp Max: \%02d             ", temperatura_maxima); 

  switch(state){
  // case 0: //menu superior
  //   if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
  //     state = 1;
  //   // else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status)
  //   //   tela = 2;
  //   // else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status)
  //   //   tela = 0;
  //   break;

  case 0: //temperatura maxima
    if(tecla_set_status && !tecla_menos_status && !tecla_mais_status)
      tela = 0;//state = 0;
    else if(tecla_mais_status && !tecla_menos_status && !tecla_set_status){
      temperatura_maxima++;
      if(temperatura_maxima > 100)
        temperatura_maxima = 0;
    }
    else if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
      temperatura_maxima--;
      if(temperatura_maxima < 1)
        temperatura_maxima = 100;
    }
    break;
  }
}

verifica_teclas() {

  if(TECLA_SET){
    if(tecla_set_tempo == DEBOUNCE){
      tecla_set_status = true;
      tecla_set_state = true;
    }    
  } else {
    if(!tecla_set_state){      
      tecla_set_tempo = DEBOUNCE;
    }
  }

  if(tecla_set_state){
    if(tecla_set_tempo > 1){
      tecla_set_tempo--;
    } else {
      tecla_set_tempo = 0;
    }
    if(tecla_set_tempo < 1){
      tecla_set_status = false;
      tecla_set_state = false;
    }
  }

  if(TECLA_MAIS){
    if(tecla_mais_tempo == DEBOUNCE){
      tecla_mais_status = true;
      tecla_mais_state = true;
    }    
  } else {
    if(!tecla_mais_state){      
      tecla_mais_tempo = DEBOUNCE;
    }
  }

  if(tecla_mais_state){
    if(tecla_mais_tempo > 1){
      tecla_mais_tempo--;
    } else {
      tecla_mais_tempo = 0;
    }
    if(tecla_mais_tempo < 1){
      tecla_mais_status = false;
      tecla_mais_state = false;
    }
  }

  if(TECLA_MENOS){
    if(tecla_menos_tempo == DEBOUNCE){
      tecla_menos_status = true;
      tecla_menos_state = true;
    }    
  } else {
    if(!tecla_menos_state){      
      tecla_menos_tempo = DEBOUNCE;
    }
  }

  if(tecla_menos_state){
    if(tecla_menos_tempo > 1){
      tecla_menos_tempo--;
    } else {
      tecla_menos_tempo = 0;
    }
    if(tecla_menos_tempo < 1){
      tecla_menos_status = false;
      tecla_menos_state = false;
    }
  }
}
