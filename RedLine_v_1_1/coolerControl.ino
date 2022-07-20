
void controleCooler(uint8_t temperaturaCooler)
{
  //int coolerF=temp18b20_2;
  //int coolerQ=temp18b20_3;
  
  if (temperaturaCooler==0)
    cooler(false);
  else 
  {
    //Serial.print("coolerQ ");Serial.println(coolerQ);
    if(temp18b20_3 > 50)//proteção TEC 50 graus cooler Quente
    {
      ventoinha(true);
      cooler(false);
    }
    else
    {
      cooler(true);
      if((temp18b20_3-temp18b20_2)>10)//liga ventuinha se diferença maior do que 10 graus coolerQuente-collerFrio
        ventoinha(true);
      else
        ventoinha(false);
      if(temp18b20_2<=(temperaturaCooler-2))
        cooler(false);
      else if(temp18b20_2>=(temperaturaCooler+2))
        cooler(true);
    }
  }
}

void cooler(boolean estadoCooler)
{
  uint8_t condiAnterior=saidaPCF8574;
  if (estadoCooler == false)// desliga TEC1
  {
    uint8_t temp=0;
    temp=(1<<4);
    saidaPCF8574=saidaPCF8574 | temp; //desliga TEC1 bitwise
    if(condiAnterior != saidaPCF8574) //escreve no PCF8574 apenas se houve alteração
      transmissaoPCF8574(saidaPCF8574); 
      
  }  
  else //liga o TEC1
  {
    uint8_t temp=0;
    temp=~(1<<4);
    saidaPCF8574=saidaPCF8574 & temp; //liga TEC1, modifica o bit TEC1
    if(condiAnterior!=saidaPCF8574) //escreve no PCF8574 apenas se houve alteração
      transmissaoPCF8574(saidaPCF8574);
  }
}
void ventoinha(boolean estadoVentoinha)
{
  uint8_t condiAnterior=saidaPCF8574;
  if (estadoVentoinha == false)// desliga Ventoinha
  {
    uint8_t temp=0;
    temp=(1<<5);
    saidaPCF8574=saidaPCF8574 | temp; //desliga TEC1 bitwise
    if(condiAnterior != saidaPCF8574) //escreve no PCF8574 apenas se houve alteração
      transmissaoPCF8574(saidaPCF8574); 
      
  }  
  else //liga Ventoinha
  {
    uint8_t temp=0;
    temp=~(1<<5);
    saidaPCF8574=saidaPCF8574 & temp; //liga TEC1, modifica o bit TEC1
    if(condiAnterior!=saidaPCF8574) //escreve no PCF8574 apenas se houve alteração
      transmissaoPCF8574(saidaPCF8574);
  }
}
