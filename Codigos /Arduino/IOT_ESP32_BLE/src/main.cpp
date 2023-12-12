#include <Arduino.h>

// ble
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// wifi
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

std::string chave;

const char* ssid = "brisa-1726032";
const char* password = "s17houuz";

// Configurações do broker MQTT
const char* mqtt_server = "192.168.0.11";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

int FLAG= 0;

class MyCallbacks: public BLECharacteristicCallbacks 
{
    void onWrite(BLECharacteristic *pCharacteristic) 
    {
      std::string value = pCharacteristic->getValue();
      chave = value;

      if (value.length() > 0) 
      {
        FLAG = 1;
        digitalWrite(17, HIGH);
        delay(1000);
        digitalWrite(17, LOW);
        delay(500);
      }
    }
};


void blinkloop(int port, int milis)
{
  digitalWrite(port, HIGH);
  delay(milis);
  digitalWrite(port, LOW);
  delay(milis);
  digitalWrite(port, HIGH);
  delay(milis);
  digitalWrite(port, LOW);
  delay(milis);
  digitalWrite(port, HIGH);
  delay(milis);
  digitalWrite(port, LOW);
  delay(milis);
}

void conectaWifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println("WiFi Connected...");
  blinkloop(18, 500);
}
void reconnect() 
{
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32_client")) 
    {
      Serial.println("Connected to MQTT broker");
    } 
    else 
    {
      Serial.print("Connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");
      delay(5000);
    }
  }
}

void checkFlag()
{
  if(FLAG)
  {
    // mqtt
    const char* chaveChar = chave.c_str();
    client.publish("Acesso 01 - BLE", chaveChar);
    Serial.print("MQTT Publicado");
    blinkloop(17, 100); 
    blinkloop(17, 100);
    FLAG = 0;
  }
}

void setupBLE()
{
  BLEDevice::init("ESP32 01 Acesso");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic
                                      (
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Acesso Laboratorio");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start...");
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  setupBLE();
  conectaWifi();
  client.setServer(mqtt_server, mqtt_port);  
}

void loop() 
{
  if(!client.connected())
  {
    reconnect();
  }
  blinkloop(18, 50);
  checkFlag();
  delay(1000);
}

