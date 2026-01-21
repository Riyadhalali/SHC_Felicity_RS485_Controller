#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ModbusMaster.h>

/*
Battery RJ45: 5 - 6 pins 
5: B in module 
6: A in module




connection of max485 to arduino 
pin 10 -> RO
pin 11 -> DO
pin 3 -> de/re 



Felicity Battery Registers:
0x010C - Current (signed, /10 for Amps)
0x010D - Voltage (/10 for Volts)
0x0110 - SOC (/10 for %)
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
  // Start from 0x010C to include current register
  uint8_t result = battery.readHoldingRegisters(0x010C, 10);
  
  if (result == battery.ku8MBSuccess) {
    // Buffer index:  0=0x010C, 1=0x010D, 2=0x010E, 3=0x010F, 4=0x0110
    int16_t rawCurrent = (int16_t)battery.getResponseBuffer(0);  // 0x010C
    float current = rawCurrent / 10.0;
    float voltage = battery.getResponseBuffer(1) / 10.0;         // 0x010D
    float soc = battery.getResponseBuffer(4) / 10.0;             // 0x0110
    
    Serial.println("----------------------------");
    Serial.print("Voltage: ");
    Serial.print(voltage, 1);
    Serial.println(" V");
    
    Serial.print("Current: ");
    Serial.print(current, 1);
    Serial.print(" A");
    if (current < 0) Serial.println(" (Discharging)");
    else if (current > 0) Serial.println(" (Charging)");
    else Serial.println(" (Idle)");
    
    Serial.print("SOC:     ");
    Serial.print(soc, 1);
    Serial.println(" %");
    
  } else {
    Serial.print("Error: 0x");
    Serial.println(result, HEX);
  }
  
  delay(2000);
}