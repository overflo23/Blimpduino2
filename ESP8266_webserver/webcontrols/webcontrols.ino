/*
 * oh sweet jesus, what a clusterfuck.
 * 
 * i was working on this code for 4 days straight because the wifi was instable 
 * and it looked like the code to send files form spiffs was broken.
 * turns out i had to change the compiler settings to:
 * 
 * Flash size 4M (1M SPIFFS)
 * Debug Port: disabled
 * Debug Level: none 
 * Iwip variant: 2 (higher bandwidth)   <- important!
 * vtables: "flash"
 * cpu freq: 160 mhz
 * exceptions: disabled
 * upload speed: 921600
 * erase flash: erase all flash contents
 * 
 */

#define DEBUG 0   //set to 0 for live usage. this outputs all kind of information on the serial.

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <WebSocketsServer.h>


// for captive portal
#include <DNSServer.h>



// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;



ESP8266WiFiMulti wifiMulti;       // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);       // create a web server on port 80
WebSocketsServer webSocket(81);    // create a websocket server on port 81

File fsUploadFile;                                    // a File variable to temporarily store the received file

const char *ssid = "OLLEDROHNE"; // The name of the Wi-Fi network that will be created
const char *password = "blimpduino";   // The password required to connect to it, leave blank for an open network

const char *OTAName = "blimpduino";           // A name and a password for the OTA service
const char *OTAPassword = "blimpduino";

const char* mdnsName = "blimpduino"; // Domain name for the mDNS responder



/* Soft AP network parameters */    
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);







/*__________________________________________________________SETUP__________________________________________________________*/

void setup() {



  
  Serial.begin(115200);        // Start the Serial communication to send messages to the computer
  delay(1000);
  Serial.println("\r\nstarting up.. \r\n");



  startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection

  startDns();
  
  startOTA();                  // Start the OTA service
  
  startSPIFFS();               // Start the SPIFFS and list all contents

  startWebSocket();            // Start a WebSocket server
  
  startMDNS();                 // Start the mDNS responder

  startServer();               // Start a HTTP server with a file read handler and an upload handler
  
}

/*__________________________________________________________LOOP__________________________________________________________*/



void loop() {
  webSocket.loop();                           // constantly check for websocket events
  server.handleClient();                      // run the server
  serialWebsocketBridge();
  ArduinoOTA.handle();                        // listen for OTA events
  dnsServer.processNextRequest();  
}






void startSPIFFS() { // Start the SPIFFS and list all contents
  SPIFFS.begin();                             // Start the SPI Flash File System (SPIFFS)
  if(DEBUG) Serial.println("SPIFFS started. Contents:");
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {                      // List the file system contents
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      if(DEBUG) Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    if(DEBUG) Serial.printf("\n");
  }
}





/*__________________________________________________________HELPER_FUNCTIONS__________________________________________________________*/

String formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
}




/** Is this an IP? */
boolean isIp(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}

/** IP to String? */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}




