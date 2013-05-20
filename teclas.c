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

#define DEBOUNCE 100

long int tecla_menos_tempo = DEBOUNCE;
long int tecla_mais_tempo = DEBOUNCE;
long int tecla_set_tempo = DEBOUNCE;

int1 tecla_menos_status = false;
int1 tecla_mais_status = false;
int1 tecla_set_status = false;

int1 tecla_menos_state = false;
int1 tecla_mais_state = false;
int1 tecla_set_state = false;

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

main()
{ 

//inicializa o display LCD
  inic_display();

  while (true)
  {
    verifica_teclas();

  display(0,0x80);
//imprime na tela a temperatura
  printf(mostra,"%d", tecla_mais_state);


          //envia o cursor do LCD para a posicao 0,0
  display(0,0xC0);
//imprime na tela a temperatura
  printf(mostra,"TS:%d T-:%d T+:%d   ", tecla_set_status, tecla_menos_status, tecla_mais_status);
            //envia o cursor do LCD para a posicao 0,0
  display(0,0x94);
//imprime na tela a temperatura
  printf(mostra,"tS:%ld t-:%ld t+:%ld   ", tecla_set_tempo, tecla_menos_tempo, tecla_mais_tempo);

  if(tecla_menos_status && tecla_mais_status){
      display(0,0xD4);
      //imprime na tela a temperatura
      printf(mostra,"+ -   ");
  }

  if(tecla_set_status && tecla_mais_status){
      display(0,0xD4);
      //imprime na tela a temperatura
      printf(mostra,"set +   ");
  }

  if(tecla_menos_status && tecla_set_status){
      display(0,0xD4);
      //imprime na tela a temperatura
      printf(mostra,"set -   ");
  }

  if(!tecla_menos_status && !tecla_set_status && !tecla_mais_status){
      display(0,0xD4);
      //imprime na tela a temperatura
      printf(mostra,"nada      ");
  }

  if(tecla_menos_status && !tecla_set_status && !tecla_mais_status){
      display(0,0xD4);
      //imprime na tela a temperatura
      printf(mostra,"-   ");
  }

  if(tecla_mais_status && !tecla_set_status && !tecla_menos_status){
      display(0,0xD4);
      //imprime na tela a temperatura
      printf(mostra,"+   ");
  }

  if(tecla_set_status && !tecla_menos_status && !tecla_mais_status){
      display(0,0xD4);
      //imprime na tela a temperatura
      printf(mostra,"set   ");
  }
    

//alterna o estado do pino D4
    //output_toggle(PIN_D1);

//aguarda 500ms
    delay_ms (1);
  }
}

