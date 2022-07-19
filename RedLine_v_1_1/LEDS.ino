void configuraLED()
{
  if(!cardSD)
  {
    pinMode(LED_G,OUTPUT);
    pinMode(LED_R,OUTPUT);
    pinMode(LED_Ref,OUTPUT);
    digitalWrite(LED_Ref,0);  
  }
  
}

void loopSinalLED()
{
    cont++;
    if(cont>1700)
    {
      cont=0;
      led=~led;
      analogWrite(LED_G,led);
    } 

}
void testaLed()
{
  
  //testa G
  for(int i=0; i<200; i++)
  {    
    analogWrite(LED_G,i);
    delay(1);                      
  }
  digitalWrite(LED_G,LOW);
   //testa R
  for(int i=0; i<200; i++)
  {    
    analogWrite(LED_R,i);
    delay(1);                      
  }
  digitalWrite(LED_R,LOW);
   //testa B
  for(int i=0; i<200; i++)
  {    
    analogWrite(LED_B,i);
    delay(1);                      
  }
  digitalWrite(LED_B,LOW);

}

void testaLedMixCores()
{
  for(int i=0; i<200; i=i+10)
  {    
    analogWrite(LED_B,i);
    delay(10); 
    for(int j=0; j<200; j=j+10)
    {    
      analogWrite(LED_R,j);
      delay(10); 
      for(int k=0; k<200; k=k+10)
      {    
        analogWrite(LED_G,k);
        delay(10); 
      }
     }
    
   }
   digitalWrite(LED_G,LOW);
   digitalWrite(LED_R,LOW);
   digitalWrite(LED_B,LOW);  
  
}
