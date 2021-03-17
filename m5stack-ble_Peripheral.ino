
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <M5Stack.h>

 
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
 
void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.print("Hello");
//  M5.Power.begin();
  
  Serial.println("Starting BLE work!");

  
  BLEDevice::init("ESP32 peripheral");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
 
  pService->start();
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  
  BLEAdvertisementData advertisementData;
  advertisementData.setManufacturerData("hoge");
  pAdvertising->setAdvertisementData(advertisementData);
  
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();

}
 
void loop() {
  // put your main code here, to run repeatedly:
//  delay(2000);
  M5.update();
}
