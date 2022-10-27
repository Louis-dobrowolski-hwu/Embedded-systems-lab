#include "avr/io.h"

int incr=1; 

const float rapportCycliqueVoulu0  = 0.00;   // Soit 25%
const float rapportCycliqueVoulu1  = 0.25;   // Soit 25%
const float rapportCycliqueVoulu2 = 0.50;   // Soit 75%
const float rapportCycliqueVoulu3  = 0.75;   // Soit 25%
const float rapportCycliqueVoulu4 = 0.98;   // Soit 75%
const float valeurMaxRegistreOCR1x = pow(2,8) - 1; 

int main()
{

DDRB |= (1 << 1);

TCCR1B &= 0b11111000;
TCCR1B |= 0b00001100;//prescaler de 64//probléme
TCCR1A = 0b10100001;// Fast correct PWM}

 while(1){
if ((PINB & 0b00001000)==8)
  { 
    switch (incr){    
    case 1: 
    OCR1A = rapportCycliqueVoulu0 * valeurMaxRegistreOCR1x;
    incr=incr+1;
    break;
    case 2 :
      OCR1A = rapportCycliqueVoulu1 * valeurMaxRegistreOCR1x;
      incr=incr+1;
      break;
    case 3 : 
      OCR1A = rapportCycliqueVoulu2 * valeurMaxRegistreOCR1x;
      incr=incr+1;
      break;
    case 4 : 
      OCR1A = rapportCycliqueVoulu3 * valeurMaxRegistreOCR1x;
      incr=incr+1;
      break;
    case 5 : 
      OCR1A = rapportCycliqueVoulu4 * valeurMaxRegistreOCR1x;
      incr=1;
      break;
    }
  }
}}



