
#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTB0
#define EN eS_PORTB1
#define F_CPU 16000000UL

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <string.h>

char* string = "Welcome to B31DD Embedded Systems!";
int i;

int main() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  DDRB = 0xFF;
  Lcd8_Init();

while(1) 
{
  // put your main code here, to run repeatedly:
  Lcd8_Set_Cursor(1,1);
  Lcd8_Write_String(string);
  for(i=0;i<strlen(string)-1;i++)
  {
    _delay_ms(500);
    Lcd8_Shift_Left();
  }
}
return 0; 
}

