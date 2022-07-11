void rotinaLigado()
{
    contLigado++;
    
    if (contLigado==600)//contabiliza tempo ligado
    {      
         cont++;   
         gatilho=false;
         if(cont=100)//regular tempo de atualização
         {
            atualizaDados();
             cont=0;
         }
         leRpm();   
         contLigado=0;  
    }   
}

void rotinaDesligado()
{
  contDesligado++;
  if(contDesligado==1700)
  {
    contDesligado=0;  
    int clientWsNum = webSocket.connectedClients();
    if(clientWsNum>0)
    {
      cont++;
      if(cont==170)
      {
        atualizaDados();
        cont=0;
      }  
      
    } 
    else
      cont=0;
  }
}
