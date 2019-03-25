/* ALEJANDRO ROIZ WALSS
 * 
 * 
 * PINOUT DE SERVO A NODEMCU
 * 
 * SERVO       NODEMCU
 * 
 * ROJO       3v3
 * CAFE       GND
 * NARANJA    D4
 */

// Librerias y variables de Servo-SG90
#include <Servo.h>
Servo servo;
#define SERVO_PIN 2

// Librerias y variables de comunicación (WiFi y MQTT)
#include <ESP8266WiFi.h>
#include <MQTT.h>

const char ssid[] = "ROIZ";
const char pass[] = "holahumano";

WiFiClient net;
MQTTClient client;

void setup() 
{
  // Iniciar patrones de comunicación
  Serial.begin(9600);      
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
  
  // Iniciar servo
  servo.attach(SERVO_PIN);
  servo.write(0);
}

void loop() 
{
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
} 

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("servo", "6593720e", "f6e260efc8885e0b")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/chapa");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(payload == "open"){
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(3000);
  }
}