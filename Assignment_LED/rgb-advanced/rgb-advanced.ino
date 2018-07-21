#define redPin 7
#define greenPin 6
#define bluePin 5

int count=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
}

void loop() {
  // red led blink 3 time
  for (int i=0;i<3;i++){
    setColor(255,0,0);    //red color
    delay(1000);
    digitalWrite(redPin, LOW);
    delay(500);
  }
  
  // green led blink 3 time
  for (int i=0;i<3;i++){
    setColor(0,255,0);    //green color
    delay(1000);
    digitalWrite(greenPin, LOW);
    delay(500);
  }

  // blue led blink 3 time
  for (int i=0;i<3;i++){
    setColor(0,0,255);    //blue color
    delay(1000);
    digitalWrite(bluePin, LOW);
    delay(500);
  }

  // yellow led blink 3 time
  for (int i=0;i<3;i++){
    setColor(255,255,0);  //yellow color
    delay(1000);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    delay(500);
  }
}

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}


