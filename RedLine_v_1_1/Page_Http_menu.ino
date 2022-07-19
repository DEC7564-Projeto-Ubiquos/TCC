/* Paginas de resposta as requisições
 *  
 *  
 */

void rootPage()
{
      http_menu+=("OK, sou o servidor!\r\n");
      http_menu+=("Comandos GET:\r\n");
      http_menu+=("/index - http Page\r\n");
      http_menu+=("/index2- Ws_escuro Page \r\n");
      http_menu+=("/index3- Ws_teste Page \r\n");
      http_menu+=("/leituraDados - envia blilhete\r\n");
      http_menu+=("/arAuto  - mantem a temperatura da cabine 5 C abaixo da externa \r\n");
      http_menu+=("/vent0   - Desliga ventilador do ar condicionado \r\n");
      http_menu+=("/vent1   - liga ventilador do ar condicionado velocidade 1 \r\n");
      http_menu+=("/vent2   - liga ventilador do ar condicionado velocidade 2 \r\n");
      http_menu+=("/vent3   - liga ventilador do ar condicionado velocidade 3 \r\n");
}
