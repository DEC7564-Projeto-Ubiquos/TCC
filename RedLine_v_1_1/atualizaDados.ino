
void atualizaDados()
{ 
  int RPM=RPMAnt;
  String agua=" ";
  if(digitalRead(D0)==LOW)
    agua="Alerta!";
  else
    agua="Normal";
 
  leComb();
  le18b20(); 

  //***************bmp280***********
  tempBmp280=bmp280.readTemperature();
  presBmp280=bmp280.readPressure();
  altiBmp280=bmp280.readAltitude();
  //********************************
 
  //***************RTC**************
              rtc.refresh();
              int tempRtc=rtc.temp()/100;
              String diaSemana="";
              int semana=rtc.dayOfWeek();
              if(semana==1)
                diaSemana="dom ";
              else if(semana==2)
                diaSemana="seg ";
              else if(semana==3)
                diaSemana="ter ";
              else if(semana==4)
                diaSemana="qua ";
              else if(semana==5)
                diaSemana="qui ";
              else if(semana==6)
                diaSemana="sex ";
              else if(semana==7)
                diaSemana="sab ";
              else
                diaSemana=" ";
              int diaRtc=rtc.day();
              int mesRtc=rtc.month();
              int anoRtc=rtc.year();
              int horaRtc=rtc.hour();
              int minRtc=rtc.minute();
              String minutos="";
              if(minRtc<10)
                minutos=("0"+String(minRtc));
              else
                minutos=(String(minRtc));
              int secRtc=rtc.second();
//********************************               
 
  indice++;
  if((horaRtc==0) && (minRtc==0))   //zera o index diariamente a 0:00 h
    indice=0;

    
      //**************TUPLA/HTTP********************
      // ("1 , qui 22-2-2222 8:30, 11 C    , 18         , 101010 Pa, 33 m    , 44       , 55       , 66          ,     77      ,   88    , 1  , Normal,");
      // (Ind, tempo sistema     , temp Sis, Temp Cabine, Pres Atm , Altitude, Temp Fora, Temp Agua, Temp CoolerF, Temp CoolerQ, Combusti, RPM, Nivel ,");
      //*********************************************
  
 String tupla = (String(indice)+", "+diaSemana+" "+String(diaRtc)+"-"+String(mesRtc)+"-"+String(anoRtc)+"  "+String(horaRtc)+":"
                  +minutos+", "+String(tempRtc)+", "+String(tempBmp280)+", "+String(presBmp280)+" hPa, "
                  +String(altiBmp280)+" m, "+String(temp18b20_0)+", "+String(temp18b20_1)+", "+String(temp18b20_2)+", "
                +String(temp18b20_3)+", "+String(combAnt)+", "+String(RPM)+", "+agua);
                
  //**************BILHETE/APP********************
      // ("1 , qui 22-2-2222 8:30, 11 C    , 18         , 101010 Pa, 33 m    , 44       , 55       , 66         , 77      , 1  , Normal,");
      // (Ind, tempo sistema     , temp Sis, Temp Cabine, Pres Atm , Altitude, Temp Fora, Temp Agua, Temp CoolerF, Combusti, RPM, Nivel ,");
      //*********************************************              
 bilhete = (" "+String(indice)+", "+diaSemana+" "+String(diaRtc)+"-"+String(mesRtc)+"-"+String(anoRtc)+"  "+String(horaRtc)+":"
                  +minutos+", "+String(tempRtc)+" C, "+String(tempBmp280)+", "+String(presBmp280)+" Pa, "
                  +String(altiBmp280)+" m, "+String(temp18b20_0)+", "+String(temp18b20_1)+", "+String(temp18b20_2)+", "+String(combAnt)+", "+String(RPM)+", "+agua);

 String socketSend=(" #RTC_S"+diaSemana+" "+"#RTC_D"+String(diaRtc)+" "+"#RTC_M"+String(mesRtc)+" "+"#RTC_A"+String(anoRtc)+" "+"#RTC_H"+String(horaRtc)+" "
                  +"#RTC_m"+minutos+" "+"#RTC_T"+String(tempRtc)+" "+"#T_BMP"+String(tempBmp280)+" "+"#P_BMP"+String(presBmp280)+" "
                  +"#A_BMP"+String(altiBmp280)+" "+"#T_EXT"+String(temp18b20_0)+" "+"#T_RAD"+String(temp18b20_1)+" "+"#T_COF"+String(temp18b20_2)+" "
                +"#T_COQ"+String(temp18b20_3)+" "+"#COMB"+String(combAnt)+" "+"#RPM"+String(RPM)+" "+"#ALM"+agua);
                
bilhete2=socketSend;

int clientWsNum = webSocket.connectedClients();
    if(clientWsNum>0)
      webSocket.broadcastTXT(bilhete2);

}
