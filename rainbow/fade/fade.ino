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

long randNumber=0, randNumberLast=0;

int K=5;                            // the number of fade steps

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  pinMode(analogRedPin, OUTPUT);
  pinMode(analogGreenPin, OUTPUT);
  pinMode(analogBluePin, OUTPUT);

  randNumber = random(0,18);        // generate a number from 0~17
  randNumberLast = randNumber;
}

void loop() {
  randNumber = random(0,18);        // generate a number from 0~17
  double intervalRed=0, intervalGreen=0, intervalBlue=0;

  // calculate the intervalRed Number
  intervalRed = rgb[randNumber][0] - rgb[randNumberLast][0];
  intervalRed /= K;

  // calculate the intervalGreen Number
  intervalGreen = rgb[randNumber][1] - rgb[randNumberLast][1];
  intervalGreen /= K;

  // calculate the intervalBlue Number
  intervalBlue = rgb[randNumber][2] - rgb[randNumberLast][2];
  intervalBlue /= K;

  int red=rgb[randNumberLast][0], green=rgb[randNumberLast][1], blue=rgb[randNumberLast][2];

  for (int i=0;i<K;i++){
    red=red+intervalRed;
    green=green+intervalGreen;
    blue=blue+intervalBlue;
    analogWrite(analogRedPin, round(red));
    analogWrite(analogGreenPin, round(green));
    analogWrite(analogBluePin, round(blue));

    delay(250);
  }

  randNumberLast = randNumber;
}
