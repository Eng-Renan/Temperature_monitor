#include <SPI.h>
#include <Ethernet.h>  // Biblioteca utilizada para comunicação com o Arduino
#include <dht.h>
#define dht_dpin A1 //Pino DATA do Sensor ligado na porta digital 30
#define dht2_dpin2 A2
#define dht3_dpin3 A3
#define dht4_dpin4 A4

dht DHT; //Inicializa o sensor

// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da placa de rede. 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[] = { 172, 22, 132, 30 };  // Define o endereço IP.
    
EthernetServer server(80);  // Porta onde estará aberta para comunicação Internet e Arduino.
 
String readString;


void setup(){
 
Ethernet.begin(mac, ip);  // Chama o MAC e o endereço IP da placa Ethernet.
  server.begin();  //  Inicia o servidor que esta inserido junto a placa Ethernet.
  //sensors.begin();
}
 
void loop()

{

//DHT.read11(dht_dpin); //Lê as informações do sensor
//DHT.read11(dht1_dpin1); //Lê as informações do sensor
//DHT.read11(dht2_dpin2); //Lê as informações do sensor
//DHT.read11(dht3_dpin3); //Lê as informações do sensor
//---------------------------------------------------------------------------COMANDOS ETHERNET SHIELD--------------------------------------------------------------------------------------  
  EthernetClient client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
 
        if (readString.length() < 100) 
        {
          readString += c;             
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          //client.println (F("<META HTTP-EQUIV=REFRESH CONTENT=5;>"));
          client.println();
    
           // A partir daqui começa os códigos html.
    
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1><title>Telemetria Estudios</title></H1>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<p>");
          client.println("<p>");
          client.println("<center><img src=http://tvcultura.com.br/_img/tvcultura/programas_abertura_TV.jpg weight=300 height=100></center>");
          client.println("<p>");
          client.println("<p>");
          client.println("<font size=+4><center><B>Telemetria Estudios</B><BR><font size=+3>");
          client.println("<p>");
          client.println("</BODY>");
          client.println("</HTML>");
//==================================================================================================================================================================================          


             
             DHT.read11(dht_dpin); //Lê as informações do sensor
             client.println("Umidade estudio B = ");
             client.println(DHT.humidity);
             client.println(" %   <font size=+2><p>");
             client.println("Temperatura  estudio B = ");
             client.println(DHT.temperature);
             client.println(" Celsius  <font size=+2><p>");

             DHT.read11(dht2_dpin2); //Lê as informações do sensor
             client.println("Umidade estudio C = ");
             client.println(DHT.humidity);
             client.println(" %   <font size=+2><p>");
             client.println("Temperatura estudio C = ");
             client.println(DHT.temperature);
             client.println(" Celsius  <font size=+2><p>");

             DHT.read11(dht3_dpin3); //Lê as informações do sensor
             client.println("Umidade estudio D = ");
             client.println(DHT.humidity);
             client.println(" %   <font size=+2><p>");
             client.println("Temperatura estudio D = ");
             client.println(DHT.temperature);
             client.println(" Celsius  <font size=+2><p>");

             DHT.read11(dht4_dpin4); //Lê as informações do sensor
             client.println("Umidade estudio E = ");
             client.println(DHT.humidity);
             client.println(" %   <font size=+2><p>");
             client.println("Temperatura estudio E = ");
             client.println(DHT.temperature);
             client.println(" Celsius  <font size=+2><p>");
             
          client.println (F("<META HTTP-EQUIV=REFRESH CONTENT=10;>"));
          delay(1);
          client.stop();
          
          readString="";    
        }
      }
    }
  }
}
