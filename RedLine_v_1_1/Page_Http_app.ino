
void pageApp()
{  
      //**************BILHETE/APP********************
      // ("1 , qui 22-2-2222 8:30, 11 C    , 18         , 101010 Pa, 33 m    , 44       , 55       , 66         , 77      , 1  , Normal,");
      // (Ind, tempo sistema     , temp Sis, Temp Cabine, Pres Atm , Altitude, Temp Fora, Temp Agua, Temp Cooler, Combusti, RPM, Nivel ,");
      //*********************************************
      modoTESTE=0;
      pageAp=" ";
      atualizaDados(); //atualiza dados dos sensores para incluir nessa pagina
      pageAp+=bilhete;
    
}
