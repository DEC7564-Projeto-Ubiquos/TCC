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
   int periodo=(pulseIn(RPM_pino, LOW)+pulseIn(RPM_pino, HIGH));//periodo em microsegundos
   if(periodo==0)
   {
      gatilho=true;
      motorLIGADO=false; 
   }
   if((periodo <200000)&&(periodo>0))//300 RPM = carro ligado
   {
      Rpm=(1000000/periodo)*60;//periodo em microsegundos
      if(abs(Rpm-RPMAnt)>1)
      {
          RPMAnt=Rpm;
          //enviaRPM_socket(RPMAnt);
      }  
      motorLIGADO=true;       
   }
   else
   {
      Rpm=0;
      if(abs(Rpm-RPMAnt)>1)
      {
          //enviaRPM_socket(Rpm);
      }         
      RPMAnt=Rpm;
 
   }
}

int leFrequencia() //le a rotação do motor em HZ
{
   int freq=0;
   int ciclo=(pulseIn(RPM_pino, LOW)+pulseIn(RPM_pino, HIGH));
   if((ciclo >0)&&(ciclo<1000000))//frequencia minima 1 HZ
   {
     freq=1000000/ciclo;   //periodo em microsegundos
     //Serial.print(ciclo);  Serial.print(" ");  Serial.println(freq);    
   }
   else
   {
     freq=0;
   }
   return freq;
}
