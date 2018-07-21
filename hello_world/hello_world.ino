void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("in setup");

  //initialize digital pin 13 as an output.
  pinMode(13,OUTPUT);

  Serial.println("out setup");
}

void loop(void) {
  // put your main code here, to run repeatedly:
  Serial.println("in loop");
  
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
  
  Serial.println("out loop");
}
