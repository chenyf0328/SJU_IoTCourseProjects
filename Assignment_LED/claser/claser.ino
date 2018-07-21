/*
 * In this program, I implement a light chaser in order of red, green. blue, green and red.
 */
#define redPin 7
#define greenPin 6
#define bluePin 5
#define greenPin2 4
#define redPin2 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin2,OUTPUT);
  pinMode(redPin2,OUTPUT);
}

void loop() {
  digitalWrite(redPin, HIGH);   // red light turn on
  delay(1000);
  digitalWrite(redPin, LOW);    // red light turn off

  digitalWrite(greenPin, HIGH);   // green light turn on
  delay(1000);
  digitalWrite(greenPin, LOW);    // green light turn off

  digitalWrite(bluePin, HIGH);   // blue light turn on
  delay(1000);
  digitalWrite(bluePin, LOW);    // blue light turn off

  digitalWrite(greenPin2, HIGH);   // green2 light turn on
  delay(1000);
  digitalWrite(greenPin2, LOW);    // green2 light turn off

  digitalWrite(redPin2, HIGH);   // red2 light turn on
  delay(1000);
  digitalWrite(redPin2, LOW);    // red2 light turn off
}


