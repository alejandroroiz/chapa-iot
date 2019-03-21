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

// Librerias y variables de Servo-SG90
#include <Servo.h>
Servo servo;
#define SERVO_PIN 2

// LEDS
#define ROJO D8
#define AZUL D0
#define VERDE D3

void setup() 
{
  // Iniciar patrones de comunicación
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();
  
  // Iniciar servo
  servo.attach(SERVO_PIN);
  servo.write(0);

  // Iniciar LEDS
  pinMode(ROJO, OUTPUT);
  pinMode(AZUL, OUTPUT);
  pinMode(VERDE, OUTPUT);
  digitalWrite(ROJO, LOW);
  // El led azul nos demuestra que el circuito esta funcionando
  digitalWrite(AZUL, HIGH);
  digitalWrite(VERDE, LOW);
  
  Serial.println("Acerca tu carta al lector...");
  Serial.println();
}

void loop() 
{
  digitalWrite(AZUL, HIGH);
  digitalWrite(ROJO, LOW);
  digitalWrite(VERDE, LOW);
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "30 1B A2 19")
  {
    digitalWrite(AZUL, LOW);
    digitalWrite(ROJO, LOW);
    digitalWrite(VERDE, HIGH);
    Serial.println("Authorized access");
    Serial.println();
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(3000);
  }
 else   {
  digitalWrite(AZUL, LOW);
  digitalWrite(VERDE, LOW);
  digitalWrite(ROJO, HIGH);
  Serial.println("Access denied");
  Serial.println();
  delay(3000);
 }
} 