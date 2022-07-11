#include <ESP8266WiFi.h>

const char* staSsid = "Guarajuba2";
const char* staPsk  = "guarajuba4321";
const char* apSsid  = "RedLine1";
const char* apPsk   = "12345678";

void wifiConfig()
{ 
  Serial.println("Configurando WIFI");
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(apSsid, apPsk);
  WiFi.begin(staSsid, staPsk);
  Serial.print("connecting to ");
  Serial.println(staSsid); 
  byte counter=0;
  while ((WiFi.status() != WL_CONNECTED) || (counter > 10))//aguarda 5 s para conexão wifi
  {
    delay(500);
    Serial.print(".");
    counter++;
  }
  if(counter>10)
  {
      Serial.println("WiFi NOT connected");
  }
  if  (WiFi.status() == WL_CONNECTED) 
  {
    Serial.println("WiFi connected");
    IPAddress ipLocalAdd=WiFi.localIP();
    // Print the STA address
    Serial.print("Use esta URL para conectar na rede ");
    Serial.print(staSsid);
    Serial.print(": http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  }
  
  IPAddress ipServAdd=WiFi.softAPIP(); 
  // Print the AP address
  Serial.print("Use esta URL para connectar na rede local ");
  Serial.print(apSsid);
  Serial.print(": http://");
  Serial.print(ipServAdd);
  Serial.println("/");

  server.begin();
  Serial.print("HTTP Server iniciou na porta ");
  Serial.println(PORTA);

   //start webSocket server porta 81
   webSocket.begin();
   webSocket.onEvent(webSocketEvent);
   Serial.println("HTTP Server iniciou na porta 81"); 
}
/*
void mdnsStart()
{
  if (MDNS.begin("redline"))
  {
    Serial.println("MDNS responder started: use http://redline.local para consultar o servidor");
  }
}*/
