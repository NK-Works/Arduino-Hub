#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

const char ssid[] = "SSID";
const char pass[] = "PASS";
const char broker[] = "BROKER";
int port = 8883;

const char mqttUser[] = "USER_NAME";
const char mqttPass[] = "USER_PASS";

WiFiSSLClient net;
MqttClient mqtt(net);

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;
long duration;
int distance;


void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi Connected.");

  // Set MQTT username and password
  mqtt.setUsernamePassword(mqttUser, mqttPass);
  
  // Connect to MQTT Broker
  Serial.print("Connecting to MQTT broker...");
  while (!mqtt.connect(broker, port)) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("MQTT Connected.");
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2;
  Serial.println(distance);
  while (distance < 10) {  // Change this distance as per your requirement
    if (mqtt.connected()) {
    Serial.println("MQTT client connected to broker");
    mqtt.beginMessage("Task3.3");
    mqtt.print("wave");
    mqtt.endMessage();
    Serial.println("Message sent to MQTT server");
    delay(5000);
  } else {
    Serial.println("MQTT client not connected to broker");
  }
  }
  delay(500); // Measurement cycle
}