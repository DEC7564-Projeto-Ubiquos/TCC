OneWire ds(4); //GPIO 4 = pino D2 barramento onewire

void le18b20()//le todos sensores no baramento onewire
{
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  boolean flag=true;
  int contSensor=0;
  while(flag)
  {
    if ( !ds.search(addr)) 
    {
      ds.reset_search();
      delay(10);
      flag=false;
      return;
    }
    if (OneWire::crc8(addr, 7) != addr[7]) 
    {
        Serial.println("CRC is not valid!");
        return;
    }
   
    // the first ROM byte indicates which chip
    switch (addr[0]) 
    {
      case 0x10:
        type_s = 1;
        break;
      case 0x28:
        type_s = 0;
        break;
      case 0x22:
        type_s = 0;
        break;
      default:
        Serial.println("Device is not a DS18x20 family device.");
        return;
    } 
   
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end  
    delay(10);
    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);         // Read Scratchpad
   
    for ( i = 0; i < 9; i++) 
    {           
      data[i] = ds.read();
    }
   
    // Convert the data to actual temperature
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s) {
      raw = raw << 3; // 9 bit resolution default
      if (data[7] == 0x10) 
      {
        raw = (raw & 0xFFF0) + 12 - data[6];
      }
    } 
    else 
    {
      byte cfg = (data[4] & 0x60);
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
   
    }
    celsius = (float)raw / 16.0;
    if(contSensor==0)
      temp18b20_0=celsius;
    else if(contSensor==1)
      temp18b20_1=celsius;
    else if(contSensor==2)
      temp18b20_2=celsius;
    else if(contSensor==3)
      temp18b20_3=celsius;
    else
       return;    
    contSensor++;
  }
}

boolean testeOneWireDevices() //verifica a quantidade e os endereços dos sensores no barramento onewire
{
  int i=0;
  byte present = 0;
  byte data[12];
  byte addr[8];
  int cont=0;
  boolean flag=1;
  Serial.println("====================");
  Serial.print("Procurando dispositivos DS18B20...\n\r");
  ds.reset_search();
  while(flag)
  {

    Serial.print("\n\rEncontrado sensor \'DS18B20\' com endereco:\n\r");
    for( i = 0; i < 8; i++) 
    {
      Serial.print("0x");
       if (addr[i] < 16) 
       {
        Serial.print('0');
       }
      Serial.print(addr[i], HEX);
       if (i < 7) 
       {
        Serial.print(", ");
       }     
    }
  
    if ( OneWire::crc8( addr, 7) != addr[7]) 
    {
        Serial.print("CRC nao e valido!\n");
    }
    if (!ds.search(addr)) //detecta fim dos sensores conectados 
    {
        flag=0;//no more sensors on chain, reset search
        cont--;
        ds.reset_search(); // volta para o valor inicial da busca  
    }  
    cont++;
  }
  if (cont>0)
  {
     Serial.println();
     Serial.print("encontrado ");Serial.print(cont);Serial.println(" 18b20");
     Serial.println("====================");
     ds.reset_search();
     return 1;
  }
  else
  {
      Serial.println("Falha OneWire");
      Serial.println("====================");
      return 0;
  }
  
}
