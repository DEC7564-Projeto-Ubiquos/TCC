void rotinaLigado()
{
    int clientWsNum = webSocket.connectedClients();
    if (clientWsNum>0)//
    {    
       leRpm();
       atualizaDados();
       logBilhete();       
    }   
    else
    {
      leRpm();
      contLigado=0;
      logBilhete();
    }
}

void rotinaDesligado()
{
    RPMAnt=0;
    motorLIGADO=false;
    gatilho=true;
    int clientWsNum = webSocket.connectedClients();
    if(clientWsNum>0)
    {
      contDesligado++;
      if(contDesligado==170)//
      {
        atualizaDados();
        logBilhete();
        contDesligado=0;
      }        
    } 
    else
    {
      contDesligado=0;
      logBilhete();      
    }
}

void logBilhete()
{
  //if(motorLIGADO&&(secRtc==0))//logs a cada min
  if(motorLIGADO)
  {
        digitalWrite(LED_R,0); 
        led=~led;
        digitalWrite(LED_G,led); 
  
  }
  //if(!motorLIGADO&&(minRtc==0))//log a cada hora
  if(!motorLIGADO)
  {
        digitalWrite(LED_G,0); 
        led=~led;
        digitalWrite(LED_R,led); 
  }
}
