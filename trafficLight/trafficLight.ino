#define greenHighAndRedCT 2
#define redHighAndGreenCT 3
#define yellow 4
#define IRSensor 8

void setup() {
  Serial.begin(115200);
  
  pinMode(IRSensor,INPUT);
  
  pinMode(greenHighAndRedCT,OUTPUT);
  pinMode(redHighAndGreenCT,OUTPUT);
  pinMode(yellow,OUTPUT);

  digitalWrite(greenHighAndRedCT, HIGH);
}

void loop() {
  // let highway green for a while
  delay(5000);

  // if IR sensor detects a car coming, changing light function will be called
  if (digitalRead(IRSensor)==0){
    change();
  }
}

void change(){
    // highway light changes from green to yellow and then red, meanwhile, CT light changes from red to green
    highwayFromGreenToRed();
    delay(5000);
    
    // CT light changes from green to yellow and then red, meanwhile, highway light changes from red to green
    highwayFromRedToGreen();
}

void highwayFromGreenToRed(){
  digitalWrite(greenHighAndRedCT, LOW);
  
  digitalWrite(yellow, HIGH);
  delay(2000);
  digitalWrite(yellow, LOW);

  digitalWrite(redHighAndGreenCT, HIGH);
}

void highwayFromRedToGreen(){
  digitalWrite(redHighAndGreenCT, LOW);
  
  digitalWrite(yellow, HIGH);
  delay(2000);
  digitalWrite(yellow, LOW);

  digitalWrite(greenHighAndRedCT, HIGH);
}
