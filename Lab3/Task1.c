#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

int main() 
{
  DDRD |= 1 << PIND4;
  PORTD = 0x00;
  USART_init(); 

  while(1) 
  {
    // put your main code here, to run repeatedly:
    unsigned char ReceivedChar = USART_receive(); // Wait until data is received
    if (ReceivedChar == '0')
    {
      PORTD &= ~ (1<<4);
      delay(200);
      USART_putstring("LED is off!\n");
    }
    if (ReceivedChar == '1')
    {
      PORTD |= (1<<4);
      delay(200);
      USART_putstring("LED is on!\n");
    }
  }
 return  0; 
}

void USART_init(void){
  UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8); //set baud rate
  UBRR0L = (uint8_t)(BAUD_PRESCALLER);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); //enable transmit
  UCSR0C = (3<<UCSZ00); //set 8-bit (default)
}

unsigned char USART_receive(void){
  while(!(UCSR0A & (1<<RXC0))); // Wait to receive data
  return UDR0; // Read data from UDR
}

