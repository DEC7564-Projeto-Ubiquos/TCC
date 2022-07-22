void logSDhora()
{
  
  rtc.refresh();
  int rtcDia=rtc.day();
  int rtcMes=rtc.month();
  int rtcAno=rtc.year();
  int rtcHor=rtc.hour();
  int rtcMin=rtc.minute();
  int rtcSec=rtc.second();

  char nome [12];
  String nomeArquivoLog="";
  nomeArquivoLog+=("RL"+String(rtc.year())+String(rtc.month())+String(rtc.day())+".txt");
  nome[((sizeof(nomeArquivoLog)))];
  for(int i=0; i<(sizeof(nomeArquivoLog));i++)
    nome[i]=nomeArquivoLog[i];

  if((rtcMin!=minAnt) && !motorLIGADO && cardSD)//grava 1 bilheteSD a cada hora se motor desligado
  {
    minAnt=rtcMin;
    horaAnt=rtcHor;
    if(minAnt==0)
    {
      indiceSD++;
      atualizaDados();
      if (SD.exists(nome)) 
      {
            Serial.print(nome);
            Serial.println(" existe. gravando...");
            Serial.println(String(indiceSD)+bilheteSD);
            File RedLineLog = SD.open(nome, FILE_WRITE);
            if (RedLineLog) 
            {
              RedLineLog.println(String(indiceSD)+bilheteSD);
              RedLineLog.close();
            }
            else 
            {
              Serial.print("erro abrindo arquivo ");
              Serial.println(nome);
            }
        }
        else 
        {
              Serial.print(nome);
              Serial.println(" não existe. criando...");
              File RedLineLog=SD.open(nome, FILE_WRITE);
              RedLineLog.close();  
              RedLineLog = SD.open(nome, FILE_WRITE);
              if (RedLineLog) 
              {
                RedLineLog.println(String(indiceSD)+bilheteSD);
                RedLineLog.close();
                //return 1;
              }
              // if the file isn't open, pop up an error:
              else 
              {
                Serial.print("erro abrindo ");
                Serial.println(nome);
              }
        } 
    }
    else if(horaAnt==0)//zera indice 0:00h
      indiceSD=0;
      
  }  
}
void logSDminuto(int rtcDia, int rtcMes, int rtcAno, int rtcHor, int rtcMin )
{ 
  char nome [12];
  String nomeArquivoLog="";
  nomeArquivoLog+=("RL"+String(rtcAno)+String(rtcMes)+String(rtcDia)+".txt");
  nome[((sizeof(nomeArquivoLog)))];
  for(int i=0; i<(sizeof(nomeArquivoLog));i++)
    nome[i]=nomeArquivoLog[i];
  if(horaAnt!=rtcHor)
    horaAnt=rtcHor;
  if(horaAnt==0 && minAnt==0)//zera indice 0:00h
     indiceSD=0;
     
  if(cardSD)//grava 1 bilheteSD a cada minuto se motor ligado
  {    
      indiceSD++;
      if (SD.exists(nome)) 
      {
            Serial.print(nome);
            Serial.println(" existe. gravando...");
            Serial.println(String(indiceSD)+bilheteSD);
            File RedLineLog = SD.open(nome, FILE_WRITE);
            if (RedLineLog) 
            {
              RedLineLog.println(String(indiceSD)+bilheteSD);
              RedLineLog.close();
            }
            else 
            {
              Serial.print("erro abrindo arquivo ");
              Serial.println(nome);
            }
        }
        else 
        {
              Serial.print(nome);
              Serial.println(" não existe. criando...");
              File RedLineLog=SD.open(nome, FILE_WRITE);
              RedLineLog.close();  
              RedLineLog = SD.open(nome, FILE_WRITE);
              if (RedLineLog) 
              {
                RedLineLog.println(String(indiceSD)+bilheteSD);
                RedLineLog.close();
              }
              // if the file isn't open, pop up an error:
              else 
              {
                Serial.print("erro abrindo ");
                Serial.println(nome);
              }
          } 
      }
 }  
