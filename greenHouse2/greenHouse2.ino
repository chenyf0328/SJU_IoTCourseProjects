/* Author: Yifan Chen 
 * What percentage of program storage space is used by your program?
 * Sketch uses 559722 bytes (42%) of program storage space. Maximum is 1310720 bytes. So it's 42.70%.
*/

#include <WiFi.h>

#define analogInputLDR 32
#define analogInputLM35 33
#define LEDAlert 19
#define SpeakerAlert 18

#define ssid "FiOS-YCO4C"             //wifi network name
#define pwd  "ash2072ion4978mini"     //wifi password

#define K 25        // total records stored
#define THIGHTemp 195
#define TLOWTemp 150

// for speaker
#define DUR 300
#define CH 0

static WiFiServer server(80);

int T = 2000;       // initial T as 2 seconds
int cnt = 1;
String recordsLight[K+1];       // store 25 Light records
String recordsTemp[K+1];        // store 25 Temp records
String recordsTime[K+1];        // store 25 Time records

boolean alertFlag = false;
String alertTime = "";

static int alertRecord = 0;            // using for judge if alert happens

void setup() {
  Serial.begin(115200);
  
  pinMode(analogInputLDR, INPUT);
  pinMode(analogInputLM35, INPUT);
  pinMode(LEDAlert, OUTPUT);
  pinMode(SpeakerAlert, OUTPUT);

  connectToWiFi();

  // start the server
  server.begin();
}

void loop() {
  // generate new record
  prepareRecord();

  //listen for incoming clients/requests, if there's incoming client, client = 1, else client = 0
  WiFiClient client = server.available();
  
  if (!client) {
      delay(200);
      return;
  }
  
  //got a request!
  Serial.print( "new client: " );
  Serial.println( client.remoteIP().toString() );
  handleRequest(client);

  // clear alert
  alertFlag = false;

  //close the connection
  client.stop();
  Serial.println( "client disconnected." );
}

// parameter: 1 stands for THIGHTemp, 0 stands for TLOWTemp
void alert(int speakerMode){
  ledcAttachPin( SpeakerAlert, CH );
  if (speakerMode==0)
    ledcWriteTone( CH, 415 );
  else
    ledcWriteTone( CH, 659 );
  
  for (int i=0; i<5; i++) {
    digitalWrite(LEDAlert, HIGH);
    delay(300);
    digitalWrite(LEDAlert, LOW);
    delay(300);
  }
  ledcDetachPin( SpeakerAlert );
}

// not used.
void alertLED(){
  for (int i=0; i<4; i++) {
    digitalWrite(LEDAlert, HIGH);
    delay(300);
    digitalWrite(LEDAlert, LOW);
    delay(300);
  }
}

// not used. parameter: 1 stands for THIGHTemp, 0 stands for TLOWTemp
void alertSpeaker(int speakerMode){
  ledcAttachPin( SpeakerAlert, CH );
  for (int i=0; i<4; i++) {
    if (speakerMode==0){
      ledcWriteTone( CH, 415 ); delay( DUR*1.3 );
      ledcWriteTone( CH, 554 ); delay( DUR*1.3 );
      ledcWriteTone( CH, 659 ); delay( DUR*1.3 );
    }
    else{
      ledcWriteTone( CH, 659 ); delay( DUR*1.3 );
      ledcWriteTone( CH, 554 ); delay( DUR*1.3 );
      ledcWriteTone( CH, 415 ); delay( DUR*1.3 );
    }
  }
  ledcDetachPin( SpeakerAlert );
}

