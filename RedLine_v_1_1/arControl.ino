
void velocidadeVentilador(int velocidade)
{
  switch(velocidade)
  {
    case 0:
            {
              uint8_t veloAnterior=saidaPCF8574;
              uint8_t temp=0;
              temp=~(1<<1);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 1 
              temp=0;
              temp=~(1<<2);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 2
              temp=0;
              temp=~(1<<3);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 3 
               if(veloAnterior!=saidaPCF8574)
               {
                transmissaoPCF8574(saidaPCF8574); 
               }
              break;        
            }
    case 1:
            {
              uint8_t veloAnterior=saidaPCF8574;
              uint8_t temp=0;
              temp=~(1<<2);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 2
              temp=0;
              temp=~(1<<3);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 3                   
              saidaPCF8574=saidaPCF8574 &~ (1<<1); //liga ventilador velocidade 1 
              if(veloAnterior!=saidaPCF8574)
              {
                transmissaoPCF8574(saidaPCF8574);
              }
              break; 
            }
              
    case 2:
            {
              uint8_t veloAnterior=saidaPCF8574;
              uint8_t temp=0;
              temp=~(1<<1);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 1 
              temp=0;
              temp=~(1<<3);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 3 ;            
              saidaPCF8574=saidaPCF8574 &~ (1<<2); //liga ventilador velocidade 2 
              if(veloAnterior!=saidaPCF8574)
              {
                if(writePCF8574(saidaPCF8574));
              }
              
              break; 
            }
    case 3:
            {
              uint8_t veloAnterior=saidaPCF8574;
              uint8_t temp=0;
              temp=~(1<<1);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 1 
              temp=0;
              temp=~(1<<2);
              saidaPCF8574=saidaPCF8574 |~ temp; //desliga ventilador velocidade 2
              saidaPCF8574=saidaPCF8574 &~ (1<<3); //liga ventilador velocidade 3 
              if(veloAnterior!=saidaPCF8574)
              {
                transmissaoPCF8574(saidaPCF8574);
              }
              break; 
            }
    default: break;
  }
}
void compressor(boolean estadoComp)
{
  uint8_t condiAnterior=saidaPCF8574;
  if (estadoComp == false)// desliga o rele 1 do ar condicionado
  {
    uint8_t temp=0;
    temp=1;
    saidaPCF8574=saidaPCF8574 | temp; //desliga ar bitwise
    if(condiAnterior != saidaPCF8574) //escreve no PCF8574 apenas se houve alteração
      transmissaoPCF8574(saidaPCF8574); 
      
  }  
  else //liga o relé 1 do ar condicionado
  {
    uint8_t temp=0;
    temp=~(1<<0);//254 na balada
    condiAnterior=saidaPCF8574;
    saidaPCF8574=saidaPCF8574 & temp; //liga ar, modifica o bit do ar
    if(condiAnterior!=saidaPCF8574) //escreve no PCF8574 apenas se houve alteração
      transmissaoPCF8574(saidaPCF8574);
  }
}

void controleAr()
{
  if(motorLIGADO)
  {
    if (!arAUTO && (temperaturaAR<10))
      compressor(false);
    else if(!arAUTO && (temperaturaAR>10))
      arManual(temperaturaAR);
    if(arAUTO)
      arAuto(true);
  }
  else
  {  
    compressor(false);
    arAUTO=false; 
  }
}

void arManual(uint8_t temperaturaAr)//realiza histerese +- 3 graus em torno da temperatura referência recebida dos aplicativos
{
  
    if(tempBmp280<(temperaturaAr-3))
      compressor(false);
    if(tempBmp280>(temperaturaAr+3))
      compressor(true);
}
void arAuto(boolean estadoArAuto)
{
  if(estadoArAuto == true)
  {
     int diferencaTemperatura=0;
     diferencaTemperatura = (temp18b20_0-tempBmp280);
     if(diferencaTemperatura > 6) //desliga compressor e ventilador 1
     {
        compressor(false); 
        uint8_t valorAnterior=saidaPCF8574;
        uint8_t temp = 14;//0000 1110
        saidaPCF8574=saidaPCF8574 | temp;
        temp = 253;//1111 1101
        saidaPCF8574=saidaPCF8574 & temp;
        if(valorAnterior!=saidaPCF8574)
          transmissaoPCF8574(saidaPCF8574);
     }
     else if((diferencaTemperatura > 2) && (diferencaTemperatura <= 4))//liga compressor e ventilador 1
     {
        compressor(true); //liga ar
        uint8_t valorAnterior=saidaPCF8574;
        uint8_t temp = 14;//0000 1110
        saidaPCF8574=saidaPCF8574 | temp;
        temp = 253;//1111 1101
        saidaPCF8574=saidaPCF8574 & temp;
        if(valorAnterior!=saidaPCF8574)
          transmissaoPCF8574(saidaPCF8574);
     }
     else if((diferencaTemperatura >= -5) && (diferencaTemperatura <= 2))//liga compressor e ventilador 2
     {
        compressor(true); //liga ar
        uint8_t valorAnterior=saidaPCF8574;
        uint8_t temp = 14;//0000 1110
        saidaPCF8574=saidaPCF8574 | temp;
        temp = 251;//1111 1011
        saidaPCF8574=saidaPCF8574 & temp;
        if(valorAnterior!=saidaPCF8574)
          transmissaoPCF8574(saidaPCF8574);

     }
     else if(diferencaTemperatura < -5)//desliga compressor e ventilador 1
     {
        compressor(true); //liga ar 
        uint8_t valorAnterior=saidaPCF8574;
        uint8_t temp = 14;//0000 1110
        saidaPCF8574=saidaPCF8574 | temp;
        temp = 247;//1111 1011
        saidaPCF8574=saidaPCF8574 & temp;
        if(valorAnterior!=saidaPCF8574)
          transmissaoPCF8574(saidaPCF8574);
     } 
     else
        return;
  }
  else
  {
    arAUTO=false;
  }
}
