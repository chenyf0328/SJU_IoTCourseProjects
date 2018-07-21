/*
 * In this program, I use 4 loops to implement blinking in red, green. blue and yellow. 
 * Each color blinks 3 times. Yellow color is red + green
 */
#define redPin 7
#define greenPin 6
#define bluePin 5

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
    digitalWrite(redPin, HIGH);    //red color
    delay(1000);
    digitalWrite(redPin, LOW);
    delay(500);
  }
  
  // green led blink 3 time
  for (int i=0;i<3;i++){
    digitalWrite(greenPin, HIGH);    //green color
    delay(1000);
    digitalWrite(greenPin, LOW);
    delay(500);
  }

  // blue led blink 3 time
  for (int i=0;i<3;i++){
    digitalWrite(bluePin, HIGH);    //blue color
    delay(1000);
    digitalWrite(bluePin, LOW);
    delay(500);
  }

  // yellow led blink 3 time
  for (int i=0;i<3;i++){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);  //yellow color
    delay(1000);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    delay(500);
  }
}


