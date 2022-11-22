#include "avr/io.h"

void initADC(void);
void USART_init(void);
unsigned char USART_receive(void);

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)


uint16_t potentiometerValue;
uint16_t threshold_level;

bool flag;

int incr=0; 
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


const float rapportCycliqueVoulu0  = 0.25;   // Soit 25%
const float rapportCycliqueVoulu1 = 0.625;   // Soit 75%
const float rapportCycliqueVoulu2 = 0.875;   // Soit 75%
const float valeurMaxRegistreOCR1x = pow(2,8) - 1; 


void setup(void)
{

  //H-bridge direction control
  //DDRD |= (1 << 2) | (1 << 3)| (1 << 4) | (1 << 7);
  DDRD= 0x11011100;
  DDRB = 0b00000001;
  DDRC = 0b0000000;
  //OCR0A PWM, set PortD.6 output
  DDRD |= (1 << 6);
  //PORTD = 0x08;
  //set OCR0A PWM, fast PWM, no
  //prescaler, non-inverted
  TCCR0B &= 0b11111000;
  TCCR0B |= 0b00000101;//prescaler de 1024//probléme
  TCCR0A = 0b10100011;// normal non inversé et Fast PWM 

  DDRB |= (1 << PB2); //Data Direction Register B: writing a 1 to the bit enables output
  threshold_level= 0b10000000;
  initADC();  
  USART_init();

}


void loop(){
  unsigned char ReceivedChar = USART_receive();


  PORTB &= ~  (1<<0);
  _delay_ms(0.002);
  PORTB |= (1<<0);
  _delay_ms(0.01);
  PORTB &= ~  (1<<0);
  duration = pulseIn(9, HIGH);///probléme 
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  if (ReceivedChar == 's' & flag==true)
    {
    Serial.print("go");
    PORTD = PORTD &= ~ (1<<2);
    PORTD = PORTD  |= (1<<3);
    PORTD = PORTD  |= (1<<4);
    PORTD = PORTD &= ~(1<<7);
    //PORTD=0x8;
  }
  else if(ReceivedChar == 'z' & flag==true){
    Serial.print("s");
    PORTD = PORTD |= (1<<2);
    PORTD = PORTD &= ~  (1<<3);
    PORTD = PORTD &= ~  (1<<4);
    PORTD = PORTD |= (1<<7);
  }
  else if(ReceivedChar == 'q' & flag==true){
    PORTD = PORTD |= (1<<2);
    PORTD = PORTD &= ~  (1<<3);
    PORTD = PORTD  |= (1<<4);
    PORTD = PORTD &= ~(1<<7);
  }
  else if(ReceivedChar == 'd' & flag==true){
    PORTD = PORTD &= ~ (1<<2);
    PORTD = PORTD  |= (1<<3);
    PORTD = PORTD &= ~  (1<<4);
    PORTD = PORTD |= (1<<7);
  }
  else if(ReceivedChar == 'a' & flag==true){
    PORTD = PORTD |= (1<<2);
    PORTD = PORTD |= (1<<3);
    PORTD = PORTD |=   (1<<4);
    PORTD = PORTD |= (1<<7);
  }
  if(distance<10){
    PORTD = PORTD |= (1<<2);
    PORTD = PORTD |= (1<<3);
    PORTD = PORTD |=   (1<<4);
    PORTD = PORTD |= (1<<7);
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


void USART_init(void){
  UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8); //set baud rate
  UBRR0L = (uint8_t)(BAUD_PRESCALLER);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); //enable transmit
  UCSR0C = (3<<UCSZ00); //set 8-bit (default)
}
unsigned char USART_receive(void){
  if(!(UCSR0A & (1<<RXC0))){
     flag=false;
  } // Wait to receive data
  else{

    flag=true;
  }
  return UDR0; // Read data from UDR
}