void prepareRecord() {
  // prepare for the record
  //String current = String("light=") + String(analogRead(analogInputLDR), DEC) + String("    temp=") + String(analogRead(analogInputLM35), DEC) + String("    current time=") + String(millis());
  String light = String(analogRead(analogInputLDR), DEC);
  String temp = String(alertRecord=analogRead(analogInputLM35), DEC);
  String currentTime = String(millis());

  // judge if send the alert
  if (alertRecord <= TLOWTemp){
    alertFlag = true;
    alertTime = currentTime;

    alert(1);
    
//    // led
//    alertLED();
//    
//    // speaker
//    alertSpeaker(1);
  }
  if (alertRecord >= THIGHTemp){
    alertFlag = true;
    alertTime = currentTime;

    alert(0);
    
//    // led
//    alertLED();
//    
//    // speaker
//    alertSpeaker(0);
  }
  
  if (cnt != K+1){
    recordsLight[cnt] = light;
    recordsTemp[cnt] = temp;
    recordsTime[cnt] = currentTime;
    cnt++;
  }
  else{
    for (int i=2; i<=K; i++){
      recordsLight[i-1] = recordsLight[i];
      recordsTemp[i-1] = recordsTemp[i];
      recordsTime[i-1] = recordsTime[i];
    }
    recordsLight[K] = light;
    recordsTemp[K] = temp;
    recordsTime[K] = currentTime;
  }
  delay(T);
}

static void connectToWiFi(void) {
    Serial.println( "Connecting to WiFi network: " + String(ssid));

    WiFi.begin(ssid, pwd);
    while (WiFi.status() != WL_CONNECTED) {      //wait until connected
        delay(1000);
        Serial.print(".");
    }

    Serial.println();
    Serial.println( "WiFi connected!" );
    Serial.print( "IP address: " );
    Serial.println( WiFi.localIP() );
}

static void outputHTML ( WiFiClient& client ) {
    //HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK),
    // a content-type so the client knows what's coming, and then a blank line

    client.println( "HTTP/1.1 200 OK" );
    client.println( "Content-type:text/html" );
    client.println();

    //output the content of the HTTP response
    client.println( "<html>" );
    client.println("   <meta http-equiv='refresh' content='15' > ");
    client.println( "  <head><title> Professor Grevera rocks! </title></head>" );
    client.println( "  <body>" );

    // check if alert exists
    if (alertFlag == true)
      showAlert(client);
    
    client.println( "    <table border='1' style='width:300px'>" );
    client.println( "      <caption><h2>25 records of light and temp</h2></caption>" );
    client.println( "      <tr>" );
    client.println( "        <th>ID</th><th>Time</th><th>Light</th><th>Temp</th>" );
    client.println( "      </tr>" );

    // use loop to print K records
    for (int i=1; i<=K; i++){
      client.println( "    <tr>" );
      client.println( "      <td>" + String(i, DEC) + "</td>");
      client.println( "      <td>" + recordsTime[i] + "</td>");
      client.println( "      <td>" + recordsLight[i] + "</td>");
      client.println( "      <td>" + recordsTemp[i] + "</td>");
      client.println( "    </tr>" );
    }

    client.println( "    </table>" );
    
    client.println( "  </body>" );
    client.println( "</html>" );

    client.println();    //the HTTP response ends with another blank line
}

static void showAlert ( WiFiClient& client ) {
  // judge what kind of alert
  if (alertRecord <= THIGHTemp)
    client.println( "      <h2><font color='red'>The most current alert: Temperature is too low!!! Happened time is " + alertTime + ".</font></h2>" );
  else
    client.println( "      <h2><font color='red'>The most current alert: Temperature is too high!!! Happened time is " + alertTime + ".</font></h2>" );
}

static void handleRequest ( WiFiClient& client ) {
    String ln = "";    //holds incoming data from client
    while (client.connected()) {               //loop while client is connected
        if (!client.available())    continue;  //wait until next char is available
        char c = client.read();                //read one char
        Serial.write( c );                     //echo it out
        if (c != '\n') {
            if (c == '\r')    continue;        //ignore cr
            ln += c;                           //add to ln
            //check for client request
//            if      (ln.endsWith("GET /H"))  digitalWrite( LED_PIN, HIGH );  //turn LED on
//            else if (ln.endsWith("GET /L"))  digitalWrite( LED_PIN, LOW  );  //turn LED off
        } else {
            //if ln is blank, we got two newlines in a row.
            if (ln.length() == 0) {
                //then end of the client HTTP request, so send a response.
                outputHTML(client);
                break;
            }
            ln = "";    //if newline, then reset ln
        }
    }
}



