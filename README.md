# Felicity Battery RS485 Controller

Arduino-based monitor for Felicity LPBF48-100A LiFePO4 battery using RS485 Modbus communication.

## Features

- Read battery voltage
- Read state of charge (SOC)
- Read discharge/charge current
- RS485 Modbus RTU communication

## Hardware Required

- Arduino Uno (or compatible)
- RS485 to TTL module (MAX485)
- Felicity LPBF48-100A battery (or similar)
- RJ45 cable for battery connection

## Wiring

| Arduino | RS485 Module |
|---------|--------------|
| Pin 10  | RO           |
| Pin 11  | DI           |
| Pin 3   | DE + RE      |
| 5V      | VCC          |
| GND     | GND          |

| RS485 Module | Felicity Battery (RJ45) |
|--------------|-------------------------|
| A+           | Pin 6 (RS485A)          |
| B-           | Pin 5 (RS485B)          |

## Modbus Register Map

| Register | Description          | Scale |
|----------|----------------------|-------|
| 0x010D   | Battery Voltage      | ÷10 V |
| 0x010F   | Current              | ÷10 A |
| 0x0110   | State of Charge (SOC)| ÷10 % |

## Dependencies

- [ModbusMaster](https://github.com/4-20ma/ModbusMaster) library
- SoftwareSerial (built-in)

## Installation

1. Clone this repository
2. Open in PlatformIO or Arduino IDE
3. Install ModbusMaster library
4. Upload to Arduino

## Usage

1. Connect RS485 module to Arduino
2. Connect RS485 to Felicity battery RJ45 port (pins 5 & 6)
3. Open Serial Monitor at 9600 baud
4. View battery data

## Output Example

```
=== Felicity Battery Monitor ===
----------------------------
Voltage: 52.5 V
Current: 0.0 A
SOC:     30.0 %
```

## License

MIT License

## Author

Riyad Halali
