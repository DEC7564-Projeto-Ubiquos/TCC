

void velocidadeVentilador(int velocidade)
{
  switch(velocidade)
  {
    case 0:
            {
              byte temp=0;
              temp=~(1<<1);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 1 
              //Serial.print("Velocidade 0 ");Serial.println(saidaPCF8574,BIN);
              temp=0;
              temp=~(1<<2);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 2
              //Serial.print("Velocidade 0 ");Serial.println(saidaPCF8574,BIN);
              temp=0;
              temp=~(1<<3);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 3 
              //Serial.print("Velocidade 0 ");Serial.println(saidaPCF8574,BIN);
              transmissaoPCF8574(saidaPCF8574); 
              break;        
            }
    case 1:
            {
              //piscaLed(corBr);
              byte temp=0;
              temp=~(1<<2);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 2
              //Serial.print("Velocidade 1 ");Serial.println(saidaPCF8574,BIN);
              temp=0;
              temp=~(1<<3);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 3 
              //Serial.print("Velocidade 1 ");Serial.println(saidaPCF8574,BIN);
              transmissaoPCF8574(saidaPCF8574);     
              
              saidaPCF8574=saidaPCF8574 &~ (1<<1); //liga ventilador velocidade 1 
              //Serial.print("Velocidade 1 ");Serial.println(saidaPCF8574,BIN);
              transmissaoPCF8574(saidaPCF8574);
              break; 
            }
              
    case 2:
            {
              //piscaLed(corBr);
              byte temp=0;
              temp=~(1<<1);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 1 
              //Serial.print("Velocidade 2 ");Serial.println(saidaPCF8574,BIN);
              temp=0;
              temp=~(1<<3);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 3 
              //Serial.print("Velocidade 2 ");Serial.println(saidaPCF8574,BIN);
              transmissaoPCF8574(saidaPCF8574);
               
              saidaPCF8574=saidaPCF8574 &~ (1<<2); //liga ventilador velocidade 2 
              //Serial.print("Velocidade 2 ");Serial.println(saidaPCF8574,BIN);
              transmissaoPCF8574(saidaPCF8574);
              
               break; 
            }
    case 3:
            {
              //piscaLed(corBr);
              byte temp=0;
              temp=~(1<<1);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 1 
              //Serial.print("Velocidade 3 ");Serial.println(saidaPCF8574,BIN);
              temp=0;
              temp=~(1<<2);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 2
              //Serial.print("Velocidade 3 ");Serial.println(saidaPCF8574,BIN);
              transmissaoPCF8574(saidaPCF8574);
              
              saidaPCF8574=saidaPCF8574 &~ (1<<3); //liga ventilador velocidade 3 
              //Serial.print("Velocidade 3 ");Serial.println(saidaPCF8574,BIN);
              transmissaoPCF8574(saidaPCF8574);
              break; 
            }
    default: break;
  }
}

void arAuto(boolean estado)
{
  if (estado == false)
  {
    byte temp=0;
    temp=~(1<<0);
    saidaPCF8574=saidaPCF8574 |~ temp; //desliga ar
    velocidadeVentilador(0);//desliga ventilador 
  }  
  else
  { 
     //piscaLed(corAz);
     int diferencaTemperatura=0;
     diferencaTemperatura = (temp18b20_0-temp18b20_3);
     //Serial.println(diferencaTemperatura);
     if(diferencaTemperatura > 10)
     {
       byte temp=0;
       temp=~(1<<0);
       saidaPCF8574=saidaPCF8574 |~ temp; //desliga ar
       velocidadeVentilador(1);
     }
     else if((diferencaTemperatura > 2) && (diferencaTemperatura <= 5))
     {
       saidaPCF8574=saidaPCF8574 &~ (1<<0); //liga ar
       velocidadeVentilador(1);
     }
     else if((diferencaTemperatura >= -5) && (diferencaTemperatura <= 2))
     {
       saidaPCF8574=saidaPCF8574 &~ (1<<0); //liga ar
       velocidadeVentilador(1);
     }
     else if(diferencaTemperatura < -5)
     {
       velocidadeVentilador(1);
       saidaPCF8574=saidaPCF8574 &~ (1<<0); //liga ar 
     }
     else
  return;    
  }
}
