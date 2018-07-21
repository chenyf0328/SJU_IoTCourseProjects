/* 
  Author: Yifan Chen
  Answers:
  A) Darker is indicated by a higher value.
  B) Higher temp is indicated by a higher value.
*/

#define analogInputLDR 32
#define analogInputLM35 33

int T = 2000;       // initial T as 2 seconds

void setup() {
  Serial.begin(115200);
  
  pinMode(analogInputLDR, INPUT);
  pinMode(analogInputLM35, INPUT);
}

void loop() {
  Serial.print("LDR: ");
  Serial.println(analogRead(analogInputLDR));
  Serial.print("LM35: ");
  Serial.println(analogRead(analogInputLM35));
  Serial.println();
  delay(T);
}
