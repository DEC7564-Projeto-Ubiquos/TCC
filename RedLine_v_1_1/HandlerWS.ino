
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
        {    
            Serial.printf("[%u] get Text: %s\n", num, payload);

            
            if(payload[0] == '#') 
            {
                uint8_t ledR = (uint8_t) strtol((const char *) &payload[1], NULL, 0); 
                if(!cardSD && modoTESTE)  
                {                             
                   analogWrite(LED_B, ledR); 
                   arAUTO=false;
                   temperaturaAR=ledR;
                                  
                }   
                else
                {
                   arAUTO=false;
                   temperaturaAR=ledR;
                }          
            }
            if(payload[0] == '$') 
            {
                uint8_t ledB = (uint8_t) strtol((const char *) &payload[1], NULL, 0);
                if(!cardSD && modoTESTE)  
                {    
                  analogWrite(LED_B, ledB);   //LED_B , valor(0->100))
                  controleCooler(ledB);
                } 
                else
                {
                  controleCooler(ledB);
                }          
            }
            if(payload[0] == '@') 
            {
              uint8_t estadoC = (uint8_t) strtol((const char *) &payload[1], NULL, 0);
              Serial.print("estadoC ");Serial.println(estadoC); 
              if(!modoTESTE)
              {

               if(estadoC==0) //todos controles desligados
               {
                  arAUTO=false;
                  velocidadeVentilador(0);
               }
                else if (estadoC==1)//liga Ar automatico difença de temperatura entre cabine e fora
                {
                  arAUTO=true;
                }
                else if (estadoC==2)
                {
                   velocidadeVentilador(1);
                   arAUTO=false;
                }
                else if (estadoC==4)
                {
                   velocidadeVentilador(2);
                   arAUTO=false; 
                }
                else if (estadoC==8)
                {
                   velocidadeVentilador(3);
                   arAUTO=false; 
                }
                else
                {
                    Serial.print("estadoC ");Serial.print(estadoC,BIN); Serial.println(")");
                } 
              }
              else
                boolean rel=writePCF8574(~estadoC); 
            }
            if(payload[0] == '!') 
            {
              uint8_t estado =  payload[1];
              webSocket.sendTXT(num,bilhete2);
              modoTESTE=false;
              if(estado==35)
                modoTESTE=true;
              else
                modoTESTE=false;
                
              Serial.print("modoTESTE ");Serial.println(modoTESTE);
            }  
        } 
                
            break;  
            case WStype_BIN:
              Serial.printf("[%u] get binary length: %u\n", num, length);
              hexdump(payload, length);
            break;         
    }    
}
