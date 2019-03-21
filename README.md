# CHAPA ELECTRÓNICA

## Librerías Necesarias

Arduino IDE = https://www.arduino.cc/en/Main/Software

ESP8266 LIB = http://arduino.esp8266.com/stable/package_esp8266com_index.json

RC522 LIB = https://github.com/miguelbalboa/rfid

## Hardware Necesario

NodeMCU = http://www.handsontec.com/pdf_learn/esp8266-V10.pdf

LED RGB (COMMON GROUND) = https://www.sparkfun.com/datasheets/Components/YSL-R596CR3G4B5C-C10.pdf

RFID-RC522 = https://www.elecrow.com/download/MFRC522%20Datasheet.pdf

SERVO-SG90 = http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf


### PINOUT DE RFID-RC522 A NODEMCU

RFID       NODEMCU

3.3V       3V3
RST        D1
GND        GND
IRQ        
MISO       D6
MOSI       D7
SCK        D5
SDA        D2

### PINOUT DE RGBLEB A NODEMCU

RGB       NODEMCU

RED       D8
GROUND    GND
GREEN     D3
BLUE      D0

### PINOUT DE SERVO-SG90 A NODEMCU

SERVO     NODEMCU

NARANJA   D4
ROJO      3V3
CAFE      GND
