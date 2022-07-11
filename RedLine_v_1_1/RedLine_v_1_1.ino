//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <OneWire.h>
#include <WebSocketsServer.h>
#include <uRTCLib.h>
#include <Adafruit_BMP280.h>

#define PORTA 80
#define RPM_pino 5 //GPIO5=D1 //sensor de rpm
#define Nivel_pino 16 //GPIO16=D0 //sensor de nível do radiador

#define LED_R    12 //D6
#define LED_G    14 //D5
#define LED_B    15 //D8
#define LED_Ref  13 //D7

#define RPM_pino 5 //GPIO5=D1 //sensor de rpm

//***************prototipos************************

void indexPage();
void rootPage();
void tempPage();
void handleURIinit();
void wifiConfig();
boolean testeI2Cdevices();
void atualizaDados();
void leRpm();
boolean testeOneWireDevices();
void loopSinalLED();
void pageApp();
void velocidadeVentilador(int velocidade);
void arAuto(boolean estado);
void le18b20();

//***************************************************
ESP8266WebServer server(PORTA);
WebSocketsServer webSocket = WebSocketsServer(81); 
Adafruit_BMP280 bmp280;
uRTCLib rtc;

OneWire ds(4); //GPIO 4 = pino D2 barramento onewire

String bilhete="1,2,3,4,5,6,7,8,9,10,11,12,13";
String bilhete2="13,12,11,10,9,8,7,6,5,4,3,2,1";

unsigned int tempo=0;

int RPMAnt=0;
int combAnt=0;
int tempBmp280=17;
int presBmp280=100100.10;
int altiBmp280=13;
int temp18b20_0;//temperatura fora
int temp18b20_1;//temperatura agua
int temp18b20_2;//temperatura cooler frio
int temp18b20_3;//temperatura cooler quente

boolean motorLIGADO=false;
boolean BMP280=true;
boolean PCF=false;
boolean gatilho=true;
boolean ligaArAuto=false;
boolean resfria=false;
boolean cardSD=false;
boolean modoTESTE=false;

unsigned int contLigado=0;
unsigned int contDesligado=0;
unsigned int indice=0;
unsigned int cont=0;

uint8_t clienteAtual;
uint8_t led=0;

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

  //indexPage();
  //rootPage();
  //tempPage();
  //handleURIinit();
  //mdnsStart(); 
  pinMode(LED_G,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_Ref,OUTPUT);
  digitalWrite(LED_Ref,0);
  le18b20();
  atualizaDados();

}

void loop() 
{
  /*
   cont++;
   if(cont==1700)
   {
    led=~led;
    digitalWrite(LED_R,led);
    cont=0;
    atualizaDados();

    
   }   */
   webSocket.loop();
   server.handleClient();

  if(gatilho && digitalRead(RPM_pino)==0)
    motorLIGADO=true;
  if(motorLIGADO)
    rotinaLigado();
  else
    rotinaDesligado();  

   if((cont==60)&&(motorLIGADO))
    {
        //int freq=leFrequencia();
        //enviaRPM_socket(freq);
        leRpm();
        
    }   

  //MDNS.update();

}
