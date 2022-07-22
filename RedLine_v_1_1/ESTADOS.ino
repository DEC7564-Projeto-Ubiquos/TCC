void rotinaLigado()
{   
     leRpm();
     atualizaDados();
     controleAr();   
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
      if(contDesligado==170)//gasta tempo para retardar atualização de dados para Ws
      {
        atualizaDados();
        //logLed();
        contDesligado=0;
      }        
    } 
    else
    {
      contDesligado=0;    
    }
    logSDhora();

}
