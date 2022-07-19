/*
#include <SD.h>
#include <SPI.h>

boolean leGravaDados()
{ 
  int tempRtc;
  int tempBmp280;
  int presBmp280;
  int altiBmp280;
  int RPM;
  rtc.refresh();
  delay(20);
  uint8_t atual=rtc.month();
  char nome[12];
  if(mesAtual!=atual);
  {
    nomeArquivoLog="";
    nomeArquivoLog+=("RLog"+String(rtc.year())+String(rtc.month())+".txt");
    //Serial.println(sizeof(nomeArquivoLog));
    nome[((sizeof(nomeArquivoLog)))];
    for(int i=0; i<(sizeof(nomeArquivoLog));i++)
      nome[i]=nomeArquivoLog[i];
    //Serial.println(nome);
    mesAtual=rtc.month();
  }  
  tempRtc=rtc.temp();
  tempBmp280=bmp280.readTemperature();
  delay(20);
  presBmp280=bmp280.readPressure();
  delay(20);
  altiBmp280=bmp280.readAltitude();
  delay(20);
  le18b20(); 
  RPM=leRpm();
  String tupla="";
  tupla+=(String(indice)+" "+String(rtc.year())+"-"+String(rtc.month())+"-"+String(rtc.day())+" "+String(rtc.hour())+":"+String(rtc.minute())
  +" "+String(rtc.dayOfWeek())+" "+String(tempRtc)+" "+" "+String(tempBmp280)+" "+String(presBmp280)+" "+String(altiBmp280)+" "+String(temp18b20_0)
  +" "+String(temp18b20_1)+" "+String(temp18b20_2)+" "+String(temp18b20_3)+" "+String(RPM)+"\n");
  Serial.println(tupla);
  //String tupla=bilhete;
  if(tupla.length()>30)
  { 
    if (CARTAOSD)
    {
        if (SD.exists(nome)) 
        {
          Serial.print(nome);
          Serial.println(" existe. gravando...");
          File RedLineLog = SD.open(nome, FILE_WRITE);
          if (RedLineLog) 
          {
            RedLineLog.println(tupla);
            RedLineLog.close();
            //Serial.println(tupla);
            //piscaLed(corCi);
            indice++;
            return 1;
          }
          else 
          {
            Serial.print("erro abrindo arquivo ");
            Serial.println(nome);
            //piscaLed(corAm);
            return 0;
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
            RedLineLog.println(tupla);
            RedLineLog.close();
            indice++;
            //piscaLed(corCi);
            return 1;
          }
          // if the file isn't open, pop up an error:
          else 
          {
            Serial.print("erro abrindo ");
            Serial.println(nome);
            //piscaLed(corAm);
            return 0;
          }
         }
       }
   }
}*/
