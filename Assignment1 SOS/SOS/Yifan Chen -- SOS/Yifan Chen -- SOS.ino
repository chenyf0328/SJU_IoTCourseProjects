#define interV 500
#define pause 2000
#define ledPin 13

//if true, short. If false, short.
static boolean flag=true;
// interval 1000, long. interval 500 short.
static int interval=1000;
static int count=0;

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(13,OUTPUT);
}

void loop(void) {
  // put your main code here, to run repeatedly:
  if (flag)
    interval=500;
  else
    interval=1000;
  
  digitalWrite(ledPin,LOW);
  delay(interV);
  digitalWrite(ledPin,HIGH);    //led turned on 1
  delay(interval);
  digitalWrite(ledPin,LOW);
  delay(interV);
  digitalWrite(ledPin,HIGH);    //led turned on 2
  delay(interval);
  digitalWrite(ledPin,LOW);
  delay(interV);
  digitalWrite(ledPin,HIGH);    //led turned on 3
  delay(interval);
  digitalWrite(ledPin,LOW);

  if (flag)
    flag=false;
  else
    flag=true;

  count++;

  if (count==3){
    flag=true;
    count=0;
    delay(pause);
  }
}
