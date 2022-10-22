/* 
Calculations (for 1.6s): 
  System clock 16 Mhz and Prescalar 1024;
  Timer 1 speed = 16Mhz/1024 = 15.6 Khz    
  Pulse time = 1/15.6 Khz =  64us  
  Count up to = 1.6s / 64us = 25 000 (so this is the value the OCR register should have)*/  

int incr=0; 
int btt=0;

const float rapportCycliqueVoulu0  = 0.25;   // Soit 25%
const float rapportCycliqueVoulu1 = 0.625;   // Soit 75%
const float rapportCycliqueVoulu2 = 0.875;   // Soit 75%
const float valeurMaxRegistreOCR1x = pow(2,8) - 1; 

void main() {

  DDRB = 0b00000110;
 
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR0A = 0;                 // Reset entire TCCR1A to 0 
  TCCR0B = 0;                 // Reset entire TCCR1B to 0
 
  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */  
  TCCR0B |= 0b00001111;
  TCCR0A |= 0b00000011;         //Set CS12 to 1 so we get prescalar 1024  
 
  
  /*3. We enable compare match mode on register A*/
  //TIMSK1 |= 0b00000010;        //Set OCIE1A to 1 so we enable compare match A 
  
  /*4. Set the value of register A to 31250*/
  //OCR1A = 25000;             //Finally we set compare register A to this value  
  //TCNT1 = 0;            // Mise du timer1 à zéro
  while(1){
    if ((PINB & 0b00001000)==0)
    { 
      if (incr==0){

        // *********************************************************************
      // Mise en marche du générateur PWM sur la sortie D9 (broche OC1A du µC)
      // *********************************************************************
      //  Mode | COM1A1 | COM1A0 | RÉSULTAT  
      //  1er  |    0   |    0   | PWM stoppé
      //  2ème |    0   |    1   | PWM stoppé ou "autobasculant", suivant la valeur de WGM13
      //  3ème |    1   |    0   | PWM en marche "normal"      <====== c'est le mode qui nous intéresse
      //  4ème |    1   |    1   | PWM en marche "inversé"
      // *********************************************************************  
      OCR0A &= ~ (1<<7);
      OCR0A = rapportCycliqueVoulu0 * valeurMaxRegistreOCR1x;
      TCCR0A |= 0b10000000;  // Mise en marche du PWM sur la sortie D9, en mode "normal"
      incr=incr+1;
      btt=0;
      }
      else if(incr==1) {
        OCR0A &= ~ (1<<7);
        OCR0A = rapportCycliqueVoulu1 * valeurMaxRegistreOCR1x;
        TCCR0A |= 0b10000000; 
        incr=incr+1;
        btt=0;
        }
      else if(incr==2)
      {
        OCR0A &= ~ (1<<7);
        OCR0A = rapportCycliqueVoulu2 * valeurMaxRegistreOCR1x;
        TCCR0A |= 0b10000000; 
        incr=0;
        btt=0;
      }
    }
  } 
}