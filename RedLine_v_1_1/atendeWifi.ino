/*
void atendeWiFi() //*****************CLIENTE WIFI***************************
{
  WiFiClient client = server.available();
    if (!client)
    {
      yield();
      return;
    }
    // Wait until the client sends some data
    Serial.println("new client");
    while (!client.available()) {
    delay(10);
    }
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    
    if (request.indexOf("/leituraDados") != -1) {
    delay(1);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println(bilhete);
    client.stop();
    Serial.println("Client disonnected"); 
    return; 
    }/*
    if (request.indexOf("/arAuto") != -1) 
    {
      delay(1);
      Serial.println(ligaArAuto);
      ligaArAuto=~ligaArAuto;
      if(!ligaArAuto)
        arAuto(false);
      resfria=true;
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println(""); // do not forget this one
      client.stop();
      Serial.println("Client disonnected");
      return;
    }
    if (request.indexOf("/vent0") != -1) 
    {
      delay(1);
      ligaArAuto=false;
      arAuto(false);
      velocidadeVentilador(0);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println(""); // do not forget this one
      client.stop();
      Serial.println("Client disonnected");
      return;
    }
    if (request.indexOf("/vent1") != -1) 
    {
      delay(1);
      ligaArAuto=false;
      arAuto(false);
      velocidadeVentilador(1);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println(""); // do not forget this one
      client.stop();
      Serial.println("Client disonnected");
      return;
    }
    if (request.indexOf("/vent2") != -1) 
    {
      delay(1);
      ligaArAuto=false;
      arAuto(false);
      velocidadeVentilador(2);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println(""); // do not forget this one
      client.stop();
      Serial.println("Client disonnected");
      return;
    }
    if (request.indexOf("/vent3") != -1) 
    {
      delay(1);
      ligaArAuto=false;
      arAuto(false);
      velocidadeVentilador(3);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println(""); // do not forget this one
      client.stop();
      Serial.println("Client disonnected");
      return;
    }
    if (request.indexOf("/ipServAdd") != -1) 
    {
      IPAddress ipServAdd=WiFi.softAPIP();
      delay(1);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println(""); // do not forget this one
        client.println(ipServAdd);
      client.stop();
      Serial.println("Client disonnected");
      return;
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("requisição não válida!");
    client.stop();
    
}*/
