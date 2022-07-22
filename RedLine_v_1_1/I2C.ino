
#define ee24c32 0x57 //eeprom zs42
#define rtc3231 0x68 //relogio zs42
#define pcf8574 0x20 //acionador relés


uint8_t PCF8574;
uint8_t ZS042;


String versao="RedLine_v_1_1";

boolean startBmp280()
{ 
    
    unsigned status;
    status = bmp280.begin();
    if (!status) 
    {
      Serial.println("Sensor BMP280 nao encontrado !!");
      return 0;
    }
    else
    {
      leBmp280();
      Serial.print("temperatura bmp280 "); Serial.print(tempBmp280); Serial.println(" C");
      Serial.print("pressão bmp280 ");     Serial.print(presBmp280); Serial.println(" hPa");
      Serial.print("altitude bmp280 ");    Serial.print(altiBmp280); Serial.println(" m");
      return 1;
    }
}
void leBmp280()
{ 
      
      tempBmp280=bmp280.readTemperature();
      presBmp280=bmp280.readPressure();
      altiBmp280=bmp280.readAltitude();
  
}
void enviaBmp280_socket()
{
    int tem=bmp280.readTemperature();
    int pre=bmp280.readPressure();
    int alt=bmp280.readAltitude();

    if(abs(tem-tempBmp280)>1)
    {
        String data=("#T_BMP"+String(tem));
        webSocket.broadcastTXT(data);
        data=("#P"+String(pre));
        webSocket.broadcastTXT(data);
        data=("#A"+String(alt));
        webSocket.broadcastTXT(data);
    }
    tempBmp280=tem;
    presBmp280=pre;
    altiBmp280=alt; 
}

byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) //le 1 byte da eeprom
{
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress,1);
    if (Wire.available()) rdata = Wire.read();
    return rdata;
}
void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) //escreve 1 byte da eeprom
{
    int rdata = data;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(rdata);
    Wire.endTransmission();
    delay(10);
}
void testaPCF8574()
{
  int  i=0;
  byte j=0;
  byte k=255;
  byte h=0;
  while(i<8)
  {
    j=pow(2,i);
    h=(j ^ k);
    transmissaoPCF8574(h);
    i++; 
    delay(500);
  }
  while(i>0)
  {
    j=pow(2,i);
    h=(j ^ k); 
    transmissaoPCF8574(h);
    i--;
    delay(500);
  }
  transmissaoPCF8574(255);
  delay(500);
}
boolean writePCF8574(uint8_t val)
{
  if(val<256)
  {
      //Inicia a transmissao para o PCF8574 endereço 32
      Wire.write(0);  //Envia dados pela interface I2C
      Wire.endTransmission();     //Fim da transmissao
      Wire.beginTransmission(pcf8574);
      Wire.write(val);
      Wire.endTransmission();
      return 1;
  }
  else
  {
      Serial.println("falha enviando PCF8574");
      return 0;  
  }
}

void transmissaoPCF8574(uint8_t val)
{
  //Inicia a transmissao para o PCF8574 endereço 32
  
  Wire.beginTransmission(pcf8574);
  Wire.write(0);  //Envia dados pela interface I2C
  Wire.endTransmission();     //Fim da transmissao
  Wire.beginTransmission(pcf8574);
  Wire.write(val);
  Wire.endTransmission();
}
byte lePCF8574()
{
  //Inicia a leitura do PCF8574 
  Wire.beginTransmission(pcf8574);
  Wire.requestFrom(pcf8574, 1);
  byte valorPCF8574;
  if (Wire.available())
  {
    valorPCF8574=Wire.read();
  }
  Wire.endTransmission();
  return valorPCF8574;
}

boolean testeI2Cdevices()//verifica se os dispositivos I2C estão presentes no barramento
{
    uint8_t flag=0;
    unsigned status;
    status = bmp280.begin();
    if (!status) 
    {
      Serial.println("Sensor bmp280 nao encontrado !!");
      Serial.println(bmp280.sensorID(),16);
      //piscaLed(corVm);
      flag=1;
      //while (1) {analogWrite(D8,100);delay(200);analogWrite(D8,0);delay(100);}
      BMP280=false;
    }
    else
    {
      Serial.println("====================");
      Serial.println("bmp280 presente");
      Serial.print("T ");
      Serial.print(bmp280.readTemperature());Serial.println(" C");
      Serial.print("P ");
      Serial.print(bmp280.readPressure());Serial.println(" hPascal");
      Serial.print("P ");
      Serial.print(bmp280.readAltitude());Serial.println(" m");
      Serial.println("====================");
      Serial.println();
      //piscaLed(corVd);
      BMP280=true;
    } 
  rtc.refresh(); //verifica se o zs-042 está presente 
  if (rtc.month()<13)
  {
    Serial.println("====================");
    Serial.println("ZS-042 presente");
    Serial.print(rtc.year());Serial.print("-");Serial.print(rtc.month());Serial.print("-");Serial.print(rtc.day());
    Serial.print(" ");Serial.print(rtc.hour());Serial.print(":");Serial.println(rtc.minute()); 
    Serial.print("T ");Serial.print(rtc.temp()/100);Serial.println(" C");
    for(int i=0; i<(sizeof(versao)+1); i++)
      i2c_eeprom_write_byte(ee24c32,i,versao[i]);
    Serial.print("Firmware ");
    for(int i=0; i<(sizeof(versao)+1); i++)
      Serial.write(i2c_eeprom_read_byte(ee24c32,i));
    Serial.println();
    Serial.println("====================");
    Serial.println();
    //piscaLed(corVd);
    ZS042=true;
  }
  else
  {
    Serial.println("Falha ZS-042");
    //piscaLed(corVm);
    flag=2;
  }
  
  Serial.println("====================");
  Wire.beginTransmission(pcf8574);
  Wire.requestFrom(pcf8574, 1);
  byte valor;
  if (Wire.available())
  {
    valor=Wire.read();
  }
  Wire.endTransmission();
  if(valor>0)
  {
    Serial.println("PCF8574 presente");
    Serial.print("Valor lido na porta = ");
    Serial.println(valor,BIN);
    Serial.println("====================");
    Serial.println();
    //piscaLed(corVd);
    PCF8574=true;
    delay(1);
    saidaPCF8574=(saidaPCF8574 &~ (1<<7));
    transmissaoPCF8574(saidaPCF8574);//liga relé 7
    delay(500);
    byte temp=0;
    temp=~(1<<7);
    saidaPCF8574=saidaPCF8574 |~ temp; //desliga rele 7
    Serial.print("Desliga rele 7 ");Serial.println(saidaPCF8574);
    transmissaoPCF8574(saidaPCF8574);
              
  }
  else
  {
    Serial.println("Falha PCF8574");
    //piscaLed(corVm);
    PCF8574=false;
    flag=3;
  }
  if (flag==0)
    return 1;
  else
    return 0;
}
