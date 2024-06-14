
// @file WebServer.ino
// @brief Example implementation using the ESP8266 WebServer.
//
// See also README.md for instructions and hints.
//
// Changelog:
// 21.07.2021 creation, first version

#include <Arduino.h>
#include <ESP8266WebServer.h>



// mark parameters not used in example
#define UNUSED __attribute__((unused))

// TRACE output simplified, can be deactivated here
#define TRACE(...) Serial.printf(__VA_ARGS__)

// name of the server. You reach it using http://webserver
#define HOSTNAME "webserver"

// local time zone definition (Berlin)
#define TIMEZONE "CET-1CEST,M3.5.0,M10.5.0/3"

// need a WebServer for http access on port 80.
ESP8266WebServer server(80);

// The text of builtin files are in this header file
#include "builtinfiles.h"

const char* ssid = "yashema494";
const char* passPhrase = "e494@skyhr";
//Serial Channel object to selectively use ports


// ===== Simple functions used to answer simple GET requests =====

// This function is called when the WebServer was requested without giving a filename.
// This will redirect to the file index.htm when it is existing otherwise to the built-in $upload.htm page
void handleRedirect() {
  TRACE("Redirect...");
  String url = "/index.htm";

  server.sendHeader("Location", url, true);
  server.send(302);
}  // handleRedirect()


// Setup everything to make the webserver work.

void radarStatus(){
  //Read the data at Serial1 RX, TX pins on arduino Mega
  //Function will run as soon as request is made, it will read serial value and send it
  delay(40);
  int len = Serial.available();
  String str = "";
  for(int i = 0; i < len; i++){
    char c = Serial.read();
    
    if((c >= '0' && c <= '9') || c == '-' || c == '+'){
        if(str.length() == 2)break;
        str+=c;
    }
  }
  if(str.length() == 0){str = "None";}
  Serial.print("Got data from arduino uno ");
  Serial.println(str);
  server.send(200, "text/javascript; charset=utf-8", str); 
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");  // send an initial string
    delay(300);
  }
}


void setup(void) {
  delay(3000);  // wait for serial monitor to start completely.

  // Use Serial port for some trace information from the example
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  //establish contact with arduino uno
  //establishContact();

  pinMode(D3, INPUT);
  TRACE("Starting WebServer for radar...\n");


  // start WiFI
  WiFi.mode(WIFI_STA);
  if (strlen(ssid) == 0) {
    WiFi.begin();
  } else {
    WiFi.begin(ssid, passPhrase);
  }

  // allow to address the device by the given name e.g. http://webserver
  WiFi.setHostname(HOSTNAME);

  TRACE("Connect to WiFi...\n");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    TRACE(".");
  }
  TRACE("connected.\n");

  // Ask for the current time using NTP request builtin into ESP firmware.
  TRACE("Setup ntp...\n");
  configTime(TIMEZONE, "pool.ntp.org");

  TRACE("Register service handlers...\n");

  // serve a built-in htm page
  server.on("/$upload.htm", []() {
    server.send(200, "text/html", FPSTR(uploadContent));
  });

  // register a redirect handler when only domain name is given.
  server.on("/", HTTP_GET, handleRedirect);

  // register some REST services
  server.on("/radarStatus", HTTP_GET, radarStatus);

  // enable CORS header in webserver results
  server.enableCORS(true);

  // enable ETAG header in webserver results from serveStatic handler
  server.enableETag(true);

  // handle cases when file is not found
  server.onNotFound([]() {
    // standard not found in browser.
    server.send(404, "text/html", FPSTR(notFoundContent));
  });

  server.begin();
  TRACE("hostname=%s\n", WiFi.getHostname());
}  // setup


// run the server...
void loop(void) {
  server.handleClient();
  //Serial.println(Serial1.read());
}  // loop()

