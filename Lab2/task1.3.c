#include "avr/io.h"

void delay_ms();
void initADC(void)

uint16_t potentiometerValue;
uint16_t threshold_level;



int incr=0; 

const float rapportCycliqueVoulu0  = 0.25;   // Soit 25%
const float rapportCycliqueVoulu1 = 0.625;   // Soit 75%
const float rapportCycliqueVoulu2 = 0.875;   // Soit 75%
const float valeurMaxRegistreOCR1x = pow(2,8) - 1; 


void setup(void)
{

  //H-bridge direction control
  DDRD |= (1 << 2) | (1 << 3);
  DDRB = 0b00000000;
  DDRC = 0b0000000;
  //OCR0A PWM, set PortD.6 output
  DDRD |= (1 << 6);
  PORTD = 0x08;
  //set OCR0A PWM, fast PWM, no
  //prescaler, non-inverted
  TCCR0B &= 0b11111000;
  TCCR0B |= 0b00000101;//prescaler de 1024//probléme
  TCCR0A = 0b10100011;// normal non inversé et Fast PWM 

  DDRB |= (1 << PB2); //Data Direction Register B: writing a 1 to the bit enables output
  threshold_level= 0b10000000;
  initADC();  

}




void loop(){

  if ((PINB & 0b00000100)==4)
  {
    PORTD = PORTD ^ (1<<2);
    PORTD = PORTD ^ (1<<3);
  }

  ADCSRA |= (1 << ADSC); //start ADC conversion

  while((ADCSRA & (1 << ADSC))) //wait until ADSC bit is clear, i.e., ADC conversion is done
  {}
  //read ADC value in
  uint8_t theLowADC = ADCL;
  potentiometerValue = ADCH << 8 | theLowADC;
  potentiometerValue = ADC;
  
  OCR0A=potentiometerValue /4;

}

void initADC(void) {
  ADMUX |= (1 << REFS0) | (1 << MUX0); //reference voltage on AVCC, and use ADC1
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC clock prescaler / 8
  ADCSRA |= (1 << ADEN); //enables the ADC
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