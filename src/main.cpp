#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <AsyncElegantOTA.h>


#define LED_1 D1 // GPIO 5
#define LED_2 D2 // GPIO 4
#define LED_3 D4 // GPIO 2


uint8_t LED1pin = D1;
bool LED1status = LOW;

uint8_t LED2pin = D2;
bool LED2status = LOW;

uint8_t LED3pin = D4;
bool LED3status = LOW;




const char* ssid     = "BLACKLEAKZ-AP";
const char* password = "123456789";

#define mDns = "blackleakz"

AsyncWebServer server(80);





String SendHTML(uint8_t led1stat,uint8_t led2stat, uint8_t led3stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server || LED Control</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  if(led3stat)
  {ptr +="<p>LED3 Status: ON</p><a class=\"button button-off\" href=\"/led3off\">OFF</a>\n";}
  else
  {ptr +="<p>LED3 Status: OFF</p><a class=\"button button-on\" href=\"/led3on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}




void URLHandler() {
  // AsyncWebserver URI/Route Handler

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML(LED1status,LED2status,LED3status));
      LED1status = LOW;
      LED2status = LOW;
      LED3status = LOW;
      Serial.println("GPIO 2 Status: OFF | GPIO4 Status: OFF || GPIO5 Status: OFF");
  });


  server.on("/led1on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML(true,LED2status, LED3status));
      LED1status = HIGH;
      Serial.println("GPIO5 Status: ON");
  });

  server.on("/led1off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML(false,LED2status, LED3status));
      LED1status = LOW;
      Serial.println("GPIO5 Status: OFF");
  });
  
  server.on("/led2on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML(LED1status, LED3status,true));
      LED2status = HIGH;
      Serial.println("GPIO4 Status: ON");
  });

  server.on("/led2off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML(LED1status, LED3status,false));
      LED2status = LOW;
      Serial.println("GPIO4 Status: OFF");
  });
  
  server.on("/led3on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML(LED2status, LED1status,true));
      LED3status = HIGH;
      Serial.println("GPIO2 Status: ON");
  });

  server.on("/led3off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML(LED2status, LED1status, false));
      LED3status = LOW;
      Serial.println("GPIO2 Status: OFF");
  });
  


  server.begin();
}






void setup() {
  
  Serial.begin(115200);
  Serial.println("Console > Serial communication of LED-Picture ESP8266 started!");


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);


  if (!MDNS.begin("blackleakz")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(356);
      }
    }
  Serial.println("mDNS responder started");


  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();  
  Serial.print("Console > AP IP address: ");
  Serial.println(IP);

  Serial.println(WiFi.localIP());

  AsyncElegantOTA.begin(&server);
  URLHandler();

  
}
 



void loop(){  

   MDNS.update();


  if(LED1status) 
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }
  
  if(LED2status)
  {
    digitalWrite(LED2pin, HIGH);
  }
  else
  {
    digitalWrite(LED2pin, LOW);
  }

  if(LED3status)
  {
    digitalWrite(LED3pin, HIGH);
  }
  else
  {
    digitalWrite(LED3pin, LOW);
  }
}



