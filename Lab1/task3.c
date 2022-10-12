int btt= 0; 
int r=1,ok=0;
bool flag=false;
int i=0;


void setup() {
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
  
  /*3. We enable compare match mode on register A*/
  /*TIMSK1 |= 0b00000010;        //Set OCIE1A to 1 so we enable compare match A 
  TIMSK0 |= 0b00000010;        //Set OCIE1A to 1 so we enable compare match A 
  
  /*4. Set the value of register A to 31250*/
  OCR1A = 40000;
  OCR0A = 0;              //Finally we set compare register A to this value  
  TCNT1 = 0;            // Mise du timer1 à zéro
  TCNT0 = 0;
  
}

void loop() {
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

void one(){
  //digitalWrite(7, !digitalRead(7));
  //ok++;
  digitalWrite(7, !digitalRead(7));
  //PORTD |=  (1<<7);
}
void two(){
  //PORTB |=  (1<<1);
  digitalWrite(9, !digitalRead(9));
}
void three(){
  //PORTD |=  (1<<7);
  //PORTB |=  (1<<1);
  digitalWrite(7, !digitalRead(7));
  digitalWrite(9, !digitalRead(9));
}
void four(){
  //PORTB |=  (1<<2);
  //PORTB |=  (1<<0);
  digitalWrite(10, !digitalRead(10));
  digitalWrite(8, !digitalRead(8));
}
void five(){
  //PORTB |=  (1<<2);
  //PORTB |=  (1<<0);
  //PORTD |=  (1<<7);
  digitalWrite(10, !digitalRead(10));
  digitalWrite(8, !digitalRead(8));
  digitalWrite(7, !digitalRead(7));
}
void six(){
  //PORTB |=  (1<<2);
  //PORTB |=  (1<<1);
  //PORTB |=  (1<<0);
  digitalWrite(10, !digitalRead(10));
  digitalWrite(9, !digitalRead(9));
  digitalWrite(8, !digitalRead(8));
}
void off(){
  PORTB &= ~  (1<<2);
  PORTB &= ~  (1<<1);
  PORTB &= ~  (1<<0);
  PORTD &= ~  (1<<7);
}/*
ISR(TIMER1_COMPA_vect){
  TCNT1  = 0;                  //First, set the timer back to 0 so it resets for next interrupt
  flag=!flag;
}*/