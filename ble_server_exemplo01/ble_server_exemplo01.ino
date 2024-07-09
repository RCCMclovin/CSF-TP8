#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEScan.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEUUID.h>
#include "esp_bt.h"
#include <string.h>

// identificadores únicos e mágicos para serviços BLE
#define MYUUID "8904b455-2e64-497c-82e9-b441cd3b7368"
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

bool deviceConnected = false;
int valor = 1;

// classe que lida com eventos de conexão e desconexão
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer *pServer){
    Serial.println(" ** Usuário novo conectado ** ");
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer){
    Serial.println(" ** Usuário desconectado ** ");
    deviceConnected = false;
  }
};

class MyCallback : public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic *pCharacteristic){
    Serial.println("Pediu algo");
  }

  void onWrite(BLECharacteristic *pCharacteristic){
    Serial.println("Pediu para escrever algo");
  }
};


class MyValorCharacteristic: public BLECharacteristic {
  
  public: MyValorCharacteristic(): BLECharacteristic(BLEUUID(MYUUID), PROPERTY_NOTIFY|PROPERTY_READ){
    //Setando um valor inicial
    this->valor = 1;
    setValor();
  }

  //Função que atualiza o valor no BLE
  void setValor(){
    setValue(this->valor);
    this->valor = this->valor + 1 ;
  }

  //Função que pega o valor do BLE
  std::string getValor(){
    return getValue();
  }

  //Declarando a variavel de valor
  private :
    uint32_t valor;
};

//Declarando Variaveis Globais
MyValorCharacteristic *pCharacteristic ;
void setup() {
  Serial.begin(9600);

  //inicia um device ble
  BLEDevice::init("Aula de CsF");
  Serial.println("Device ble iniciado...");

  //cria um servidor (server = sender) - tipo uma estação de rádio
  BLEServer *pServer = BLEDevice::createServer();
  //seta callbacks
  pServer->setCallbacks(new MyServerCallbacks());

  //crio um servico
  BLEService *pService = pServer->createService(SERVICE_UUID);
  Serial.println("\tServico(s) ble iniciado...");

  pCharacteristic = new MyValorCharacteristic();
  //adiciono a característica mágica ao serviço
  pService->addCharacteristic(pCharacteristic);
  Serial.println("\tCaracteristica(s) ble iniciada(s)...");
  
  pCharacteristic->addDescriptor(new BLE2902());

  //setando callbacks para rleitura e escrita na característica
  pCharacteristic->setCallbacks(new MyCallback());

  pService->start();

  // Começa a anunciar o servidor BLE (em um beacon)
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  Serial.println("esperando cliente conectar...");
}

void loop() {
  //niveis de pootencia do sinal do bluetooth

  esp_power_level_t lst[] = {ESP_PWR_LVL_N11, ESP_PWR_LVL_N9, ESP_PWR_LVL_N6, ESP_PWR_LVL_N3, ESP_PWR_LVL_N0, ESP_PWR_LVL_P3, ESP_PWR_LVL_P6, ESP_PWR_LVL_P9};
  BLEDevice::setPower(lst[0]);
  if(deviceConnected){
    //for(int i = 0; i < 8; i++){
      //BLEDevice::setPower(lst[i]);
      // Atualizando e notificando valor quando um cliente está conectado
      pCharacteristic->setValor();
      Serial.println("Cliente conectou e setei um novo valor..."); //pode ser um dado de um sensor
  
      pCharacteristic->notify(); 
      Serial.print("Notifiquei meu cliente com o valor: ");
      Serial.println(valor);
      delay(3000); // Espera um pouco antes de enviar o próximo valor
      valor++;
    //}

    //delay(500);
  }

}
