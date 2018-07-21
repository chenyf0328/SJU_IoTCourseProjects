#define ledPin 6

void setup(){
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  double dutyCycle = 1.0;
  int p = (int)(255 * dutyCycle + 0.5);  //0% duty cycle
  analogWrite(ledPin, p);  
}

void loop(){
}

