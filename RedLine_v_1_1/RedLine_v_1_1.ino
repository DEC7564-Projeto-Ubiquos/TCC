#include <ESP8266WebServer.h>
#include <Wire.h>
#include <OneWire.h>
#include <WebSocketsServer.h>
#include <uRTCLib.h>
#include <Adafruit_BMP280.h>
#include <SD.h>

#define PORTA 80
#define RPM_pino 5 //GPIO5=D1 //sensor de rpm
#define Nivel_pino 16 //GPIO16=D0 //sensor de nível do radiador

#define ChipS 15 // chip select SD card

#define RPM_pino 5 //GPIO5=D1 //sensor de rpm

//***************prototipos************************

void indexPage();
void pageApp();
void rootPage();
void tempPage();
void handleURIinit();
void wifiConfig();
boolean testeI2Cdevices();
void atualizaDados();
void leRpm();
boolean testeOneWireDevices();
void velocidadeVentilador(int velocidade);
void arAuto(boolean estado);
void le18b20();
void logLed();
void arManual(uint8_t temperaturaAr);
void arAuto(boolean estado);
void transmissaoPCF8574(uint8_t val);
void controleCooler(uint8_t temperaturaCooler);
void logSDhora();
void logSDminuto();
void controleAr();

//***************************************************
ESP8266WebServer server(PORTA);
WebSocketsServer webSocket = WebSocketsServer(81); 
Adafruit_BMP280 bmp280;
uRTCLib rtc;

String bilheteSD="1,2,3,4,5,6,7,8,9,10,11,12,13";//log SD
String bilhete="1,2,3,4,5,6,7,8,9,10,11,12,13";//log app e pagina http
String bilheteWs="13,12,11,10,9,8,7,6,5,4,3,2,1";//log pagina Ws

int RPMAnt=0;
int combAnt=0;
int tempBmp280=17;
int presBmp280=100100;
int altiBmp280=13;
int temp18b20_0;//temperatura fora
int temp18b20_1;//temperatura agua
int temp18b20_2;//temperatura cooler frio
int temp18b20_3;//temperatura cooler quente
int contDesligado=0;
int indiceSD=0;
int indice=0;
int minAnt=0;
int horaAnt=0;

boolean motorLIGADO=false;
boolean BMP280=true;
boolean PCF=false;
boolean gatilho=true;
boolean ligaArAuto=false;
boolean cardSD=false;
boolean modoTESTE=false;
boolean arAUTO=false;
boolean COOLER=false;

uint8_t clienteAtual;
uint8_t led=0;
uint8_t temperaturaAR=0;
uint8_t temperaturaCOOLER=0;
uint8_t saidaPCF8574=255;

void setup() 
{
  Serial.begin(9600);

//*********************wificonfig***********************

  wifiConfig(); //configura rede wifi
  handleURIinit();
//***************configura pinos barramento I2C, RPM, Nível********************
   Wire.begin(0,2); //gpio 0 e 2 = D3 e D4 dispositivos i2c = bmp18, zs42, pcf8574
  
   pinMode(RPM_pino,INPUT); //GPIO5 = D1 sensor RPM
   pinMode(Nivel_pino,INPUT); 
 
  if (testeOneWireDevices())
    Serial.println("Dispositivos oneWire estão funcionando");
  else
    Serial.println("falha em dispositivos oneWire");  
  delay(1000);
  
  if (testeI2Cdevices())
    Serial.println("Dispositivos i2c estão funcionando");
  else
    Serial.println("falha em dispositivos i2c");
    
  if (!SD.begin(SS))
    Serial.println("falha SD");
  else
    cardSD=true;

  //configuraLED();
  atualizaDados();

}

void loop() 
{

   webSocket.loop();
   server.handleClient();

  if(gatilho) 
    motorLIGADO=!digitalRead(RPM_pino);

  if(motorLIGADO)
    rotinaLigado();
  else
    rotinaDesligado(); 

  if(COOLER)
    controleCooler(temperaturaCOOLER);

  //controleAr(); 
  //MDNS.update();

}
