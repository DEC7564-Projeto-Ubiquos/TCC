
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{   
     clienteAtual=num;
     
     String altBmp="#A1";
     String temBmp="#T_BMP2";
     String preBmp="#P1000";
     String comBus=("#COMB"+String(combAnt));
     String rPm="#RPM0";
     switch(type) 
     {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            
            break;
        case WStype_CONNECTED: 
        {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocket.sendTXT(num, "Connected");
        }
        break;
        case WStype_TEXT:
            
            Serial.printf("[%u] get Text: %s\n", num, payload);

            if(payload[0] == 'W') 
            {
                modoTESTE=true;
                uint8_t estado = (uint8_t) strtol((const char *) &payload[1], NULL, 16);
                if(estado==0)
                  modoTESTE=false;
                else
                  modoTESTE=true;
                
                Serial.print("modoTTESTE (");Serial.println(modoTESTE);Serial.print(")");
            }
            if(payload[0] == '#') 
            {
              
                if(!cardSD)  // we get RGB data // decode rgb data
                {
                  uint8_t ledR = (uint8_t) strtol((const char *) &payload[1], NULL, 16);
                 
                  analogWrite(LED_R, ledR);   //LED_R , valor(0->255))
                
                }             
            }
            if(payload[0] == '@') 
            {
              uint8_t estadoC = (uint8_t) strtol((const char *) &payload[1], NULL, 0);
              if(!modoTESTE)
              {

               if(estadoC==0)
                  velocidadeVentilador(0);
                else if (estadoC==1)
                  arAuto(1);
                else if (estadoC==2)
                   velocidadeVentilador(1);
                else if (estadoC==4)
                   velocidadeVentilador(2);
                else if (estadoC==8)
                   velocidadeVentilador(3);
                else
                {
                    Serial.print("estadoC b(");Serial.println(estadoC,BIN);Serial.print(")");  
                } 
              }
              else
                boolean rel=writePCF8574(~estadoC); 
            }
            if(payload[0] == '!') 
            {
              webSocket.sendTXT(num,bilhete2);
              
            }      
            break;  
            case WStype_BIN:
              Serial.printf("[%u] get binary length: %u\n", num, length);
              hexdump(payload, length);
            break;         
    }    
}
/*
void index2()
{
      page2="";
      page2+=("<html>");
      page2+=(       "<style>");              
      page2+=(       "</style>");              
      page2+=(       "<head>"); 
      page2+=(       "</head>");
      page2+=("<body>");
      page2+=(    "Sou  Index2 <br><br>");
      page2+=(    "sem implementa&ccedil&atildeo!");            
      page2+=("</body>");              
      page2+=("</html>");
  
}*/
