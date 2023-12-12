#include <Arduino.h>
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MFRC522.h>

#define TOPICO_SUBSCRIBE "esp8266su"    
#define TOPICO_PUBLISH   "esp8266pu"
#define ID_MQTT  "esp8266id" 
 
#define D0    16
#define D1    0
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1
 
#define SS_PIN D8
#define RST_PIN D0

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

String tag;
 
// WIFI
const char* SSID = "IoT_Embarcados"; 
const char* PASSWORD = "12345678";
  
// MQTT
const char* BROKER_MQTT = "192.168.1.100";
int BROKER_PORT = 1883;
const char* var = "";  

WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoSaida = '0';
  
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
void ler_rfid(void);
 
void setup() 
{
    //inicializações:
    InitOutput();
    initSerial();
    SPI.begin();
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
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;

    // Obtém a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
        char c = (char)payload[i];
        msg += c;
    }

    Serial.print("Mensagem recebida: ");
    Serial.println(msg);

    // Verifica se a mensagem é "L" ou "D" e age de acordo
    if (msg == "L")
    {
        Serial.println("Comando recebido: Ligar");
        digitalWrite(D1, LOW); // Altera para LOW (considerando lógica invertida)
        EstadoSaida = '1';
    }
    else if (msg == "D")
    {
        Serial.println("Comando recebido: Desligar");
        digitalWrite(D1, HIGH); // Altera para HIGH (considerando lógica invertida)
        EstadoSaida = '0';
    }
    else
    {
        Serial.println("Comando desconhecido");
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
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
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
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

void EnviaEstadoOutputMQTT(String tag)
{
    const char* chaveChar = tag.c_str();
    //if (EstadoSaida == '0')
      MQTT.publish(TOPICO_PUBLISH, chaveChar);
 
    //if (EstadoSaida == '1')
    //  MQTT.publish(TOPICO_PUBLISH, "L");
 
    Serial.println("enviado!!");
    delay(100);
}

void InitOutput(void)
{
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
   
    pinMode(4, OUTPUT);  
    rfid.PCD_Init();    
}
 
 
//programa principal
void loop() 
{   
    //garante funcionamento das conexões WiFi e ao broker MQTT
    VerificaConexoesWiFIEMQTT();
 
    //envia o status de todos os outputs para o Broker no protocolo esperado
    ler_rfid();
    //EnviaEstadoOutputMQTT();
 
    //keep-alive da comunicação com broker MQTT
    MQTT.loop();
}

void ler_rfid(void) {
  String temp;
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
    
  if (rfid.PICC_ReadCardSerial()) {
    
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    
    Serial.println(tag);
    temp = tag;
    
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    EnviaEstadoOutputMQTT(temp);
  }
}