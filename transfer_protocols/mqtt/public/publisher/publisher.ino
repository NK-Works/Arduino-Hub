/* This code is made by Anneshu Nag, Student ID- 2210994760  */
/*                    Dated- 31/08/2023                      */

/* In this code, the Arduino Nano 33 IoT is acting as the publisher. */
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
  
// WiFi credentials
char ssid[] = "SSID"; // WiFi SSID
char pass[] = "PASS";  // WiFi Password

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;
float duration, distance;

// WiFi and MQTT client instances
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// MQTT broker details
const char broker[] = "mqtt-dashboard.com";
int port = 1883;
const char topic[] = "NK-Works/MQTT/Test";

// Time interval for sending messages (milliseconds)
const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // Wait for serial port to connect
  }

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // Keep the MQTT connection alive
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Ultrasonic sensor measurements
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
    
    // Send message if distance is below threshold
    if (distance < 10) {
      Serial.print("Sending 'wave' message to topic: ");
      Serial.println(topic);

      // Begin constructing MQTT message
      mqttClient.beginMessage(topic);
      mqttClient.print("NK : Wave signal recorded!");
      mqttClient.endMessage();
      delay(1000); // Delay for stability
    
    } else if (distance < 30 && distance > 10){
      Serial.print("Sending 'pat' message to topic: ");
      Serial.println(topic);

      // Begin constructing MQTT message
      mqttClient.beginMessage(topic);
      mqttClient.print("NK : Pat signal recorded!");
      mqttClient.endMessage();
      delay(1000); // Delay for stability
    }

    Serial.println();
    count++;
  }
}
