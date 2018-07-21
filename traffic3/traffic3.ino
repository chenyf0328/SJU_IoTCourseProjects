/*  author: Yifan Chen
 *  date: 3/31/2018
Question:
(a) If the 2560 has a clock rate of 16 MHz, how long in ns is each clock tick?
  T=1/F
   =(1/16)*10^(-6)
   =62.5ns

(b) If TCCR3B has no prescaling, what is the length of time in ms before overflow occurs?
  T=(1/F)*65536
   =(1/16)*10^(-6)*65536
   =4.096ms

(c) If TCCR3B has a prescaling factor of 1024, what is the time in sec before overflow occurs?
  T=(1/F)*1024*65536
   =(1/16)*10^(-6)*1024*65536
   =4.1943s

(d) How could you provide longer delays (approximate is fine)?
  We can use a counter to calculate how many times overflow happened. If you want to let the timer be approximately 12 seconds, 
  we can set counter++ in method ISR: ISR ( TIMER3_OVF_vect ) { counter++; }, then use if (counter==3) to judge if it’s 12 seconds passed. 
  All in all, we can use counter to provide longer delays. If the prescaling factor is 1024, then the whole delay time is 4.1943*counter.
*/

#define RedHigh 2
#define YellowHigh 3
#define GreenHigh 4
#define RedCT 5
#define YellowCT 6
#define GreenCT 7

#define interruptPin 21

// false: proximity sensor detected cars. Otherwise, keep high way always green
boolean sensor_flag = false;

// used to implement delay using timer, Green->Yellow: 2s, Yellow->Red: 5s
int cnt = -1;

void setup() {
  Serial.begin(115200);
  
  pinMode(RedHigh,OUTPUT);
  pinMode(YellowHigh,OUTPUT);
  pinMode(GreenHigh,OUTPUT);
  pinMode(RedCT,OUTPUT);
  pinMode(YellowCT,OUTPUT);
  pinMode(GreenCT,OUTPUT);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_Sensor, FALLING);    // if IR sensor detects a car coming, proximity sensor from 1 to 0, interrupt function isr will be called

  noInterrupts();  //turn off interrupts
  
  TCNT3 = 0;  //reset timer to 0
  TCCR3A = 0;  //use simply as counter/timer
  
  TCCR3B =  (1 << CS32) | (1 << CS30);  // divide (slow) by 1024, if overflow, whole time is 4.1s, ((1/16)*10^(-6)*1024*65536=4.1s
  TCCR3B |= (1 << WGM32);        // enable CTC (Clear Timer on Compare) mode for OCR3A

  OCR3A = 16384;  //set desired timer count
  
  TIMSK3 = ( 1 << TOIE3 );  //enable Timer 3 overflow interrupt
  TIMSK3 |= (1 << OCIE3A);  //enable Output Compare A Match Interrupt Enable

  interrupts();  //turn interrupts back on

  // initial lights
  digitalWrite(GreenHigh, HIGH);
  digitalWrite(RedCT, HIGH);
}

void loop() {
  
}

void ISR_Sensor(void){
  sensor_flag = true;
  digitalWrite(GreenHigh, LOW);
  digitalWrite(YellowHigh, HIGH);
}

ISR ( TIMER3_COMPA_vect ) {
  if (sensor_flag == true){

    // means 1s passed
    cnt++;
    
    //Test
    Serial.println(cnt);

    // after 2s. High way: yellow turns off, red turns on; CT: red turns off, green turns on
    if (cnt==2){
      digitalWrite(YellowHigh, LOW);
      digitalWrite(RedHigh, HIGH);
      
      digitalWrite(RedCT, LOW);
      digitalWrite(GreenCT, HIGH);
    }

    // after 5s. CT: green turns off, yellow turns on
    if (cnt==7){
      digitalWrite(GreenCT, LOW);
      digitalWrite(YellowCT, HIGH);
    }

    // after 2s. CT: yellow turns off, red turns on. High way: red turns off, green turns on 
    if (cnt==9){
      digitalWrite(YellowCT, LOW);
      digitalWrite(RedCT, HIGH);
      
      digitalWrite(RedHigh, LOW);
      digitalWrite(GreenHigh, HIGH);
      
      cnt=-1;                  // clear cnt
      sensor_flag = false;     // means there's no external interrupt now
    }
  }
}

ISR ( TIMER3_OVF_vect ) {
  
}
