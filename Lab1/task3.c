int btt= 0; 
int r=1,ok=0;
int i=0;


void main() {
  // put your setup code here, to run once:
  DDRB = 0b00000111;
  DDRD = 0b10000000;
 
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR0A = 0;                 // Reset entire TCCR0A to 0 
  TCCR0B = 0;                 // Reset entire TCCR0B to 0
 
  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */  
  TCCR1B |= 0b00000101;        //Set CS12 to 1 so we get prescalar 1024 
  TCCR0B |= 0b00000101;        //Set CS12 to 1 so we get prescalar 1024 
  
  /*3. Set the value of register A to 31250*/
  OCR1A = 40000;
  OCR0A = 0;              //Finally we set compare register A to this value  
  TCNT1 = 0;            // Mise du timer1 à zéro
  TCNT0 = 0;
  

while(1) {
  // put your main code here, to run repeatedly:
  
  if ((PINB & 0b00001000)==0)
    {
      r = random(1,7);
      for(i=0;i<2;i++){
      if ((TIFR1 & 0b00000001) == 1){
        TCNT1 = 40286;
        TIFR1 |=  (1<<0);
        if (r == 1)
        {
            one();
        }
        if (r == 2)
        {
          two();
        }
        if (r == 3)
        {
          three();
        }
        if (r == 4)
        {
          four();
        }
        if (r == 5)
        {
          five();
        }
      if (r == 6)
        {
          six();
        }
      //}
      btt=0;
        }}}
}
}
void one(){
  PORTD = PORTD ^ (1<<7);
}
void two(){
  PORTB = PORTB ^ (1<<1);
}
void three(){
  PORTD = PORTD ^ (1<<7);
  PORTB =PORTB ^  (1<<1);
}
void four(){
  PORTB = PORTB ^ (1<<2);
  PORTB = PORTB ^ (1<<0);
}
void five(){
  PORTB = PORTB ^ (1<<2);
  PORTB =  PORTB ^(1<<0);
  PORTD =  PORTB ^(1<<7);
}
void six(){
  PORTB = PORTB ^ (1<<2);
  PORTB =  PORTB ^(1<<1);
  PORTB = PORTB ^ (1<<0);
}
void off(){
  PORTB &= ~  (1<<2);
  PORTB &= ~  (1<<1);
  PORTB &= ~  (1<<0);
  PORTD &= ~  (1<<7);
}