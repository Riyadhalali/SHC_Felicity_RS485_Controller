#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ModbusMaster.h>

/*
Battery RJ45: 5 - 6 pins 
5: B in module 
6: A in module

*/

#define MAX485_RX      10
#define MAX485_TX      11
#define MAX485_RE_DE   3
#define BATTERY_ID     1

SoftwareSerial softSerial(MAX485_RX, MAX485_TX);
ModbusMaster battery;

void preTransmission() {
  digitalWrite(MAX485_RE_DE, HIGH);
}

void postTransmission() {
  digitalWrite(MAX485_RE_DE, LOW);
}

void setup() {
  pinMode(MAX485_RE_DE, OUTPUT);
  digitalWrite(MAX485_RE_DE, LOW);

  Serial.begin(9600);
  softSerial.begin(9600);

  battery.begin(BATTERY_ID, softSerial);
  battery.preTransmission(preTransmission);
  battery.postTransmission(postTransmission);

  Serial.println("=== Felicity Battery Monitor ===");
}

void loop() {
  uint8_t result = battery.readHoldingRegisters(0x010D, 4);
  
  if (result == battery.ku8MBSuccess) {
    float voltage = battery.getResponseBuffer(0) / 10.0;
    float current = battery.getResponseBuffer(2) / 10.0;
    float soc = battery.getResponseBuffer(3) / 10.0;
    
    Serial.println("----------------------------");
    Serial.print("Voltage: ");
    Serial.print(voltage, 1);
    Serial.println(" V");
    
    Serial.print("Current: ");
    Serial.print(current, 1);
    Serial.println(" A");
    
    Serial.print("SOC:     ");
    Serial.print(soc, 1);
    Serial.println(" %");
    
  } else {
    Serial.print("Error: 0x");
    Serial.println(result, HEX);
  }
  
  delay(2000);
}