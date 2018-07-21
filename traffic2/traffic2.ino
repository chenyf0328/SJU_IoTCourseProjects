#define RedHigh 2
#define YellowHigh 3
#define GreenHigh 4
#define RedCT 5
#define YellowCT 6
#define GreenCT 7

#define interruptPin 21

volatile int state = LOW;

void setup() {
  Serial.begin(115200);
  
  pinMode(RedHigh,OUTPUT);
  pinMode(YellowHigh,OUTPUT);
  pinMode(GreenHigh,OUTPUT);
  pinMode(RedCT,OUTPUT);
  pinMode(YellowCT,OUTPUT);
  pinMode(GreenCT,OUTPUT);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), isr, FALLING);    // if IR sensor detects a car coming, proximity sensor from 1 to 0, interrupt function isr will be called

  digitalWrite(GreenHigh, HIGH);
  digitalWrite(RedCT, HIGH);
}

void loop() {
  // let highway green for a while
  delay(5000);

  if (state == LOW)
    change();
}

void isr(void){
  state = LOW;
}

void change(){
  // highway light changes from green to yellow and then red, meanwhile, CT light changes from red to green
  highwayFromGreenToRed();
  delay(5000);
  
  // CT light changes from green to yellow and then red, meanwhile, highway light changes from red to green
  highwayFromRedToGreen();

  // reset state to High
  state = HIGH;
}

void highwayFromGreenToRed(){
  digitalWrite(GreenHigh, LOW);
  
  digitalWrite(YellowHigh, HIGH);
  delay(2000);
  digitalWrite(YellowHigh, LOW);

  digitalWrite(RedHigh, HIGH);
  digitalWrite(RedCT, LOW);
  digitalWrite(GreenCT, HIGH);
}

void highwayFromRedToGreen(){
  digitalWrite(GreenCT, LOW);
  
  digitalWrite(YellowCT, HIGH);
  delay(2000);
  digitalWrite(YellowCT, LOW);

  digitalWrite(RedCT, HIGH);
  digitalWrite(RedHigh, LOW);
  digitalWrite(GreenHigh, HIGH);
}
