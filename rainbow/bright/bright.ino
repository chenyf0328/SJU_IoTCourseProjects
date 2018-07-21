#define analogInputPin A3                     // pot range from 0-683
#define analogOutputPin 7

void setup() {
  Serial.begin(115200);

  pinMode(analogInputPin, INPUT);
  pinMode(analogOutputPin, OUTPUT);
}

void loop() {
  int level = readPin()*255;                  // generate a value range from 0-255
  analogWrite(analogOutputPin, level);
}

double readPin(){
  return analogRead(analogInputPin)/683.0;    // read the input pin, range from 0-1
}
