 /* Atendimento de requisições GET do servidor 
 * As funções desse código foram extraídas ou modificadas 
 * do exemplo HelloServer da biblioteca ESP8266webserver 
 */
String http_menu="";
String http_Lj="";
String pageAp="";
String Ws_escuro="";
String Ws_teste="";

void handleRoot() {

  server.send(200, "text/plain", http_menu); 
}

void handleURIinit()
{
    rootPage();
    indexPage();   
    indexWsPage();
    indexWsTeste();
    pageApp();
    
//**************URI root*********************** 
  server.on("/", handleRoot);
  
//**************URI index*********************** 
  server.on("/index", []() 
  {
     Serial.println("Handler : Requisição Web /index");  
     indexPage(); 
     delay(1);
     server.send(200, "text/html", http_Lj);
  });
  //**************URI index*********************** 
  server.on("/index2", []() 
  {
     Serial.println("Handler : Requisição Web /index2");  
     delay(1);
     server.send(200, "text/html", Ws_escuro);
  });
 //**************URI index*********************** 
  server.on("/index3", []() 
  {
     Serial.println("Handler : Requisição Web /index3");  
     delay(1);
     server.send(200, "text/html", Ws_teste);
  });
//**************URI leituraDados***********************
  server.on("/leituraDados", []() 
  {
      Serial.println("Handler : Requisição Web /leituraDados");
      pageApp();
      delay(1);
      server.send(200, "text/html", pageAp);
  });

//**************URI ARAUTO***********************   
  server.on("/arAuto", []() 
  {
    Serial.println("Handler : Requisição Web /arAuto");
    ligaArAuto=~ligaArAuto;
    if(!ligaArAuto)
      arAuto(false);
    resfria=true;
    server.send(200, "text/html", "OK");
  });
  
//**************URI VENT0***********************   
  server.on("/vent0", []() 
  {
    Serial.println("Handler : Requisição Web /vent0");
    ligaArAuto=false;
    arAuto(false);
    velocidadeVentilador(0);
    server.send(200, "text/html", "OK");
  });

  
//**************URI VENT1***********************  
  server.on("/vent1", []()
  {
    Serial.println("Handler : Requisição Web /vent1");
    ligaArAuto=false;
    arAuto(false);
    velocidadeVentilador(1);
    server.send(200,  "text/html", "OK");
  });

  
//**************URI VENT2***********************
  server.on("/vent2", []()
  {
    Serial.println("Handler : Requisição Web /vent2");
    ligaArAuto=false;
    arAuto(false);
    velocidadeVentilador(2);
    server.send(200,  "text/html", "OK");
  });


//**************URI VENT3***********************
  server.on("/vent3", []()
  {
    Serial.println("Handler : Requisição Web /vent3");
    ligaArAuto=false;
    arAuto(false);
    velocidadeVentilador(3);
    server.send(200,  "text/html", "OK");
  });

  
  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
