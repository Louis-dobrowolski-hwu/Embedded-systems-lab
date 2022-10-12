#define __SFR_OFFSET 0x20
  
#include "avr/io.h"

.global start
.global forever

start:
  LDI R16, 0x01     ; Setting 1st bit of PORTB as output
  STS DDRB, R16

  LDI R16, 0x02     ; Setting 2st bit of PORTC as output
  STS DDRC, R16

  LDI R16, 0x03     ; Setting 2st bit of PORTD as output
  STS DDRD, R16

  LDI R17, 0x00
  STS PORTB, R17    ; Writing 0 to PORTB

  LDI R17, 0x00
  STS PORTC, R17    ; Writing 0 to PORTC

  LDI R17, 0x00
  STS PORTD, R17    ; Writing 0 to PORTD

  LDI R16, 0x00
  STS TCCR1A, R16   ; Setting all bits of TCCR1A as 0

  MOV R23,0x0 

  ;LDI R16,  0x0     ;
  ;STS R23, R16       ;
  RET


forever: 
  LDI R16, 0xC2
  STS TCNT1H, R16   ; Writing 0xC2 into TCNT1H (8-bit)
  LDI R16, 0xF7
  STS TCNT1L, R16   ; Writing 0xF7 into TCNT1H (8-bit)
  LDI R16, 0x05
  STS TCCR1B, R16   ; Writing 0x05 into TCCR1B

L:LDS R0, TIFR1     ; Load the value of TIFR1 into R0
  SBRS R0, 0        ; Skip the next statement if overflow has occured. 
  RJMP L            ; Loop until overflow occurs.
  LDI R16, 0x00
  STS TCCR1B, R16   ; Stop the Timer/Counter1
  LDI R16, 0x01
  STS TIFR1, R16    ; Clear the overflow flag by writing 1 to it
  COM R17           ; Clear the overflow flag by writing 1 to it          ; Complement R17 register

  STS PORTB, R17    ; Toggle the LED output
  RET
  
  
  
  CPI R23,0x0       
  BREQ  L7            ; Toggle the LED output
;  CPI R23, 0x01        
;  BREQ L8            
;  CPI R23, 0x02        
;  BREQ  L9            
  RET

L7: STS PORTB, R17 
  INC R23
  COM R17 
    
;L8: STS PORTC, R17 ;
;  INC R23;
;  RET

;L9: STS PORTD, R17 ;
;  INC R23;
;  LDI R23,0x0
;  RET
