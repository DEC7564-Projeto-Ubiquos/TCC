void indexWsTeste()
{
      Ws_teste="";
      Ws_teste+=("<html>");
      Ws_teste+=(       "<style>");              
      Ws_teste+=(       "</style>");              
      Ws_teste+=(       "<head>");              
      Ws_teste+=(       "<script>");
      Ws_teste+=(           "var connection = new WebSocket('ws://192.168.4.1:81/', ['esp8266']);");
      Ws_teste+=(           "connection.onopen = function () {");
      Ws_teste+=(              "connection.send('Message from Browser to ESP8266 Working!! ' + new Date());");                     
      Ws_teste+=(              "connection.send('CLIENTE WebSocket' + new Date());");
      Ws_teste+=(              "connection.send('Time: ' + new Date());"); 
      Ws_teste+=(              "connection.send('W'+'1');");
      Ws_teste+=(           "};");
      Ws_teste+=(           "connection.onerror = function (error) {");
      Ws_teste+=(              "console.log('WebSocket Error ', error);");
      Ws_teste+=(           "};");
      Ws_teste+=(           "connection.onmessage = function (e) {");
      Ws_teste+=(              "console.log('Server: ', e.data);");
      Ws_teste+=(              "var tempe=e.data;");
      Ws_teste+=(              "var primeiro='';");
      Ws_teste+=(              "var segundo='';");
      Ws_teste+=(              "if(tempe.search('#RPM')>-1)");
      Ws_teste+=(              "{"); 
      Ws_teste+=(                "primeiro=tempe.split('#RPM');"); 
      Ws_teste+=(                "segundo=primeiro[1].split(' ');");
      Ws_teste+=(                "rota=segundo[0];");
      Ws_teste+=(                "document.getElementById('rota').innerHTML = rota;");
      Ws_teste+=(              "}");
      Ws_teste+=(              "if(tempe.search('#COMB')>-1)");
      Ws_teste+=(              "{"); 
      Ws_teste+=(                "primeiro=tempe.split('#COMB');");
      Ws_teste+=(                "segundo=primeiro[1].split(' ');");
      Ws_teste+=(                "comb=segundo[0];");
      Ws_teste+=(                "document.getElementById('comb').innerHTML = comb;");
      Ws_teste+=(              "}");
      Ws_teste+=(              "if(tempe.search('#A')>-1)");
      Ws_teste+=(              "{ ");
      Ws_teste+=(                "var primeiro=tempe.split('#A');");
      Ws_teste+=(                "var segundo=primeiro[1].split(' ');");
      Ws_teste+=(                "alti=segundo[0];");
      Ws_teste+=(                "document.getElementById('alti').innerHTML = alti+' m';");
      Ws_teste+=(              "}");
      Ws_teste+=(              "if(tempe.search('#P')>-1)");
      Ws_teste+=(              "{ ");
      Ws_teste+=(                "var primeiro=tempe.split('#P');");
      Ws_teste+=(                "var segundo=primeiro[1].split(' ');");
      Ws_teste+=(                "pres=segundo[0];");
      Ws_teste+=(                "document.getElementById('pres').innerHTML = pres+' hPa';");
      Ws_teste+=(              "}");
      Ws_teste+=(              "if(tempe.search('#T_BMP')>-1)");
      Ws_teste+=(              "{ ");
      Ws_teste+=(                "var primeiro=tempe.split('#T_BMP');");
      Ws_teste+=(                "var segundo=primeiro[1].split(' ');");
      Ws_teste+=(                "tBMP=segundo[0];");
      Ws_teste+=(                "document.getElementById('tBMP').innerHTML = tBMP+' &#x2103';");
      Ws_teste+=(                "}");
      Ws_teste+=(                "console.log(comb);");
      Ws_teste+=(                "connection.send('Time: ' + new Date());"); 
      Ws_teste+=(           "};");
                 
      Ws_teste+=(           "function sendRGB() {");
      Ws_teste+=(              "  var r = document.getElementById('r').value;");
      Ws_teste+=(              "  var rEd = '#'+r;");
      Ws_teste+=(              "  connection.send(rEd); ");
      Ws_teste+=(           "}");
      
      Ws_teste+=(           "function acionaRele() {");
      Ws_teste+=(              "  var R1 = (document.getElementById('R1').checked);");
      Ws_teste+=(              "  R1 = R1*1;");
      Ws_teste+=(              "  console.log('R1 = ' + R1); ");
      Ws_teste+=(              "  var R2 = (document.getElementById('R2').checked);");
      Ws_teste+=(              "  R2 = R2*2;");
      Ws_teste+=(              "  console.log('R2 = ' + R2);");
      Ws_teste+=(              "  var R3 = (document.getElementById('R3').checked);");
      Ws_teste+=(              "  R3 = R3*4;");
      Ws_teste+=(              "  console.log('R3 = ' + R3);");
      Ws_teste+=(              "  var R4 = (document.getElementById('R4').checked);");
      Ws_teste+=(              "  R4 = R4*8;");
      Ws_teste+=(              "  console.log('R4 = ' + R4); ");
      Ws_teste+=(              "  var R5 = (document.getElementById('R5').checked);");
      Ws_teste+=(              "  R5 = R5*16;");
      Ws_teste+=(              "  console.log('R5 = ' + R5); ");
      Ws_teste+=(              "  var R6 = (document.getElementById('R6').checked);");
      Ws_teste+=(              "  R6 = R6*32;");
      Ws_teste+=(              "  console.log('R6 = ' + R6);");
      Ws_teste+=(              "  var R7 = (document.getElementById('R7').checked);");
      Ws_teste+=(              "  R7 = R7*64;");
      Ws_teste+=(              "  console.log('R7 = ' + R7);");
      Ws_teste+=(              "  var R8 = (document.getElementById('R8').checked);");
      Ws_teste+=(              "  R8 = R8*128;");
      Ws_teste+=(              "  console.log('R8 = ' + R8);");
      Ws_teste+=(              "  var estado = R1+R2+R3+R4+R5+R6+R7+R8;");
      Ws_teste+=(              "  console.log('estado = ' + estado);");
      Ws_teste+=(              "  connection.send('@'+estado);");   
      Ws_teste+=(           "}");
        
      Ws_teste+=(           "function leBmp180(temperatura, pressao,altitude) {");
      Ws_teste+=(              " connection.send('!'+'1');");
      Ws_teste+=(              " var temp = temperatura;");
      Ws_teste+=(              " var pres = pressao;");
      Ws_teste+=(              " var alti = altitude;");
      Ws_teste+=(              " document.getElementById('tBMP').innerHTML = temp+'&#x2103';");
      Ws_teste+=(              " document.getElementById('pres').innerHTML = pres+'hPa';");
      Ws_teste+=(              " document.getElementById('alti').innerHTML = alti+'m';");             
      Ws_teste+=(           "}");
                    
      Ws_teste+=(       "</script>");
                    
      Ws_teste+=(       "</head>");
      Ws_teste+=(       "<body>");
      Ws_teste+=(       "<h2>Redline Control</h2><br>");
                    
      Ws_teste+=(       "LED Control:<br/>");
      Ws_teste+=(       "<br/>");
      Ws_teste+=(       "R: <input id='r' type='range' min='0' max='255' step='1' onchange='sendRGB();' /><br/>");

      Ws_teste+=(       "<br/><br/>");
                    
      Ws_teste+=(       "Reles<br/>");
      Ws_teste+=(       "<table style='width:50%'>");
      Ws_teste+=(          "<tr>");
      Ws_teste+=(              "<td style='text-align: center;'>1</td>");
      Ws_teste+=(              "<td style='text-align: center;'>2</td>");
      Ws_teste+=(              "<td style='text-align: center;'>3</td>");
      Ws_teste+=(              "<td style='text-align: center;'>4</td>");
      Ws_teste+=(              "<td style='text-align: center;'>5</td>");
      Ws_teste+=(              "<td style='text-align: center;'>6</td>");
      Ws_teste+=(              "<td style='text-align: center;'>7</td>");
      Ws_teste+=(              "<td style='text-align: center;'>8</td>");
      Ws_teste+=(          "</tr>");
      Ws_teste+=(          "<tr>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R1' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R2' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R3' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R4' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R5' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R6' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R7' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(              "<td style='text-align: center;'><input id='R8' type='checkbox' onclick=acionaRele();></td>");
      Ws_teste+=(          "</tr>");
      Ws_teste+=(       "</table>");
      Ws_teste+=(       "<br/><br/>");
      Ws_teste+=(       "BMP180");
      Ws_teste+=(       "<button type='button' onclick=leBmp180(0,0,0);>Atualizar</button>");
      Ws_teste+=(       "<table style='width:50%'>");
      Ws_teste+=(          "<tr>");
      Ws_teste+=(              "<td style='text-align: center;'>Temperatura</td>");
      Ws_teste+=(              "<td style='text-align: center;'>Press&atildeo</td>");
      Ws_teste+=(              "<td style='text-align: center;'>Altitude</td>");
      Ws_teste+=(          "</tr>");
      Ws_teste+=(          "<tr>");
      Ws_teste+=(              "<td style='text-align: center;'><div id='tBMP'></div></td>");
      Ws_teste+=(              "<td style='text-align: center;'><div id='pres'></div></td>");
      Ws_teste+=(              "<td style='text-align: center;'><div id='alti'></div></td>");               
      Ws_teste+=(          "</tr>");
      Ws_teste+=(       "</table><br><br>");
      Ws_teste+=(       "<table style='width:50%'>");
      Ws_teste+=(          "<tr>");
      Ws_teste+=(              "<td style='text-align: center;'>COMB</td>");
      Ws_teste+=(              "<td style='text-align: center;'></td>");
      Ws_teste+=(              "<td style='text-align: center;'></td>");
      Ws_teste+=(              "<td style='text-align: center;'>RPM</td>");
      Ws_teste+=(          "</tr>");
      Ws_teste+=(          "<tr>");
      Ws_teste+=(              "<td style='text-align: center;'><div  style='text-align: center;width:100px;height:60px;border:1px solid #000000;background-color:#0000FF;color:#FFFFFF;margin:0 auto' >");
      Ws_teste+=(                                                    "<h2 id='comb'></h2>");
      Ws_teste+=(                                              "</div></td>");
      Ws_teste+=(              "<td style='text-align: center;'></td>");
      Ws_teste+=(              "<td style='text-align: center;'></td>");
      Ws_teste+=(              "<td style='text-align: center;'><div  style='text-align: center;width:100px;height:60px;border:1px solid #000000;background-color:#0000FF;color:#FFFFFF;margin:0 auto' >");
      Ws_teste+=(                                                    "<h2 id='rota'></h2>");
      Ws_teste+=(                                              "</div></td>");
      Ws_teste+=(          "</tr>");
      Ws_teste+=(        "</table>");
      Ws_teste+=(    "</body>");
      Ws_teste+=(    "</html>");
      
}
