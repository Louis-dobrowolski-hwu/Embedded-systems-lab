#include "avr/io.h"

void delay_ms();

int incr=0; 

const float rapportCycliqueVoulu0  = 0.25;   // Soit 25%
const float rapportCycliqueVoulu1 = 0.625;   // Soit 75%
const float rapportCycliqueVoulu2 = 0.875;   // Soit 75%
const float valeurMaxRegistreOCR1x = pow(2,8) - 1; 

void setup(void)
{

//H-bridge direction control
DDRB = 0b00000000;
//OCR0A PWM, set PortD.6 output
DDRD |= (1 << 6);
//set OCR0A PWM, fast PWM, no
//prescaler, non-inverted
  TCCR0B &= 0b11111000;
  TCCR0B |= 0b00000101;//prescaler de 1024//probléme
  TCCR0A = 0b10100011;// normal non inversé et Fast PWM 
}


void loop (){
  //if ((PINB & 0b00001000)==8)
  //Serial.println(digitalRead(11));
  if ((PINB & 0b00001000)==8)
  { 

    switch (incr){    
    case 0:
    OCR0A = 0;
    Serial.println(OCR0A);
    incr=incr+1;
    delay(100);
    break;
    case 1: 
    OCR0A = rapportCycliqueVoulu0 * valeurMaxRegistreOCR1x;
    Serial.println(OCR0A);
    incr=incr+1;
    delay(100);
    break;
    case 2 :
      OCR0A = rapportCycliqueVoulu1 * valeurMaxRegistreOCR1x;
      incr=incr+1;
      Serial.println(OCR0A);
      delay(100);
      break;
    case 3 : 
      OCR0A = rapportCycliqueVoulu2 * valeurMaxRegistreOCR1x;
      incr=0;
      Serial.println(OCR0A);
      delay(100);
      break;
    } 

  } 

}



void delay_ms(){
  TCCR0A=0x00;
  TCCR0B=0x00000111;
  TCNT0= 0;
  //TIMSK2 = 0b00000100; // Enable interuption timer0 
  while((TIFR0 & 0x1)==0);
  TCCR0B=0;
  TIFR0=1<<TOV0;
}
