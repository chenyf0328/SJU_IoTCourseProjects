#include <WiFi.h>
//----------------------------------------------------------------------
void setup ( ) {
    Serial.begin( 115200 );
    scanNetworks();
}
//----------------------------------------------------------------------
//based on: https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiScan/WiFiScan.ino
static void scanNetworks ( void ) {
    Serial.println( "scanning..." );
    int n = WiFi.scanNetworks();
    Serial.println( "done" );
    Serial.print( n );
    Serial.println( " network(s) found" );
    for (int i = 0; i < n; i++) {
        Serial.print( i+1 );
        Serial.print( ": " );
        Serial.print( WiFi.SSID(i) );
        Serial.print( " (" );
        Serial.print( WiFi.RSSI(i) );  //RSSI or received signal strength indication from 0 to -100 (best to worst)
        Serial.print( ") " );
        switch (WiFi.encryptionType(i)) {
            case WIFI_AUTH_OPEN :             Serial.print( "open" );             break;
            case WIFI_AUTH_WEP :              Serial.print( "wep" );              break;
            case WIFI_AUTH_WPA_PSK :          Serial.print( "wpa psk" );          break;
            case WIFI_AUTH_WPA2_PSK :         Serial.print( "wpa2 psk" );         break;
            case WIFI_AUTH_WPA_WPA2_PSK :     Serial.print( "wpa wpa2 psk" );     break;
            case WIFI_AUTH_WPA2_ENTERPRISE :  Serial.print( "wpa2 enterprise" );  break;
            case WIFI_AUTH_MAX :              Serial.print( "max" );              break;
            default :                         Serial.print( "?" );                break;
        }
        Serial.println();
    }
}
//----------------------------------------------------------------------
void loop ( void ) {
    Serial.println( "Hello, world!" );
    delay( 10000 );
}

