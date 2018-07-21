/* Author: Yifan Chen */

#include <WiFi.h>

#define analogInputLDR 32
#define analogInputLM35 33

#define ssid "FiOS-YCO4C"             //wifi network name
#define pwd  "ash2072ion4978mini"     //wifi password
#define hostDomain "108.52.18.188"    //internet domain to request from
#define hostDoc "/~george/iot.php?user=yves0328"              //cannot be empty; use "/" if necessary (doc root)
#define hostPort 80

int T = 2000;       // initial T as 2 seconds

void setup() {
  Serial.begin(115200);
  
  pinMode(analogInputLDR, INPUT);
  pinMode(analogInputLM35, INPUT);

  connectToWiFi();
}

void loop() {
//  // Test for LDR and LM35
//  Serial.print("LDR: ");
//  Serial.println(analogRead(analogInputLDR));
//  Serial.print("LM35: ");
//  Serial.println(analogRead(analogInputLM35));
//  Serial.println();
  String LDRValue = String(analogRead(analogInputLDR), DEC);
  String LM35Value = String(analogRead(analogInputLM35), DEC);
  String doc = hostDoc + String("&temp=" + LDRValue + "&light=" + LM35Value);
  
  // Length (with one extra character for the null terminator)
  int str_len = doc.length() + 1;
  // Define char array as the parameter of requestURL()
  char docCharArray[str_len];
  // String to char array
  doc.toCharArray(docCharArray, str_len);
  
  requestURL(hostDomain, docCharArray, hostPort);

  // delay 2 seconds for next data collection
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

static void requestURL (char* host, char* doc, uint8_t port) {
  Serial.println( "----------" );
  Serial.println( "Connecting to domain: " + String(host) );

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
      Serial.println( "connection failed" );
      return;
  }
  Serial.println( "Connected!" );
  Serial.println( "----------" );

  // This will send the request to the server
  client.print( (String) "GET " + doc + " HTTP/1.1\r\n" +
                         "Host: " + String(host) + "\r\n" +
                         "Connection: close\r\n\r\n" );
  unsigned long timeout = millis();
  while (client.available() == 0) {  //wait for response(but not forever)
      if (millis()-timeout > 5000) {
          Serial.println( ">>> Client Timeout !" );
          client.stop();
          return;
      }
  }

  //read all lines of the reply from server and print them
  while (client.available()) {
      String line = client.readStringUntil( '\r' );
      Serial.print( line );
  }

  Serial.println();
  Serial.println( "closing connection" );
  client.stop();
}

