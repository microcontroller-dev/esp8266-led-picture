#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>


#define LED_1 D1 // GPIO 5
#define LED_2 D2 // GPIO 4
#define LED_3 D4 // GPIO 2


const char* ssid     = "BLACKLEAKZ-AP";
const char* password = "123456789";



AsyncWebServer server(80);




const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html>
  <head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
 <a href="/update">
  <center><button>Light ON</button></center>
</a>

</body>
</html>
)rawliteral";



void setup() {
  
  Serial.begin(115200);
  Serial.println("Console > Serial communication of LED-Picture ESP8266 started!");


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, LOW);
  delay(300);
  digitalWrite(LED_1, HIGH);

  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  delay(300);
  digitalWrite(5, HIGH);

  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, LOW);
  delay(300);
  digitalWrite(LED_2, HIGH);

  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, LOW);
  delay(300);
  digitalWrite(LED_3, HIGH);



  if(!LittleFS.begin()){
    Serial.println("Console > An error has occured while mounting LittleFS");
    return;
  }






  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();  
  Serial.print("Console > AP IP address: ");
  Serial.println(IP);

  Serial.println(WiFi.localIP());




  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {

      digitalWrite(LED_1, LOW);
      delay(500);
      digitalWrite(LED_1, HIGH);
      delay(1000);
      digitalWrite(LED_1, LOW);

      delay(300);
      digitalWrite(5, LOW);
      delay(500);
      digitalWrite(5, HIGH);
      delay(1000);
      digitalWrite(5, LOW);
 
  });










  server.begin();
}
 



void loop(){  



  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(2000);

}
