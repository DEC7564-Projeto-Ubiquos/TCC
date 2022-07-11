void leComb()
{
    int med=0;
    for(int i=0; i<3 ;i++)
    {
         med+= analogRead(A0);       
          
    }
    med=(med/3)/10;
      
    if(abs(med-combAnt)>1)
    {

       combAnt=med;
    }       
}
void enviaComb_socket()

{
    int med=0;
    for(int i=0; i<3 ;i++)
    {
         med+= analogRead(A0);                 
    }
    med=(med/3)/10;
      
    if(abs(med-combAnt)>1)
    {
        String data=("#COMB"+String(med)+" ");
        webSocket.broadcastTXT(data);
        
    }    
    combAnt=med;
    //int clientWsNum = webSocket.connectedClients();
}
