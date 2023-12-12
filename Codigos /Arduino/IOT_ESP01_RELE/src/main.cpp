#include <Arduino.h>

#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
 
#define TOPICO_SUBSCRIBE "iotreturn"     
#define TOPICO_PUBLISH   "IotJP"    
#define ID_MQTT  "HomeAut"                                
 
//defines - mapeamento de pinos do NodeMCU
#define D0    16
#define D1    0
#define D2    4
#define D3    1599
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1
 
const char* SSID = "brisa-1726032"; 
const char* PASSWORD = "s17houuz"; 
  
const char* BROKER_MQTT = "192.168.0.11";
int BROKER_PORT = 1883; 

WiFiClient espClient; 
PubSubClient MQTT(espClient); 
char EstadoSaida = '0'; 

void initSerial(void);
void initWiFi(void);
void initMQTT(void);
void reconectWiFi(void); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
 
void setup() 
{
  InitOutput();
  initSerial();
  initWiFi();
  initMQTT();
}
  
void initSerial() 
{
  Serial.begin(115200);
}

void initWiFi() 
{
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");
     
  reconectWiFi();
}

void initMQTT() 
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);   
  MQTT.setCallback(mqtt_callback);            
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
  String msg;

  for(int i = 0; i < length; i++) 
  {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.print("Mensagem recebida: ");
  Serial.println(msg);

  if (msg == "L")
  {   
    Serial.println("Comando recebido: Ligar");
    digitalWrite(D1, LOW); 
    delay(3000);
    EstadoSaida = '1';
    digitalWrite(D1, HIGH);
  }    
}
  
void reconnectMQTT() 
{
  while (!MQTT.connected()) 
  {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) 
    {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe(TOPICO_SUBSCRIBE); 
    } 
    else
    {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Havera nova tentatica de conexao em 2s");
      delay(2000);
    }
  }
}

void reconectWiFi() 
{
  if (WiFi.status() == WL_CONNECTED)
    return;
        
  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(100);
    Serial.print(".");
  }
   
  Serial.println();
  Serial.print("Conectado com sucesso na rede ");
  Serial.print(SSID);
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}
 
void VerificaConexoesWiFIEMQTT(void)
{
  if (!MQTT.connected()) 
  reconnectMQTT();  
  reconectWiFi(); 
}

void EnviaEstadoOutputMQTT(void)
{
  if (EstadoSaida == '0')
  MQTT.publish(TOPICO_PUBLISH, "D");
 
  if (EstadoSaida == '1')
  MQTT.publish(TOPICO_PUBLISH, "L");
 
  Serial.println("- Estado da saida D0 enviado ao broker!");
  delay(1000);
}

void InitOutput(void)
{
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);          
}

void loop() 
{
  VerificaConexoesWiFIEMQTT();
  MQTT.loop();
}