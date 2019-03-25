/* ALEJANDRO ROIZ WALSS
 * 
 * 
 * PINOUT DE RFID-RC522 A NODEMCU
 * 
 * RFID       NODEMCU
 * 
 * 3.3v       3v3
 * RST        D1
 * GND        GND
 * IRQ        
 * MISO       D6
 * MOSI       D7
 * SCK        D5
 * SDA        D2
 * 
 */

// Librerias y variables de RFID-RC522
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 4 
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
#define CARTA_CORRECTA "30 1B A2 19"

// Librerias y variables de Servo-SG90
#include <Servo.h>
Servo servo;
#define SERVO_PIN 2

// LEDS
#define ROJO D8
#define AZUL D0
#define VERDE D3

// Librerias y variables de comunicación (WiFi)
#include <ESP8266WiFi.h>
const char ssid[] = "ROIZ";
const char pass[] = "holahumano";
WiFiServer server(80); // Servidor montado en puerto 80

void setup() {
  // Iniciar patrones de comunicación  
  SPI.begin();      
  mfrc522.PCD_Init();
  
  // Iniciar servo
  servo.attach(SERVO_PIN);
  servo.write(0);

  // Iniciar LEDS
  pinMode(ROJO, OUTPUT);
  pinMode(AZUL, OUTPUT);
  pinMode(VERDE, OUTPUT);
  inicializaLeds();

  connect();
}

void loop() {

  inicializaLeds();
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) { return; }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) { return; }
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == CARTA_CORRECTA) { correcto(); } 
  else { equivocado(); }
}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void inicializaLeds() {
  digitalWrite(AZUL, HIGH); // El led azul nos demuestra que el circuito esta funcionando
  digitalWrite(ROJO, LOW);
  digitalWrite(VERDE, LOW);
}

void correcto() {
  digitalWrite(AZUL, LOW);
  digitalWrite(ROJO, LOW);
  digitalWrite(VERDE, HIGH);
  servo.write(90);
  delay(3000);
  servo.write(0);
  delay(1000);
}

void equivocado() {
  digitalWrite(AZUL, LOW);
  digitalWrite(VERDE, LOW);
  digitalWrite(ROJO, HIGH);
  delay(1000);
}