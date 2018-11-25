// --- Bibliotecas Auxiliares ---
#include <SPI.h> // Biblioteca para o barramento
#include <WiFi.h> // Biblioteca comunicação Wifi
#include <PubSubClient.h> // Biblioteca para publicar utilizando o protocolo MQTT
#include "EmonLib.h" 

// --- Mapeamento de Hardware ---
EnergyMonitor emon1;
#define wifi_ssid "ssid"
#define wifi_password "senha"
#define mqtt_server "ip do servidor mqtt"
//#define mqtt_user "admin"
//#define mqtt_password "admin"
#define your_topic "/esp32/sctLeitura"
WiFiClient espClient;
PubSubClient client(espClient);

// --- Variáveis Globais ---
int pino_sct = 36; // Pino do sensor SCT
String sctLeitura;
String recebe;
char data[20];
 
void setup(){
  Serial.begin(115200);
  emon1.current(pino_sct, 3); //Pino, calibracao - Cur Const= Ratio/BurdenR. 1800/62 = 29.

  SPI.begin(); // Inicia comunicação SPI bus
  setup_wifi();
  client.setServer(mqtt_server, 1883);
} 
  
void loop(){ 
  
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  
  emon1.calcIrms(1480); // Calcula a corrente  
  float i = emon1.Irms;
  
  if(i>10.0){
    recebe = "Ligado";
    sctLeitura = "{ \"estado\":\"" + recebe + "\"}";
    sctLeitura.toCharArray(data, (sctLeitura.length() + 1));
    Serial.println("Valor de data: ");
    Serial.println(data);
    client.publish(your_topic, data, true);
  }
  else if(i<10){
    i = 0;
    recebe = "Desligado";
    sctLeitura = "{ \"estado\":\"" + recebe + "\"}";
    sctLeitura.toCharArray(data, (sctLeitura.length() + 1));
    Serial.println("Valor de data: ");
    Serial.println(data);
    client.publish(your_topic, data, true);
  }
  
  delay(5000);
}

void setup_wifi(){
  delay(10);
  //inicio da conexão com a rede wifi
  Serial.println();
  Serial.print("Conectando: ");
  Serial.println(wifi_ssid) ;

  WiFi.begin(wifi_ssid, wifi_password);

  //enquanto não estiver conectado imprime os pontinhos
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado ao Wifi");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while(!client.connected()){
    Serial.print("Tentando conectar o MQTT...");
    if(client.connect("ESP32")){
      Serial.println();
      Serial.println("Conectado");
    } else{
        Serial.print("Falha, rc=");
        Serial.print(client.state());
        Serial.println("Próxima tentativa em 5 segundos");
        delay(5000);
      }
  }  
}
