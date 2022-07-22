void enviaRPM_socket(int rpm)
{
    String rPm=("#RPM"+String(rpm));
    int clientWsNum = webSocket.connectedClients();
    if(clientWsNum>0)
      webSocket.broadcastTXT(rPm);
      //webSocket.sendTXT(clienteAtual,combu);  
}

void leRpm() //le a rotação do motor em RPM
{
   int Rpm=0;
   //int periodo=(pulseIn(RPM_pino, LOW)+pulseIn(RPM_pino, HIGH));//periodo em microsegundos
   int periodo=(pulseIn(RPM_pino, LOW)*2);//periodo em microsegundos
   if(periodo==0)
   {
      gatilho=true;

   }
   if((periodo<=200000)&&(periodo>0))//300 RPM = carro ligado
   {
      Rpm=(1000000/periodo)*60;//periodo em microsegundos
      if(abs(Rpm-RPMAnt)>1)//filtro
      {
          RPMAnt=Rpm;
          //enviaRPM_socket(RPMAnt);
      }  
      motorLIGADO=true; 
      gatilho=false;      
   }
   else
   {
      RPMAnt=Rpm;
      motorLIGADO=false;;
   }
}

int leFrequencia() //le a rotação do motor em HZ
{
   int freq=0;
   int ciclo=(pulseIn(RPM_pino, LOW)+pulseIn(RPM_pino, HIGH));
   if((ciclo >0)&&(ciclo<1000000))//frequencia minima 1 HZ
   {
     freq=1000000/ciclo;   //periodo em microsegundos   
   }
   else
   {
     freq=0;
   }
   return freq;
}
