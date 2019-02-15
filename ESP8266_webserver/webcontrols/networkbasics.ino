void startDns()
{

  /* Setup the DNS server redirecting all the domains to the apIP */
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);

  
}
void startOTA() { // Start the OTA service
  ArduinoOTA.setHostname(OTAName);
  ArduinoOTA.setPassword(OTAPassword);

  ArduinoOTA.onStart([]() {
    if(DEBUG) Serial.println("Start");

  });
  ArduinoOTA.onEnd([]() {
    if(DEBUG) Serial.println("\r\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    if(DEBUG) Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    if(DEBUG) Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) if(DEBUG) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) if(DEBUG) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) if(DEBUG) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) if(DEBUG) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) if(DEBUG) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  if(DEBUG) Serial.println("OTA ready\r\n");
}



void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incoming websocket message, go to function 'webSocketEvent'
  if(DEBUG) Serial.println("WebSocket server started.");
}



void startMDNS() { // Start the mDNS responder
  MDNS.begin(mdnsName);                        // start the multicast domain name server
  if(DEBUG) Serial.print("mDNS responder started: http://");
  if(DEBUG) Serial.print(mdnsName);
  if(DEBUG) Serial.println(".local");
}




/*__________________________________________________________SETUP_FUNCTIONS__________________________________________________________*/

void startWiFi() { // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
  WiFi.softAP(ssid, password);             // Start the access point
  if(DEBUG) Serial.print("Access Point \"");
  if(DEBUG) Serial.print(ssid);
  if(DEBUG) Serial.println("\" started\r\n");

/*

  wifiMulti.addAP("wlan1", "password");
  wifiMulti.addAP("wlan2", "password");

  if(DEBUG) Serial.println("Connecting");
  while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {  // Wait for the Wi-Fi to connect
    delay(250);
    if(DEBUG) Serial.print('.');
  }
  if(DEBUG) Serial.println("\r\n");
  if(WiFi.softAPgetStationNum() == 0) {      // If the ESP is connected to an AP
    if(DEBUG) Serial.print("Connected to ");
    if(DEBUG) Serial.println(WiFi.SSID());             // Tell us what network we're connected to
    if(DEBUG) Serial.print("IP address:\t");
    if(DEBUG) Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
  } else {                                   // If a station is connected to the ESP SoftAP
    if(DEBUG) Serial.print("Station connected to ESP8266 AP");
  }



  if(DEBUG) Serial.println("\r\n");
*/
}
