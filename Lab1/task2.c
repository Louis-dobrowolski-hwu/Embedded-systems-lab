/* 
Calculations (for 1.6s): 
  System clock 16 Mhz and Prescalar 1024;
  Timer 1 speed = 16Mhz/1024 = 15.6 Khz    
  Pulse time = 1/15.6 Khz =  64us  
  Count up to = 1.6s / 64us = 25 000 (so this is the value the OCR register should have)*/  

int incr=0; 
int btt=0;

int main() {

  DDRB = 0b00000111;
 
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
 
  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */  
  TCCR1B |= 0b00000101;        //Set CS12 to 1 so we get prescalar 1024  
  
  /*3. We enable compare match mode on register A*/
  TIMSK1 |= 0b00000010;        //Set OCIE1A to 1 so we enable compare match A 
  
  /*4. Set the value of register A to 31250*/
  OCR1A = 25000;             //Finally we set compare register A to this value  
  TCNT1 = 0;            // Mise du timer1 à zéro

  while(1){
    if ((PINB & 0b00001000)==0)
    { 
      btt=1;
    }
  }
  return 0; 
}
//With the settings above, this IRS will trigger each 500ms.
ISR(TIMER1_COMPA_vect){
  TCNT1  = 0;                  //First, set the timer back to 0 so it resets for next interrupt
  if (btt==1){
    if (incr==0){
      PORTB &= ~ (1<<2);
      PORTB |= (1<<0);
      incr=incr+1;
    }
    else if(incr==1) {
      //LED_STATE = !LED_STATE;
      PORTB &= ~ (1<<0);
      PORTB |= (1<<1);
      incr=incr+1;
      }
    else if(incr==2)
    {
      //LED_STATE1 = !LED_STATE1;
      PORTB &= ~(1<<1);
      PORTB |= (1<<2);
      incr=incr+1;
    }
    else if(incr==3)
    {
      PORTB &= ~(1<<2);
      incr=0;
      btt=0;
    }
  }
}