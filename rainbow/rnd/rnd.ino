#define analogRedPin 2
#define analogGreenPin 3
#define analogBluePin 4

// array contains all color set
int rgb[18][3]={
              {248,12,18},{238,17,0},{255,51,17},{255,68,34},{255,102,68},
              {255,153,51},{254,174,45},{204,187,51},{208,195,16},{170,204,34},
              {105,208,37},{34,204,170},{18,189,185},{17,170,187},{68,68,221},
              {51,17,187},{59,12,189},{68,34,153}
             };

long randNumber;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  pinMode(analogRedPin, OUTPUT);
  pinMode(analogGreenPin, OUTPUT);
  pinMode(analogBluePin, OUTPUT);
}

void loop() {
  randNumber = random(0,18);        // generate a number from 0~17
  
  analogWrite(analogRedPin, rgb[randNumber][0]);
  analogWrite(analogGreenPin, rgb[randNumber][1]);
  analogWrite(analogBluePin, rgb[randNumber][2]);

  delay(250);
}
