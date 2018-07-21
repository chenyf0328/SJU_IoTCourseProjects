#define  LEDPin  13  //we will flash this LED

void setup ( void ) {
    Serial.begin( 115200 );
    Serial.println( "in setup" );
    pinMode( LEDPin, OUTPUT );
    digitalWrite( LEDPin, LOW );

    noInterrupts();  //turn off interrupts

    TCNT3=0;
    TCCR3A=0;
    TCCR3B = (1<<CS32) | (1<<CS30);

    OCR3A=1000;
    
    TIMSK3=(1<<TOIE3);
    TIMSK3 |= (1<<OCIE3A);
    
    interrupts();  //turn interrupts back on
}

void loop ( void ) {
    
}

ISR ( TIMER3_COMPA_vect ) {
      digitalWrite( LEDPin, !digitalRead(LEDPin) );
      Serial.print( "ISR(TIMER3_COMPA_vect) " );
      Serial.print(TCNT3);
}

ISR ( TIMER3_OVF_vect ) {
    digitalWrite( LEDPin, !digitalRead(LEDPin) );
    Serial.print( "ISR(TIMER3_OVF_vect) " );
    Serial.print(TCNT3);
}

