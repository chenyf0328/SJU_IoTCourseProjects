/* Author: Yifan Chen */

#include <WiFi.h>

#define analogInputLDR 32
#define analogInputLM35 33

#define ssid "FiOS-YCO4C"             //wifi network name
#define pwd  "ash2072ion4978mini"     //wifi password

#define K 5

static WiFiServer server(80);

int T = 2000;       // initial T as 2 seconds
int cnt = 1;
String records[K+1];       // store 25 records

void setup() {
  Serial.begin(115200);
  
  pinMode(analogInputLDR, INPUT);
  pinMode(analogInputLM35, INPUT);

  connectToWiFi();
}

void loop() {
  String current = String("light=") + String(analogRead(analogInputLDR), DEC) + String("    temp=") + String(analogRead(analogInputLM35), DEC) + String("    current time=") + String(millis());
  if (cnt != K+1){
//    Serial.println(record);
    records[cnt++] = current;
  }
  else{
    for (int i=2; i<=K; i++){
      records[i-1] = records[i];
    }
    records[cnt-1] = current;
  }
  
//  listen for incoming clients/requests
  WiFiClient client = server.available();
//  Serial.println("client: " + String(client));
  if (!client) {
    delay(T);
    return;
  }

  //got a request!
  Serial.print("new client: ");
  Serial.println(client.remoteIP().toString());
  
  handleRequest(client);
//      outputHTML(client);

  //close the connection
  client.stop();
  Serial.println("client disconnected.");
}

static void connectToWiFi() {
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

static void outputHTML(WiFiClient& client) {
  Serial.println("in outputHTML()");
  //HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK),
  // a content-type so the client knows what's coming, and then a blank line

  client.println( "HTTP/1.1 200 OK" );
  client.println( "Content-type:text/html" );
  client.println();

  //output the content of the HTTP response
    client.println( "<html>" );
    client.println( "  <head><title> Professor Grevera rocks! </title></head>" );
    client.println( "  <body>" );
    client.println( "    <h3> 25 records of light and temp </h3>" );

    // use loop to print K records
    for (int i=1; i<=K; i++){
      client.println( "    <p>" + records[i] + "</p>" );
    }
    
    client.println( "  </body>" );
    client.println( "</html>" );

  client.println();    //the HTTP response ends with another blank line
}

static void handleRequest(WiFiClient& client) {
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
                outputHTML( client );
                break;
            }
            ln = "";    //if newline, then reset ln
        }
    }
}
